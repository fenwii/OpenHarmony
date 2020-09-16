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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include "gtest/gtest.h"
#include "utils.h"
#define MAX 5

using namespace testing::ext;

static int g_count = 0;
static int g_cancel = 0;
static pthread_mutex_t g_mutex_lock;
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_notfull = PTHREAD_COND_INITIALIZER;
static pthread_cond_t g_notempty = PTHREAD_COND_INITIALIZER;
static pthread_rwlock_t g_rwlock;
static pthread_spinlock_t g_spinlock;
static int g_testvalue = 0;
static int g_index = 0;
static int g_retvalue[25] = {2};
static int g_wcount;
static int g_top = 0;
static int g_bottom = 0;
static int g_rwindex = 0;
static int g_rwresult[15] = {0};
static int g_fifteen = 15;
static int g_fourty = 40;
static int g_fivehundred = 520;
std::ostringstream s1;
std::ostringstream s2;
class ActsFutexApiTest : public testing::Test {
protected:
    static void *thread_fun_1(void *data)
    {
        pthread_mutex_lock(&g_mutex_lock);
        g_count++;
        printf("%s g_count: %d\n", __func__, g_count);
        pthread_mutex_unlock(&g_mutex_lock);
        return NULL;
    }

    static void *thread_fun_2(void *data)
    {
        pthread_mutex_lock(&g_mutex_lock);
        g_count++;
        printf("%s g_count: %d\n", __func__, g_count);
        pthread_mutex_unlock(&g_mutex_lock);
        return NULL;
    }

    static void *thread_fun_3(void *data)
    {
        pthread_mutex_lock(&g_mutex_lock);
        g_count++;
        printf("%s g_count: %d\n", __func__, g_count);
        pthread_mutex_unlock(&g_mutex_lock);
        return NULL;
    }

    static void *thread_fun_4(void *data)
    {
        pthread_mutex_lock(&g_mutex_lock);
        int i = 0;
        while (i < 10) {
            s1 << "1" ;
            i++;
        }
        pthread_mutex_unlock(&g_mutex_lock);
        return NULL;
    }

    static void *thread_fun_5(void *data)
    {
        pthread_mutex_lock(&g_mutex_lock);
        int i = 0;
        while (i < 10) {
            s1 << "2" ;
            i++;
        }
        pthread_mutex_unlock(&g_mutex_lock);
        return NULL;
    }

    static void *thread_fun_6(void *data)
    {
        if (pthread_mutex_trylock(&g_mutex_lock) != 0) {
            g_cancel = 1;
            return 0;
        }
        int i = 0;
        g_cancel = 0;

        while (i < 10) {
            if (g_cancel) break;
            s2 << "1" ;
            i++;
	        Msleep(10);
        }

        pthread_mutex_unlock(&g_mutex_lock);
        return NULL;
    }

    static void *thread_fun_7(void *data)
    {
        if (pthread_mutex_trylock(&g_mutex_lock) != 0) {
            g_cancel = 1;
            return 0;
        }
        int i = 0;
        g_cancel = 0;

        while (i < 10) {
            if (g_cancel) break;
            s2 << "2" ;
            i++;
            Msleep(10);
        }
        pthread_mutex_unlock(&g_mutex_lock);
        return NULL;
    }

    static void *produce(void* arg)
    {
        int i;
        for ( i = 0; i < MAX*2; i++)
        {
            pthread_mutex_lock(&g_mutex);
            while ((g_top + 1)%MAX == g_bottom)
            {
                printf("full! producer is waiting\n");
                pthread_cond_wait(&g_notfull, &g_mutex);
            }
            Msleep(10);
            g_top = (g_top + 1) % MAX;
            pthread_cond_signal(&g_notempty);
            pthread_mutex_unlock(&g_mutex);
        }
        return (void*)1;
    }
    static void *consume(void* arg)
    {
        int i;
        for ( i = 0; i < MAX*2; i++)
        {
            pthread_mutex_lock(&g_mutex);
            while (g_top%MAX == g_bottom)
            {
                printf("empty! consumer is waiting\n");
                g_count++;
                pthread_cond_wait(&g_notempty, &g_mutex);
            }
            Msleep(1);
            g_bottom = (g_bottom + 1) % MAX;
            pthread_cond_signal(&g_notfull);
            pthread_mutex_unlock(&g_mutex);
        }
        return (void*)2;
    }

    static void *pth_wr(void *arg)
    {
        int i = (int)arg;
        while (g_wcount <= g_fivehundred)
        {
            pthread_rwlock_wrlock(&g_rwlock);
            printf("write================w_count = %ld, %d thread\n", g_wcount += g_fourty, i + 1);
            if (g_rwindex < g_fifteen)
            {
                g_rwresult[g_rwindex] = g_wcount;
                g_rwindex++;
            }
            pthread_rwlock_unlock(&g_rwlock);
            Msleep(10);
        }
        return NULL;
    }

    static void *pth_rd(void *arg)
    {
        int i = (int)arg;
        while (g_wcount <= g_fivehundred)
        {
            pthread_rwlock_rdlock(&g_rwlock);
            printf("read================w_count = %ld, %d thread\n", g_wcount, i + 1);
            pthread_rwlock_unlock(&g_rwlock);
            Msleep(10);
        }
        return NULL;
    }

    static void *UDP_first_thread(void *arg)
    {
        int i ,ret;
        printf("UDP_first_thread begin\n");
        for(i =0 ;i<10 ;i++ ) {
            pthread_spin_lock(&g_spinlock);
            g_testvalue++;
            g_retvalue[g_index] = g_testvalue;
            g_index++;
            printf("test_value %d\n", g_testvalue);
            Msleep(10);
            pthread_spin_unlock(&g_spinlock);
            Msleep(5);
        }
        printf("UDP_first_thread end\n");
        return NULL;
    }

    static void *UDP_second_thread(void *arg)
    {
        int i ,ret;
        printf("UDP_second_thread begin\n");
        for(i =0 ;i<10 ;i++ ) {
            pthread_spin_lock(&g_spinlock);
            g_testvalue--;
            g_retvalue[g_index] = g_testvalue;
            g_index++;
            printf("test_value %d\n", g_testvalue);
            Msleep(10);
            pthread_spin_unlock(&g_spinlock);
            Msleep(5);
        }
        printf("UDP_second_thread end\n");
        return NULL;
    }
};

/**
* @tc.number     SUB_KERNEL_NDKAPI_FUTEX_LOCK_0100
* @tc.name       testpthreadmutexlock api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsFutexApiTest, testpthreadmutexlock, TestSize.Level1) {
    int ret;
    pthread_t pid[3];

    ret = pthread_mutex_init(&g_mutex_lock, NULL);
    if (ret != 0) {
        printf("mutex init failed\n");
        EXPECT_EQ(ret, 0);
    }

    pthread_create(&pid[0], NULL, thread_fun_1, NULL);
    pthread_create(&pid[1], NULL, thread_fun_2, NULL);
    pthread_create(&pid[2], NULL, thread_fun_3, NULL);

    pthread_join(pid[0], NULL);
    pthread_join(pid[1], NULL);
    pthread_join(pid[2], NULL);

    pthread_mutex_destroy(&g_mutex_lock);
    EXPECT_EQ(g_count, 3) << "ErrInfo: g_count, --> g_count:='" << g_count << "'";
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_FUTEX_LOCK_0200
* @tc.name       testpthreadmutexlock1 api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsFutexApiTest, testpthreadmutexlock1, TestSize.Level1) {
    int ret;
    pthread_t pid[3];

    ret = pthread_mutex_init(&g_mutex_lock, NULL);
    if (ret != 0) {
        printf("mutex init failed\n");
        EXPECT_EQ(ret, 0);
    }

    pthread_create(&pid[0], NULL, thread_fun_4, NULL);
	Msleep(5);
    pthread_create(&pid[1], NULL, thread_fun_5, NULL);

    pthread_join(pid[0], NULL);
    pthread_join(pid[1], NULL);

    pthread_mutex_destroy(&g_mutex_lock);
    EXPECT_EQ(s1.str(), "11111111112222222222");
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_FUTEX_LOCK_0300
* @tc.name       testpthreadmutextrylock api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsFutexApiTest, testpthreadmutextrylock, TestSize.Level1) {
    int ret;
    pthread_t pid[3];

    ret = pthread_mutex_init(&g_mutex_lock, NULL);
    if (ret != 0) {
        printf("mutex init failed\n");
        EXPECT_EQ(ret, 0);
    }

    pthread_create(&pid[0], NULL, thread_fun_6, NULL);
    pthread_create(&pid[1], NULL, thread_fun_7, NULL);

    pthread_join(pid[0], NULL);
    pthread_join(pid[1], NULL);

    pthread_mutex_destroy(&g_mutex_lock);
    string s = s2.str();
    EXPECT_NE(s, "11111111112222222222");
    EXPECT_NE(s, "22222222221111111111");
    printf("s2.str = %s", s.c_str());
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_FUTEX_LOCK_0400
* @tc.name       testpthread_cond_wait api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsFutexApiTest, testpthread_cond_wait, TestSize.Level1) {
    pthread_t thid1;
    pthread_t thid2;
    pthread_t thid3;
    pthread_t thid4;

    int ret1;
    int ret2;
    int ret3;
    int ret4;
    g_count = 0;
    pthread_create(&thid1, NULL, produce, NULL);
    pthread_create(&thid2, NULL, consume, NULL);
    pthread_create(&thid3, NULL, produce, NULL);
    pthread_create(&thid4, NULL, consume, NULL);

    pthread_join(thid1, (void**)&ret1);
    pthread_join(thid2, (void**)&ret2);
    pthread_join(thid3, (void**)&ret3);
    pthread_join(thid4, (void**)&ret4);
    EXPECT_NE(g_count, 0);
    printf("testpthread_cond_wait g_count = %d", g_count);
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_FUTEX_LOCK_0500
* @tc.name       testpthread_rwlock api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsFutexApiTest, testpthread_rwlock, TestSize.Level1) {
    pthread_t pth[10];
    int i;
    pthread_rwlock_init(&g_rwlock, nullptr);
    for (i = 0; i < 5; i++)
    {
        pthread_create(&pth[i], NULL, pth_wr, (void *)i);
    }
    for (i = 0; i < 5; i++)
    {
        pthread_create(&pth[5 + i], NULL, pth_rd, (void *)i);
    }
    
    while (1)
    {
        if (g_wcount >= 520)
        {
            for (int j = 0; j < 10; j++)
            {
                pthread_cancel(pth[j]);
                pthread_join(pth[j], nullptr);
            }
            break;
        }
        Msleep(200);
    }
    EXPECT_EQ(g_rwresult[0], 40);
    EXPECT_EQ(g_rwresult[1], 80);
    EXPECT_EQ(g_rwresult[2], 120);
    EXPECT_EQ(g_rwresult[3], 160);
    EXPECT_EQ(g_rwresult[4], 200);
    EXPECT_EQ(g_rwresult[5], 240);
    EXPECT_EQ(g_rwresult[6], 280);
    EXPECT_EQ(g_rwresult[7], 320);
    EXPECT_EQ(g_rwresult[8], 360);
    EXPECT_EQ(g_rwresult[9], 400);
    EXPECT_EQ(g_rwresult[10], 440);
    EXPECT_EQ(g_rwresult[11], 480);
    EXPECT_EQ(g_rwresult[12], 520);
    EXPECT_EQ(g_rwresult[13], 560);
}

/**
* @tc.number     SUB_KERNEL_NDKAPI_FUTEX_LOCK_0600
* @tc.name       testpthread_spin_lock api
* @tc.desc       [C- SOFTWARE -0200]
* @tc.size       SMALL
* @tc.type       FUNC
*/
HWTEST_F(ActsFutexApiTest, testpthread_spin_lock, TestSize.Level1) {
    int err;
    pthread_t tid1, tid2;

    pthread_spin_init(&g_spinlock, 0);
    err = pthread_create(&tid1, NULL, UDP_first_thread, NULL);
    if (err != 0) {
        perror(" fail to create thread ");
    }
    err = pthread_create(&tid2, NULL, UDP_second_thread, NULL);
    if (err != 0) {
        perror(" fail to create thread ");
    }
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    for (int i = 0; i < 20; i++)
    {
        if (i%2 == 0)
        {
            EXPECT_EQ(g_retvalue[i], 1);
        }
        else
        {
            EXPECT_EQ(g_retvalue[i], 0);
        }
    }
}