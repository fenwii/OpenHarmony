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

#include "nativeapi_fs.h"
#include <securec.h>
#include "ability_env.h"
#include "js_async_work.h"
#include "nativeapi_common.h"
#include "nativeapi_fs_impl.h"

namespace OHOS {
namespace ACELite {
namespace {
char g_uriFullPath[FILE_NAME_MAX_LEN + 1] = {0};
const unsigned int PREFIX_LEN = strlen(FILE_PREFIX);

bool IsValidPath(const char* path)
{
    if ((path == nullptr) || (strlen(path) > URI_NAME_MAX_LEN)) {
        return false;
    }
    if ((strlen(path) < PREFIX_LEN) || (strncmp(path, FILE_PREFIX, PREFIX_LEN) != 0)) {
        return false;
    }
    if ((strstr(path, "/./") != nullptr) || (strstr(path, "/../") != nullptr)) {
        return false;
    }
    return true;
}

int GetFullPath(const char* uri, char* fullPath, int len)
{
    if (!IsValidPath(uri) || (fullPath == nullptr)) {
        return ERROR_CODE_PARAM;
    }
    const char* dataPath = GetDataPath();
    if (dataPath == nullptr) {
        return ERROR_CODE_PARAM;
    }
    if (memset_s(fullPath, len, 0x0, len) != EOK) {
        return ERROR_CODE_GENERAL;
    }
    if (sprintf_s(fullPath, len, "%s%s", dataPath, uri + PREFIX_LEN) < 0) {
        return ERROR_CODE_GENERAL;
    }
    return NATIVE_SUCCESS;
}

JSIValue ExecuteAsyncWork(const JSIValue thisVal, const JSIValue* args,
    uint8_t argsNum, AsyncWorkHandler ExecuteFunc, bool flag = false)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if (!NativeapiCommon::IsValidJSIValue(args, argsNum)) {
        return undefValue;
    }
    FuncParams* params = new FuncParams();
    if (params == nullptr) {
        return undefValue;
    }
    params->thisVal = JSI::AcquireValue(thisVal);
    params->args = JSI::AcquireValue(args[0]);
    params->flag = flag;
    JsAsyncWork::DispatchAsyncWork(ExecuteFunc, reinterpret_cast<void *>(params));
    return undefValue;
}

void ExecuteCopyFile(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* src = JSI::GetStringProperty(args, FILE_SOURCE_URI);
    char* dest = JSI::GetStringProperty(args, FILE_DESTINATION_URI);
    char* destFullPath = nullptr;
    JSIValue result = JSI::CreateUndefined();
    int ret = GetFullPath(src, g_uriFullPath, sizeof(g_uriFullPath));
    JSI::ReleaseString(src);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    destFullPath = reinterpret_cast<char *>(malloc(FILE_NAME_MAX_LEN + 1));
    if (destFullPath == nullptr) {
        NativeapiCommon::FailCallBack(thisVal, args, ERROR_CODE_GENERAL);
        goto EXIT;
    }
    ret = GetFullPath(dest, destFullPath, FILE_NAME_MAX_LEN + 1);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    ret = CopyFileImpl(g_uriFullPath, destFullPath);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    if (params->flag) {
        ret = DeleteFileImpl(g_uriFullPath);
    }
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    result = JSI::CreateString(dest);
    NativeapiCommon::SuccessCallBack(thisVal, args, result);
EXIT:
    JSI::ReleaseString(dest);
    free(destFullPath);
    JSI::ReleaseValueList(args, thisVal, result, ARGS_END);
    delete params;
}

void ExecuteDeleteAccess(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* src = JSI::GetStringProperty(args, FILE_URI);
    int ret = GetFullPath(src, g_uriFullPath, sizeof(g_uriFullPath));
    JSI::ReleaseString(src);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    if (params->flag) {
        ret = DeleteFileImpl(g_uriFullPath);
    } else {
        ret = AccessImpl(g_uriFullPath);
    }
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, JSI::CreateUndefined());
EXIT:
    JSI::ReleaseValueList(args, thisVal, ARGS_END);
    delete params;
}

int GetFileListInner(const char* path, const char* key, JSIValue& result)
{
    int fileNum = GetFileNum(g_uriFullPath);
    if (fileNum <= 0) {
        return fileNum;
    }
    FileMetaInfo *fileList = reinterpret_cast<FileMetaInfo *>(malloc(fileNum * sizeof(FileMetaInfo)));
    if (fileList == nullptr) {
        return ERROR_CODE_GENERAL;
    }
    if (memset_s(fileList, fileNum * sizeof(FileMetaInfo), 0x0, fileNum * sizeof(FileMetaInfo)) != EOK) {
        free(fileList);
        return ERROR_CODE_GENERAL;
    }
    int ret = GetFileListImpl(g_uriFullPath, fileList, fileNum);
    if (ret != NATIVE_SUCCESS) {
        free(fileList);
        return ret;
    }
    JSIValue arrayValue = JSI::CreateArray(fileNum);
    for (int i = 0; i < fileNum; i++) {
        JSIValue tmp = JSI::CreateObject();
        JSI::SetStringProperty(tmp, FILE_URI, fileList[i].fileName);
        JSI::SetNumberProperty(tmp, FILE_LENGTH, fileList[i].fileSize);
        JSI::SetNumberProperty(tmp, FILE_LAST_MODIFIED_TIME, fileList[i].fileMtime);
        JSI::SetStringProperty(tmp, FILE_TYPE, TYPE_FILE);
        if (S_ISDIR(fileList[i].fileMode)) {
            JSI::SetStringProperty(tmp, FILE_TYPE, TYPE_DIR);
        }
        JSI::SetPropertyByIndex(arrayValue, i, tmp);
        JSI::ReleaseValue(tmp);
    }
    free(fileList);
    JSI::SetNamedProperty(result, key, arrayValue);
    JSI::ReleaseValue(arrayValue);
    return NATIVE_SUCCESS;
}

void ExecuteGetFileList(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* uri = JSI::GetStringProperty(args, FILE_URI);
    JSIValue result = JSI::CreateObject();
    int ret = GetFullPath(uri, g_uriFullPath, sizeof(g_uriFullPath));
    JSI::ReleaseString(uri);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    if (params->flag) {
        ret = GetFileListInner(g_uriFullPath, FILE_LIST, result);
    } else {
        ret = GetFileListInner(g_uriFullPath, SUB_FILES, result);
    }
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, result);
EXIT:
    JSI::ReleaseValueList(args, thisVal, result, ARGS_END);
    delete params;
}

void ExecuteGetFileInfo(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* src = JSI::GetStringProperty(args, FILE_URI);
    bool recursive = JSI::GetBooleanProperty(args, RECURSIVE);
    struct stat info = {0};
    JSIValue result = JSI::CreateObject();
    int ret = GetFullPath(src, g_uriFullPath, sizeof(g_uriFullPath));
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    ret = StatImpl(g_uriFullPath, &info);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    if (recursive && (S_ISDIR(info.st_mode))) {
        JSI::ReleaseString(src);
        ExecuteGetFileList(data);
        return;
    }
    JSI::SetStringProperty(result, FILE_URI, src);
    JSI::SetNumberProperty(result, FILE_LENGTH, info.st_size);
    JSI::SetNumberProperty(result, FILE_LAST_MODIFIED_TIME, info.st_mtime);
    JSI::SetStringProperty(result, FILE_TYPE, TYPE_FILE);
    if (S_ISDIR(info.st_mode)) {
        JSI::SetStringProperty(result, FILE_TYPE, TYPE_DIR);
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, result);
EXIT:
    JSI::ReleaseString(src);
    JSI::ReleaseValueList(args, thisVal, result, ARGS_END);
    delete params;
}

void ExecuteWriteTextFile(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* src = JSI::GetStringProperty(args, FILE_URI);
    char* text = JSI::GetStringProperty(args, TEXT);
    bool append = JSI::GetBooleanProperty(args, FILE_APPEND);
    int ret = GetFullPath(src, g_uriFullPath, sizeof(g_uriFullPath));
    JSI::ReleaseString(src);
    if ((text == nullptr) || (ret != NATIVE_SUCCESS)) {
        NativeapiCommon::FailCallBack(thisVal, args, ERROR_CODE_PARAM);
        goto EXIT;
    }
    ret = WriteTextFile(g_uriFullPath, text, strlen(text), append);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, JSI::CreateUndefined());
EXIT:
    JSI::ReleaseString(text);
    JSI::ReleaseValueList(args, thisVal, ARGS_END);
    delete params;
}

int ReadTextInner(const char* src, int position, int length, JSIValue& result)
{
    if ((position < 0) || (length < 0)) {
        return ERROR_CODE_PARAM;
    }
    if (length == 0) {
        length = TEXT_MAX_READ_LEN;
    }
    int ret = GetFullPath(src, g_uriFullPath, sizeof(g_uriFullPath));
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    struct stat info = {0};
    ret = StatImpl(g_uriFullPath, &info);
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    size_t readLen = (info.st_size > length) ? length : info.st_size;
    if (readLen > TEXT_MAX_READ_LEN) {
        return ERROR_CODE_READ_TOO_LONG;
    }
    char* text = reinterpret_cast<char *>(malloc(readLen + 1));
    if (text == nullptr) {
        return ERROR_CODE_GENERAL;
    }
    size_t actualLen = 0;
    ret = ReadFileImpl(g_uriFullPath, text, readLen, position, &actualLen);
    if (ret != NATIVE_SUCCESS) {
        free(text);
        return ret;
    }
    text[actualLen] = '\0';
    JSI::SetStringProperty(result, TEXT, text);
    free(text);
    return NATIVE_SUCCESS;
}

void ExecuteReadTextFile(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* src = JSI::GetStringProperty(args, FILE_URI);
    double position = JSI::GetNumberProperty(args, FILE_POSITION);
    double length = JSI::GetNumberProperty(args, FILE_LENGTH);
    JSIValue result = JSI::CreateObject();
    int ret = ReadTextInner(src, position, length, result);
    JSI::ReleaseString(src);
    if (ret == NATIVE_SUCCESS) {
        NativeapiCommon::SuccessCallBack(thisVal, args, result);
    } else {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
    }
    JSI::ReleaseValueList(args, thisVal, result, ARGS_END);
    delete params;
}

void ExecuteDirFunc(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* src = JSI::GetStringProperty(args, FILE_URI);
    int ret = GetFullPath(src, g_uriFullPath, sizeof(g_uriFullPath));
    JSI::ReleaseString(src);
    bool recursive = JSI::GetBooleanProperty(args, RECURSIVE);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    if (params->flag) {
        ret = CreateDirImpl(g_uriFullPath, recursive);
    } else {
        ret = RemoveDirImpl(g_uriFullPath, recursive);
    }
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, JSI::CreateUndefined());
EXIT:
    JSI::ReleaseValueList(args, thisVal, ARGS_END);
    delete params;
}
#if (JS_FWK_TYPEDARRAY == NATIVE_FEATURE_ON)
int ReadArrayFileInner(const char* path, size_t len, unsigned int position, JSIValue& result)
{
    struct stat info = {0};
    int ret = StatImpl(path, &info);
    if (ret != NATIVE_SUCCESS) {
        return ret;
    }
    void* text = malloc(info.st_size + 1);
    if (text == nullptr) {
        return ERROR_CODE_GENERAL;
    }
    size_t actualLen = 0;
    ret = ReadFileImpl(path, text, len, static_cast<int>(position), &actualLen);
    if (ret != NATIVE_SUCCESS) {
        free(text);
        return ret;
    }
    uint8_t* ptr = nullptr;
    JSIValue arrayBuffer = JSI::CreateArrayBuffer(actualLen, ptr);
    if (ptr == nullptr) {
        free(text);
        JSI::ReleaseValue(arrayBuffer);
        return ERROR_CODE_GENERAL;
    }
    ret = memcpy_s(ptr, actualLen, text, actualLen);
    free(text);
    if (ret != EOK) {
        JSI::ReleaseValue(arrayBuffer);
        return ERROR_CODE_GENERAL;
    }
    JSIValue typedArray = JSI::CreateTypedArray(TypedArrayType::JSI_UINT8_ARRAY, actualLen, arrayBuffer, 0);
    JSI::SetNamedProperty(result, FILE_BUFFER, typedArray);
    JSI::ReleaseValueList(typedArray, arrayBuffer, ARGS_END);
    return NATIVE_SUCCESS;
}

void ExecuteReadArrayFile(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* src = JSI::GetStringProperty(args, FILE_URI);
    double position = JSI::GetNumberProperty(args, FILE_POSITION);
    double length = JSI::GetNumberProperty(args, FILE_LENGTH);
    JSIValue result = JSI::CreateObject();
    int ret = ERROR_CODE_PARAM;
    if ((position < 0) || (length < 0)) {
        JSI::ReleaseString(src);
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    ret = GetFullPath(src, g_uriFullPath, sizeof(g_uriFullPath));
    JSI::ReleaseString(src);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    ret = ReadArrayFileInner(g_uriFullPath, static_cast<int>(length), static_cast<int>(position), result);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, result);
EXIT:
    JSI::ReleaseValueList(args, thisVal, result, ARGS_END);
    delete params;
}

void ExecuteWriteArrayFile(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    char* src = JSI::GetStringProperty(args, FILE_URI);
    int ret = GetFullPath(src, g_uriFullPath, sizeof(g_uriFullPath));
    JSI::ReleaseString(src);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        JSI::ReleaseValueList(args, thisVal, ARGS_END);
        delete params;
        return;
    }
    JSIValue buffer = JSI::GetNamedProperty(args, FILE_BUFFER);
    double position = JSI::GetNumberProperty(args, FILE_POSITION);
    bool append = JSI::GetBooleanProperty(args, FILE_APPEND);
    TypedArrayType type = TypedArrayType::JSI_INVALID_ARRAY;
    size_t length = 0;
    JSIValue arrayBuffer = JSI::CreateUndefined();
    size_t byteOffset = 0;
    uint8_t* arrayPtr = JSI::GetTypedArrayInfo(buffer, type, length, arrayBuffer, byteOffset);
    ret = ERROR_CODE_PARAM;
    if ((position < 0) || (arrayPtr == nullptr) || (type != TypedArrayType::JSI_UINT8_ARRAY)) {
        JSI::ReleaseValueList(buffer, arrayBuffer, ARGS_END);
        NativeapiCommon::FailCallBack(thisVal, args, ERROR_CODE_PARAM);
        goto EXIT;
    }
    ret = WriteArrayFile(g_uriFullPath, arrayPtr, length, static_cast<int>(position), append);
    JSI::ReleaseValueList(buffer, arrayBuffer, ARGS_END);
    if (ret != NATIVE_SUCCESS) {
        NativeapiCommon::FailCallBack(thisVal, args, ret);
        goto EXIT;
    }
    NativeapiCommon::SuccessCallBack(thisVal, args, JSI::CreateUndefined());
EXIT:
    JSI::ReleaseValueList(args, thisVal, ARGS_END);
    delete params;
}
#endif
}

void InitNativeApiFs(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "move", NativeapiFs::MoveFile);
    JSI::SetModuleAPI(exports, "copy", NativeapiFs::CopyFile);
    JSI::SetModuleAPI(exports, "delete", NativeapiFs::DeleteFile);
    JSI::SetModuleAPI(exports, "list", NativeapiFs::GetFileList);
    JSI::SetModuleAPI(exports, "get", NativeapiFs::GetFileInfo);
    JSI::SetModuleAPI(exports, "readText", NativeapiFs::ReadTextFile);
    JSI::SetModuleAPI(exports, "writeText", NativeapiFs::WriteTextFile);
    JSI::SetModuleAPI(exports, "access", NativeapiFs::Access);
    JSI::SetModuleAPI(exports, "mkdir", NativeapiFs::CreateDir);
    JSI::SetModuleAPI(exports, "rmdir", NativeapiFs::RemoveDir);

#if (JS_FWK_TYPEDARRAY == NATIVE_FEATURE_ON)
    JSI::SetModuleAPI(exports, "readArrayBuffer", NativeapiFs::ReadArrayFile);
    JSI::SetModuleAPI(exports, "writeArrayBuffer", NativeapiFs::WriteArrayFile);
#endif
}

JSIValue NativeapiFs::MoveFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteCopyFile, true);
}

JSIValue NativeapiFs::CopyFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteCopyFile);
}

JSIValue NativeapiFs::DeleteFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteDeleteAccess, true);
}

JSIValue NativeapiFs::GetFileList(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteGetFileList, true);
}

JSIValue NativeapiFs::GetFileInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteGetFileInfo);
}

JSIValue NativeapiFs::WriteTextFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteWriteTextFile);
}

JSIValue NativeapiFs::ReadTextFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteReadTextFile);
}

JSIValue NativeapiFs::Access(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteDeleteAccess);
}

JSIValue NativeapiFs::CreateDir(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteDirFunc, true);
}

JSIValue NativeapiFs::RemoveDir(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteDirFunc);
}

#if (JS_FWK_TYPEDARRAY == NATIVE_FEATURE_ON)
JSIValue NativeapiFs::ReadArrayFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteReadArrayFile);
}

JSIValue NativeapiFs::WriteArrayFile(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteWriteArrayFile);
}
#endif
} // ACELite
} // OHOS
