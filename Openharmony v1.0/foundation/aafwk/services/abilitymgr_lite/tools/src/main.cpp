/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdio>
#include <cstdlib>
#include <getopt.h>

#include "ability_tool.h"

using OHOS::AbilityTool;

static void PrintUsage()
{
    printf("Usage:\n");
    printf("aa start -p bundlename -n ability_name\n");
    printf("aa stopability -p bundlename -n ability_name\n");
    printf("aa terminate -p bundlename\n");
    printf("aa dump -p bundlename -n ability_name -e extra_option\n");
    printf("aa dump -a\n");
    printf("\n");
    printf("Options:\n");
    printf(" -h (--help)                Show the help information.             [eg: aa -h]\n");
    printf(" -p (--bundlename)          Appoint the bundlename name.           [eg: -p com.huawei]\n");
    printf(" -n (--abilityname)         Appoint the ability name.              [eg: -n MyAbility]\n");
    printf(" -a (--all)                 [Unnecessary]dump all ability info.    [eg: -a]\n");
    printf(" -e (--extra)               [Unnecessary]extra info when dump.     [eg: -e]\n");
    printf("\n");
    printf("Commands:\n");
    printf("aa start                    Start the target ability.\n");
    printf("aa stopability              Stop the target service ability.\n");
    printf("aa terminate                Terminate the target app.\n");
    printf("aa dump                     Dump ability\n");
}

static void SetOptions(int argc, char *argv[], const option *options, AbilityTool &tool)
{
    const char *command = argv[1];
    int index = 0;
    const char *optStr = "hap:n:e:";
    int para = 0;
    while ((para = getopt_long(argc, argv, optStr, options, &index)) != -1) {
        switch (para) {
            case 'h': {
                PrintUsage();
                exit(0);
            }
            case 'a': {
                tool.SetDumpAll();
                break;
            }
            case 'p': {
                tool.SetBundleName(optarg);
                break;
            }
            case 'n': {
                tool.SetAbilityName(optarg);
                break;
            }
            case 'e': {
                tool.SetExtra(optarg);
                break;
            }
            default:
                printf("Try 'aa -h' for more information.\n");
                exit(-1);
        }
    }
    if (!tool.SetCommand(command)) {
        printf("Unsupported this command. Try 'aa -h' for more information.\n");
        exit(-1);
    }
}

int main(int argc, char *argv[])
{
    struct option options[] = {
        {"help",        no_argument,       nullptr, 'h'},
        {"bundlename",  required_argument, nullptr, 'p'},
        {"abilityname", required_argument, nullptr, 'n'},
        {"all",         no_argument,       nullptr, 'a'},
        {"extra",       required_argument, nullptr, 'e'},
        {nullptr,       no_argument,       nullptr, 0},
    };

    if (argc == 1) {
        PrintUsage();
        exit(0);
    }
    AbilityTool tool = AbilityTool();
    SetOptions(argc, argv, options, tool);
    bool ret = tool.RunCommand();
    if (!ret) {
        printf("Failed to run the command. \n");
    }
    exit(0);
}
