/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "init_jobs.h"
#include <stdio.h>
#include <string.h>
#include "init_cmds.h"
#include "securec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define JOBS_ARR_NAME_IN_JSON "jobs"
#define CMDS_ARR_NAME_IN_JSON "cmds"
#define MAX_JOBS_COUNT        10

static const char* g_supportedJobs[] = {
    "pre-init",
    "init",
    "post-init",
};

static Job* g_jobs = NULL;
static int g_jobCnt = 0;

static int GetJobName(const cJSON* jobItem, Job* resJob)
{
    char* jobNameStr = cJSON_GetStringValue(cJSON_GetObjectItem(jobItem, "name"));
    if (jobNameStr == NULL) {
        return 0;
    }

    size_t supportJobCnt = sizeof(g_supportedJobs) / sizeof(g_supportedJobs[0]);
    for (size_t i = 0; i < supportJobCnt; ++i) {
        if (strlen(g_supportedJobs[i]) == strlen(jobNameStr) &&
            strncmp(g_supportedJobs[i], jobNameStr, strlen(g_supportedJobs[i])) == 0) {
            if (memcpy_s(resJob->name, MAX_JOB_NAME_LEN, jobNameStr, strlen(jobNameStr)) != EOK) {
                return 0;
            }
            resJob->name[strlen(jobNameStr)] = '\0';
            return 1;
        }
    }
    return 0;
}

static void ParseJob(const cJSON* jobItem, Job* resJob)
{
    if (!GetJobName(jobItem, resJob)) {
        (void)memset_s(resJob, sizeof(*resJob), 0, sizeof(*resJob));
        return;
    }

    cJSON* cmdsItem = cJSON_GetObjectItem(jobItem, CMDS_ARR_NAME_IN_JSON);
    if (!cJSON_IsArray(cmdsItem)) {
        return;
    }

    int cmdLinesCnt = cJSON_GetArraySize(cmdsItem);
    if (cmdLinesCnt <= 0) {  // empty job, no cmd
        return;
    }

    if (cmdLinesCnt > MAX_CMD_CNT_IN_ONE_JOB) {
        printf("[Init] ParseAllJobs, too many cmds[cnt %d] in one job, it should not exceed %d.\n",\
            cmdLinesCnt, MAX_CMD_CNT_IN_ONE_JOB);
        return;
    }

    resJob->cmdLines = (CmdLine*)malloc(cmdLinesCnt * sizeof(CmdLine));
    if (resJob->cmdLines == NULL) {
        return;
    }

    if (memset_s(resJob->cmdLines, cmdLinesCnt * sizeof(CmdLine), 0, cmdLinesCnt * sizeof(CmdLine)) != EOK) {
        free(resJob->cmdLines);
        resJob->cmdLines = NULL;
        return;
    }
    resJob->cmdLinesCnt = cmdLinesCnt;

    for (int i = 0; i < cmdLinesCnt; ++i) {
        char* cmdLineStr = cJSON_GetStringValue(cJSON_GetArrayItem(cmdsItem, i));
        ParseCmdLine(cmdLineStr, &(resJob->cmdLines[i]));
    }
}

void ParseAllJobs(const cJSON* fileRoot)
{
    if (fileRoot == NULL) {
        printf("[Init] ParseAllJobs, input fileRoot is NULL!\n");
        return;
    }

    cJSON* jobArr = cJSON_GetObjectItemCaseSensitive(fileRoot, JOBS_ARR_NAME_IN_JSON);
    int jobArrSize = 0;
    if (cJSON_IsArray(jobArr)) {
        jobArrSize = cJSON_GetArraySize(jobArr);
    }

    if (jobArrSize <= 0 || jobArrSize > MAX_JOBS_COUNT) {
        printf("[Init] ParseAllJobs, jobs count %d is invalid, should be positive and not exceeding %d.\n",\
            jobArrSize, MAX_JOBS_COUNT);
        return;
    }

    Job* retJobs = (Job*)malloc(sizeof(Job) * jobArrSize);
    if (retJobs == NULL) {
        printf("[Init] ParseAllJobs, malloc failed! job arrSize %d.\n", jobArrSize);
        return;
    }

    if (memset_s(retJobs, sizeof(Job) * jobArrSize, 0, sizeof(Job) * jobArrSize) != EOK) {
        printf("[Init] ParseAllJobs, memset_s failed.\n");
        free(retJobs);
        retJobs = NULL;
        return;
    }

    for (int i = 0; i < jobArrSize; ++i) {
        cJSON* jobItem = cJSON_GetArrayItem(jobArr, i);
        ParseJob(jobItem, &(retJobs[i]));
    }
    g_jobs = retJobs;
    g_jobCnt = jobArrSize;
}

void DoJob(const char* jobName)
{
    if (jobName == NULL) {
        printf("[Init] DoJob, input jobName NULL!\n");
        return;
    }

    for (int i = 0; i < g_jobCnt; ++i) {
        if (strncmp(jobName, g_jobs[i].name, strlen(g_jobs[i].name)) == 0) {
            CmdLine* cmdLines = g_jobs[i].cmdLines;
            for (int j = 0; j < g_jobs[i].cmdLinesCnt; ++j) {
                DoCmd(&(cmdLines[j]));
            }
            break;
        }
    }
}

void ReleaseAllJobs()
{
    if (g_jobs == NULL) {
        return;
    }

    for (int i = 0; i < g_jobCnt; ++i) {
        if (g_jobs[i].cmdLines != NULL) {
            free(g_jobs[i].cmdLines);
            g_jobs[i].cmdLines = NULL;
            g_jobs[i].cmdLinesCnt = 0;
        }
    }

    free(g_jobs);
    g_jobs = NULL;
    g_jobCnt = 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
