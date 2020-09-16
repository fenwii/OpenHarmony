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

#include "zip_file.h"

#include <cassert>
#include <cstring>
#include <limits>
#include <ostream>

#include "log.h"
#include "securec.h"
#include "zlib.h"

namespace OHOS {
namespace {
#define ZIPPOS_ADD_AND_CHECK_OVERFLOW(first, second, sum)                               \
{                                                                                       \
    if ((second > 0) && (first > (std::numeric_limits<ZipPos>::max() - second))) {      \
        return false;                                                                   \
    }                                                                                   \
    sum = first + second;                                                               \
}

constexpr uint32_t MAX_FILE_NAME = 256;
constexpr uint32_t UNZIP_BUFFER_SIZE = 1024;
constexpr uint32_t UNZIP_BUF_IN_LEN = 2 * UNZIP_BUFFER_SIZE;         // in  buffer length: 2KB
constexpr uint32_t UNZIP_BUF_OUT_LEN = 4 * UNZIP_BUFFER_SIZE;        // out buffer length: 4KB
constexpr uint32_t LOCAL_HEADER_SIGNATURE = 0x04034b50;
constexpr uint32_t CENTRAL_SIGNATURE = 0x02014b50;
constexpr uint32_t EOCD_SIGNATURE = 0x06054b50;
constexpr uint32_t DATA_DESC_SIGNATURE = 0x08074b50;
constexpr uint32_t FLAG_DATA_DESC = 0x8;
constexpr size_t FILE_READ_COUNT = 1;
constexpr uint8_t INFLATE_ERROR_TIMES = 5;
} // namespace

ZipEntry::ZipEntry(const CentralDirEntry &centralEntry)
{
    compressionMethod = centralEntry.compressionMethod;
    uncompressedSize = centralEntry.uncompressedSize;
    compressedSize = centralEntry.compressedSize;
    localHeaderOffset = centralEntry.localHeaderOffset;
    crc = centralEntry.crc;
    flags = centralEntry.flags;
}

ZipFile::ZipFile(const std::string &pathName)
    : pathName_(pathName)
{
    HILOG_INFO(HILOG_MODULE_APP, "create ZipFile instance");
}

ZipFile::~ZipFile()
{
    Close();
}

bool ZipFile::CheckEndDir(const EndDir &endDir) const
{
    size_t lenEndDir = sizeof(EndDir);
    if ((endDir.numDisk != 0) ||
        (endDir.signature != EOCD_SIGNATURE) ||
        (endDir.startDiskOfCentralDir != 0) ||
        (endDir.offset >= fileLength_) ||
        (endDir.totalEntriesInThisDisk != endDir.totalEntries) ||
        (endDir.commentLen != 0) ||
        // central dir cant overlap end of central dir
        ((endDir.offset + endDir.sizeOfCentralDir + lenEndDir) > fileLength_)) {
        HILOG_ERROR(HILOG_MODULE_APP, "end dir formate error");
        return false;
    }
    return true;
}

bool ZipFile::ParseEndDirectory()
{
    size_t endDirLen = sizeof(EndDir);
    ZipPos endFilePos = fileLength_;
    if (fileLength_ <= endDirLen) {
        HILOG_ERROR(HILOG_MODULE_APP,
            "parse EOCD file length(%{public}llu) <= end dir length(%{public}zu)", fileLength_, endDirLen);
        return false;
    }
    ZipPos eocdPos = endFilePos - endDirLen;
    if (fseek(file_, eocdPos, SEEK_SET) != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "locate EOCD seek failed, error: %{public}s", strerror(errno));
        return false;
    }
    if (fread(&endDir_, sizeof(EndDir), FILE_READ_COUNT, file_) != FILE_READ_COUNT) {
        HILOG_ERROR(HILOG_MODULE_APP, "read EOCD struct failed, error: %{public}s", strerror(errno));
        return false;
    }
    centralDirPos_ = endDir_.offset;
    return CheckEndDir(endDir_);
}

bool ZipFile::ParseAllEntries()
{
    bool ret = true;
    ZipPos currentPos = centralDirPos_;
    CentralDirEntry directoryEntry = {};
    size_t fileLength = 0;

    for (int32_t i = 0; i < endDir_.totalEntries; i++) {
        std::string fileName;
        fileName.reserve(MAX_FILE_NAME);
        fileName.resize(MAX_FILE_NAME - 1);

        if (fseek(file_, currentPos, SEEK_SET) != 0) {
            HILOG_ERROR(HILOG_MODULE_APP,
                "parse entry(%{public}d) seek zipEntry failed, error: %{public}s", i, strerror(errno));
            ret = false;
            break;
        }

        if (fread(&directoryEntry, sizeof(CentralDirEntry), FILE_READ_COUNT, file_) != FILE_READ_COUNT) {
            HILOG_ERROR(HILOG_MODULE_APP, "parse entry(%{public}d) read ZipEntry failed, error: %{public}s",
                i, strerror(errno));
            ret = false;
            break;
        }

        if (directoryEntry.signature != CENTRAL_SIGNATURE) {
            HILOG_ERROR(HILOG_MODULE_APP,
                "parse entry(%{public}d) check signature(0x%{public}08x) at pos(0x%{public}08llx) failed",
                i, directoryEntry.signature, currentPos);
            ret = false;
            break;
        }

        fileLength = (directoryEntry.nameSize >= MAX_FILE_NAME) ? (MAX_FILE_NAME - 1) : (directoryEntry.nameSize);
        if (fread(&(fileName[0]), fileLength, FILE_READ_COUNT, file_) != FILE_READ_COUNT) {
            HILOG_ERROR(HILOG_MODULE_APP,
                "parse entry(%{public}d) read file name failed, error: %{public}s", i, strerror(errno));
            ret = false;
            break;
        }
        fileName.resize(fileLength);

        ZipEntry currentEntry(directoryEntry);
        currentEntry.fileName = fileName;
        entriesMap_[fileName] = currentEntry;
        fileNames_.emplace_back(fileName);

        ZIPPOS_ADD_AND_CHECK_OVERFLOW(currentPos, sizeof(directoryEntry), currentPos);
        ZIPPOS_ADD_AND_CHECK_OVERFLOW(currentPos, directoryEntry.nameSize, currentPos);
        ZIPPOS_ADD_AND_CHECK_OVERFLOW(currentPos, directoryEntry.extraSize, currentPos);
        ZIPPOS_ADD_AND_CHECK_OVERFLOW(currentPos, directoryEntry.commentSize, currentPos);
    }
    HILOG_INFO(HILOG_MODULE_APP, "parse %{public}d central entries from %{private}s", endDir_.totalEntries,
        pathName_.c_str());
    return ret;
}

const std::vector<std::string> &ZipFile::GetFileNames() const
{
    return fileNames_;
}

bool ZipFile::Open()
{
    HILOG_INFO(HILOG_MODULE_APP, "open: %{private}s", pathName_.c_str());
    if (isOpen_) {
        HILOG_ERROR(HILOG_MODULE_APP, "has already opened");
        return true;
    }

    if (pathName_.length() > PATH_MAX) {
        HILOG_ERROR(HILOG_MODULE_APP, "path length(%{public}zu) longer than max path length(%{public}d)",
            pathName_.length(), PATH_MAX);
        return false;
    }
    char realPath[PATH_MAX + 1] = { 0 };
    if (realpath(pathName_.c_str(), realPath) == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "transform real path error: %{public}s", strerror(errno));
        return false;
    }

    FILE* tmpFile = fopen(realPath, "rb");
    if (tmpFile == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "open file(%{public}s) failed, error: %{private}s", pathName_.c_str(),
            strerror(errno));
        return false;
    }

    if (fseek(tmpFile, 0, SEEK_END) != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "file seek failed, error: %{public}s", strerror(errno));
        fclose(tmpFile);
        return false;
    }

    ZipPos fileLength = ftell(tmpFile);
    if (fileLength_ == 0) {
        fileLength_ = fileLength;
    }

    file_ = tmpFile;
    bool result = ParseEndDirectory();
    if (result) {
        result = ParseAllEntries();
    }
    // it means open file success.
    isOpen_ = true;
    return result;
}

void ZipFile::Close()
{
    HILOG_INFO(HILOG_MODULE_APP, "close: %{private}s", pathName_.c_str());
    if (!isOpen_ || file_ == nullptr) {
        HILOG_WARN(HILOG_MODULE_APP, "file is not opened");
        return;
    }

    entriesMap_.clear();
    fileNames_.clear();
    pathName_ = "";
    isOpen_ = false;

    if (fclose(file_) != 0) {
        HILOG_WARN(HILOG_MODULE_APP, "close failed, error: %{public}s", strerror(errno));
    }
    file_ = nullptr;
}

// Get all file zipEntry in this file
const ZipEntryMap &ZipFile::GetAllEntries() const
{
    return entriesMap_;
}

bool ZipFile::GetEntry(const std::string &entryName, ZipEntry &resultEntry) const
{
    HILOG_INFO(HILOG_MODULE_APP, "get entry by name: %{public}s", entryName.c_str());
    auto iter = entriesMap_.find(entryName);
    if (iter != entriesMap_.end()) {
        resultEntry = iter->second;
        HILOG_DEBUG(HILOG_MODULE_APP, "get entry successed");
        return true;
    }
    HILOG_ERROR(HILOG_MODULE_APP, "get entry failed");
    return false;
}

size_t ZipFile::GetLocalHeaderSize(const uint16_t nameSize, const uint16_t extraSize) const
{
    size_t localSize = sizeof(LocalHeader);
    if (localSize > std::numeric_limits<size_t>::max() - nameSize - extraSize) {
        return 0;
    }
    return localSize + nameSize + extraSize;
}

bool ZipFile::CheckDataDesc(const ZipEntry &zipEntry, const LocalHeader &localHeader) const
{
    uint32_t crcLocal = 0;
    uint32_t compressedLocal = 0;
    uint32_t uncompressedLocal = 0;

    if (localHeader.flags & FLAG_DATA_DESC) { // use data desc
        DataDesc dataDesc;

        size_t localHeaderSize = GetLocalHeaderSize(localHeader.nameSize, localHeader.extraSize);
        if (localHeaderSize == 0) {
            return false;
        }
        ZipPos descPos = 0;
        ZIPPOS_ADD_AND_CHECK_OVERFLOW(zipEntry.localHeaderOffset, localHeaderSize, descPos);
        ZIPPOS_ADD_AND_CHECK_OVERFLOW(descPos, zipEntry.compressedSize, descPos);

        if (fseek(file_, descPos, SEEK_SET) != 0) {
            HILOG_ERROR(HILOG_MODULE_APP,
                "check local header seek datadesc failed, error: %{public}s", strerror(errno));
            return false;
        }

        if (fread(&dataDesc, sizeof(DataDesc), FILE_READ_COUNT, file_) != FILE_READ_COUNT) {
            HILOG_ERROR(HILOG_MODULE_APP, "check local header read datadesc failed, error: %{public}s",
                strerror(errno));
            return false;
        }

        if (dataDesc.signature != DATA_DESC_SIGNATURE) {
            HILOG_ERROR(HILOG_MODULE_APP, "check local header check datadesc signature failed");
            return false;
        }

        crcLocal = dataDesc.crc;
        compressedLocal = dataDesc.compressedSize;
        uncompressedLocal = dataDesc.uncompressedSize;
    } else {
        crcLocal = localHeader.crc;
        compressedLocal = localHeader.compressedSize;
        uncompressedLocal = localHeader.uncompressedSize;
    }

    if ((zipEntry.crc != crcLocal) ||
        (zipEntry.compressedSize != compressedLocal) ||
        (zipEntry.uncompressedSize != uncompressedLocal)) {
        HILOG_ERROR(HILOG_MODULE_APP, "check local header compressed size corrupted");
        return false;
    }

    return true;
}

bool ZipFile::CheckCoherencyLocalHeader(const ZipEntry &zipEntry, uint16_t &extraSize) const
{
    LocalHeader localHeader = {};

    if (zipEntry.localHeaderOffset >= fileLength_) {
        HILOG_ERROR(HILOG_MODULE_APP, "check local file header offset is overflow %{public}d",
            zipEntry.localHeaderOffset);
        return false;
    }
    if (fseek(file_, zipEntry.localHeaderOffset, SEEK_SET) != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "check local header seek failed, error: %{public}s", strerror(errno));
        return false;
    }
    if (fread(&localHeader, sizeof(LocalHeader), FILE_READ_COUNT, file_) != FILE_READ_COUNT) {
        HILOG_ERROR(HILOG_MODULE_APP, "check local header read localheader failed, error: %{public}s",
            strerror(errno));
        return false;
    }
    if ((localHeader.signature != LOCAL_HEADER_SIGNATURE) ||
        (zipEntry.compressionMethod != localHeader.compressionMethod)) {
        HILOG_ERROR(HILOG_MODULE_APP, "check local header signature or compressionMethod failed");
        return false;
    }
    // current only support store and Z_DEFLATED method
    if ((zipEntry.compressionMethod != Z_DEFLATED) &&
        (zipEntry.compressionMethod != 0)) {
        HILOG_ERROR(HILOG_MODULE_APP, "check local header compressionMethod(%{public}d) not support",
            zipEntry.compressionMethod);
        return false;
    }

    std::string fileName;
    fileName.reserve(MAX_FILE_NAME);
    fileName.resize(MAX_FILE_NAME - 1);
    size_t fileLength = (localHeader.nameSize >= MAX_FILE_NAME) ? (MAX_FILE_NAME - 1) : localHeader.nameSize;
    if (fileLength != zipEntry.fileName.length()) {
        HILOG_ERROR(HILOG_MODULE_APP, "check local header file name size failed");
        return false;
    }
    if (fread(&(fileName[0]), fileLength, FILE_READ_COUNT, file_) != FILE_READ_COUNT) {
        HILOG_ERROR(HILOG_MODULE_APP, "check local header read file name failed, error: %{public}s", strerror(errno));
        return false;
    }
    fileName.resize(fileLength);
    if (zipEntry.fileName != fileName) {
        HILOG_ERROR(HILOG_MODULE_APP, "check local header file name corrupted");
        return false;
    }

    if (!CheckDataDesc(zipEntry, localHeader)) {
        return false;
    }

    extraSize = localHeader.extraSize;
    return true;
}

bool ZipFile::SeekToEntryStart(const ZipEntry &zipEntry, const uint16_t extraSize) const
{
    ZipPos startOffset = zipEntry.localHeaderOffset;
    // get data offset, add signature+localheader+namesize+extrasize
    size_t localHeaderSize = GetLocalHeaderSize(zipEntry.fileName.length(), extraSize);
    if (localHeaderSize == 0) {
        return false;
    }
    ZipPos zipEntryPos = 0;
    ZIPPOS_ADD_AND_CHECK_OVERFLOW(startOffset, localHeaderSize, startOffset);
    ZIPPOS_ADD_AND_CHECK_OVERFLOW(startOffset, zipEntry.compressedSize, zipEntryPos);
    if (zipEntryPos > fileLength_) {
        HILOG_ERROR(HILOG_MODULE_APP, "seek to entry start failed, startOffset(%{public}lld) + entryCompressedSize"
            "(%{public}ud) > fileLength(%{public}llu)", startOffset, zipEntry.compressedSize, fileLength_);
        return false;
    }
    HILOG_INFO(HILOG_MODULE_APP, "seek to entry start 0x%{public}08llx", startOffset);
    if (fseek(file_, startOffset, SEEK_SET) != 0) {
        HILOG_ERROR(HILOG_MODULE_APP, "seek failed, error: %{public}s", strerror(errno));
        return false;
    }
    return true;
}

bool ZipFile::UnzipWithStore(const ZipEntry &zipEntry, const uint16_t extraSize, std::ostream &dest) const
{
    HILOG_INFO(HILOG_MODULE_APP, "unzip with store");
    if (!SeekToEntryStart(zipEntry, extraSize)) {
        return false;
    }

    uint32_t remainSize = zipEntry.compressedSize;
    std::string readBuffer;
    readBuffer.reserve(UNZIP_BUF_OUT_LEN);
    readBuffer.resize(UNZIP_BUF_OUT_LEN - 1);
    while (remainSize > 0) {
        size_t readBytes;
        size_t readLen = (remainSize > UNZIP_BUF_OUT_LEN) ? UNZIP_BUF_OUT_LEN : remainSize;
        readBytes = fread(&(readBuffer[0]), sizeof(Byte), readLen, file_);
        if (readBytes == 0) {
            HILOG_ERROR(HILOG_MODULE_APP, "unzip store read failed, error: %{public}s", strerror(errno));
            return false;
        }
        remainSize -= readBytes;
        dest.write(&(readBuffer[0]), readBytes);
    }
    HILOG_INFO(HILOG_MODULE_APP, "unzip with store success");
    return true;
}

bool ZipFile::InitZStream(z_stream &zstream) const
{
    // init zlib stream
    if (memset_s(&zstream, sizeof(z_stream), 0, sizeof(z_stream))) {
        HILOG_ERROR(HILOG_MODULE_APP, "unzip stream buffer init failed");
        return false;
    }
    int32_t zlibErr = inflateInit2(&zstream, -MAX_WBITS);
    if (zlibErr != Z_OK) {
        HILOG_ERROR(HILOG_MODULE_APP, "unzip inflated init failed");
        return false;
    }

    BytePtr bufOut = new Byte[UNZIP_BUF_OUT_LEN];
    if (bufOut == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "unzip inflated new out buffer failed");
        return false;
    }

    BytePtr bufIn = new Byte[UNZIP_BUF_IN_LEN];
    if (bufIn == nullptr) {
        HILOG_ERROR(HILOG_MODULE_APP, "unzip inflated new in buffer failed");
        delete[] bufOut;
        return false;
    }
    zstream.next_out = bufOut;
    zstream.next_in = bufIn;
    zstream.avail_out = UNZIP_BUF_OUT_LEN;
    return true;
}

bool ZipFile::ReadZStream(const BytePtr &buffer, z_stream &zstream, uint32_t &remainCompressedSize) const
{
    if (zstream.avail_in == 0) {
        size_t readBytes;
        size_t remainBytes = (remainCompressedSize > UNZIP_BUF_IN_LEN) ? UNZIP_BUF_IN_LEN : remainCompressedSize;
        readBytes = fread(buffer, sizeof(Byte), remainBytes, file_);
        if (readBytes == 0) {
            HILOG_ERROR(HILOG_MODULE_APP, "unzip inflated read failed, error: %{public}s", strerror(errno));
            return false;
        }

        remainCompressedSize -= readBytes;
        zstream.avail_in = readBytes;
        zstream.next_in = buffer;
    }
    return true;
}

bool ZipFile::UnzipWithInflated(const ZipEntry &zipEntry, const uint16_t extraSize, std::ostream &dest) const
{
    HILOG_INFO(HILOG_MODULE_APP, "unzip with inflated");
    z_stream zstream;
    if (!SeekToEntryStart(zipEntry, extraSize)) {
        return false;
    }
    if (!InitZStream(zstream)) {
        return false;
    }
    BytePtr bufIn = zstream.next_in;
    BytePtr bufOut = zstream.next_out;

    bool ret = true;
    int32_t zlibErr = Z_OK;
    uint32_t remainCompressedSize = zipEntry.compressedSize;
    size_t inflateLen = 0;
    uint8_t errorTimes = 0;

    while ((remainCompressedSize > 0) || (zstream.avail_in > 0)) {
        if (!ReadZStream(bufIn, zstream, remainCompressedSize)) {
            ret = false;
            break;
        }

        zlibErr = inflate(&zstream, Z_SYNC_FLUSH);
        if (zlibErr < Z_OK) {
            HILOG_ERROR(HILOG_MODULE_APP, "unzip inflated inflate, error: %{public}d", zlibErr);
            if (zstream.msg != nullptr) {
                HILOG_ERROR(HILOG_MODULE_APP, "err msg: %{public}s", zstream.msg);
            }
            ret = false;
            break;
        }

        inflateLen = UNZIP_BUF_OUT_LEN - zstream.avail_out;
        if (inflateLen > 0) {
            dest.write((const char*)bufOut, inflateLen);
            zstream.next_out = bufOut;
            zstream.avail_out = UNZIP_BUF_OUT_LEN;
            errorTimes = 0;
        } else {
            errorTimes++;
        }

        if (errorTimes >= INFLATE_ERROR_TIMES) {
            HILOG_ERROR(HILOG_MODULE_APP, "unzip inflated data is abnormal!");
            ret = false;
            break;
        }
    }

    // free all dynamically allocated data structures except the next_in and next_out for this stream.
    zlibErr = inflateEnd(&zstream);
    if (zlibErr != Z_OK) {
        HILOG_ERROR(HILOG_MODULE_APP, "unzip inflateEnd error, error: %{public}d", zlibErr);
        ret = false;
    }
    HILOG_INFO(HILOG_MODULE_APP, "unzip with inflated success");

    delete[] bufOut;
    delete[] bufIn;
    return ret;
}

bool ZipFile::ExtractFile(const std::string &file, std::ostream &dest) const
{
    HILOG_INFO(HILOG_MODULE_APP, "extract file %{public}s", file.c_str());
    ZipEntry zipEntry;
    if (!GetEntry(file, zipEntry)) {
        HILOG_ERROR(HILOG_MODULE_APP, "extract file: not find file");
        return false;
    }

    uint16_t extraSize = 0;
    if (!CheckCoherencyLocalHeader(zipEntry, extraSize)) {
        return false;
    }

    bool ret = true;
    if (zipEntry.compressionMethod == 0) {
        ret = UnzipWithStore(zipEntry, extraSize, dest);
    } else {
        ret = UnzipWithInflated(zipEntry, extraSize, dest);
    }
    return ret;
}
}
