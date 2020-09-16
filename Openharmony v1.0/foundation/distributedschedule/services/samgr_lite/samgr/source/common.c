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
#include "common.h"
#include <securec.h>
#include "memory_adapter.h"

#define GROW_STEP 4
Vector VECTOR_Make(VECTOR_Key key, VECTOR_Compare compare)
{
    Vector vector = {0, 0, 0, NULL, key, compare};
    return vector;
}

void VECTOR_Clear(Vector *vector)
{
    if (vector == NULL) {
        return;
    }
    if (vector->data == NULL) {
        return;
    }
    SAMGR_Free(vector->data);
    vector->max = 0;
    vector->top = 0;
    vector->free = 0;
    vector->data = NULL;
}

int16 VECTOR_Add(Vector *vector, void *element)
{
    if (vector == NULL || element == NULL) {
        return INVALID_INDEX;
    }

    if (vector->top >= vector->max) {
        int16 i;
        // use released data elements preferentially
        for (i = vector->top - (int16)1; i >= 0; --i) {
            if (vector->data[i] == NULL) {
                vector->data[i] = element;
                vector->free--;
                return i;
            }
        }

        if (vector->max + GROW_STEP < 0) {
            return INVALID_INDEX;
        }

        void **data = (void **)SAMGR_Malloc(sizeof(void *) * (vector->max + GROW_STEP));
        if (data == NULL) {
            return INVALID_INDEX;
        }

        if (vector->data != NULL) {
            // data's length is bigger than vector->data's length and only copy vector->data's length's memory;
            // no need to check return value
            (void)memcpy_s(data, sizeof(void *) * (vector->max + GROW_STEP),
                           vector->data, sizeof(void *) * vector->max);
            SAMGR_Free(vector->data);
        }
        vector->data = data;
        vector->max += GROW_STEP;
    }

    vector->data[vector->top] = element;
    return vector->top++;
}

void *VECTOR_At(Vector *vector, int16 index)
{
    if (vector == NULL || vector->top <= index || index < 0) {
        return NULL;
    }

    return vector->data[index];
}

void *VECTOR_Swap(Vector *vector, int16 index, void *element)
{
    if (vector == NULL || vector->top <= index || index < 0) {
        return NULL;
    }
    if (element == NULL) {
        vector->free++;
    }
    void *oldElement = vector->data[index];
    vector->data[index] = element;
    return oldElement;
}

int16 VECTOR_Find(Vector *vector, const void *element)
{
    if (vector == NULL || element == NULL) {
        return INVALID_INDEX;
    }
    return VECTOR_FindByKey(vector, (vector->key == NULL) ? element : vector->key(element));
}

int16 VECTOR_FindByKey(Vector *vector, const void *key)
{
    if (vector == NULL || key == NULL) {
        return INVALID_INDEX;
    }

    int16 i;
    for (i = 0; i < vector->top; ++i) {
        if (vector->data[i] == NULL) {
            continue;
        }

        void *first = (vector->key != NULL) ? vector->key(vector->data[i]) : vector->data[i];
        if (first == key) {
            return i;
        }

        if (vector->compare == NULL || first == NULL) {
            continue;
        }

        if (vector->compare(first, key) == 0) {
            return i;
        }
    }
    return INVALID_INDEX;
}

int16 VECTOR_Size(Vector *vector)
{
    if (vector == NULL) {
        return INVALID_INDEX;
    }
    return vector->top;
}

int16 VECTOR_Num(Vector *vector)
{
    if (vector == NULL) {
        return INVALID_INDEX;
    }
    return vector->top - vector->free;
}
