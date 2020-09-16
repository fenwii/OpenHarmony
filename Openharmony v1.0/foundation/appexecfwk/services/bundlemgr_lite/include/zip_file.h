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

#ifndef OHOS_BUNDLE_ZIP_FILE_H
#define OHOS_BUNDLE_ZIP_FILE_H

#include <map>
#include <string>
#include <vector>

#include "stdint.h"
#include "unzip.h"

namespace OHOS {
using ZipPos = ZPOS64_T;
using CentralDirEntry = struct CentralDirEntry;
using LocalHeader = struct LocalHeader;
using EndDir = struct EndDir;
using DataDesc = struct DataDesc;
using ZipEntry = struct ZipEntry;
using ZipEntryMap = std::map<std::string, ZipEntry>;
using BytePtr = Byte *;

// Local file header: descript in APPNOTE-6.3.4
//    local file header signature     4 bytes  (0x04034b50)
//    version needed to extract       2 bytes
//    general purpose bit flag        2 bytes
//    compression method              2 bytes  10
//    last mod file time              2 bytes
//    last mod file date              2 bytes
//    crc-32                          4 bytes
//    compressed size                 4 bytes  22
//    uncompressed size               4 bytes
//    file name length                2 bytes
//    extra field length              2 bytes  30
struct __attribute__((packed)) LocalHeader {
    uint32_t signature = 0;
    uint16_t versionNeeded = 0;
    uint16_t flags = 0;
    uint16_t compressionMethod = 0;
    uint16_t modifiedTime = 0;
    uint16_t modifiedDate = 0;
    uint32_t crc = 0;
    uint32_t compressedSize = 0;
    uint32_t uncompressedSize = 0;
    uint16_t nameSize = 0;
    uint16_t extraSize = 0;
};

// central file header
//    Central File header:
//    central file header signature   4 bytes  (0x02014b50)
//    version made by                 2 bytes
//    version needed to extract       2 bytes
//    general purpose bit flag        2 bytes  10
//    compression method              2 bytes
//    last mod file time              2 bytes
//    last mod file date              2 bytes
//    crc-32                          4 bytes  20
//    compressed size                 4 bytes
//    uncompressed size               4 bytes
//    file name length                2 bytes  30
//    extra field length              2 bytes
//    file comment length             2 bytes
//    disk number start               2 bytes
//    internal file attributes        2 bytes
//    external file attributes        4 bytes
//    relative offset of local header 4 bytes 46byte
struct __attribute__((packed)) CentralDirEntry {
    uint32_t signature = 0;
    uint16_t versionMade = 0;
    uint16_t versionNeeded = 0;
    uint16_t flags = 0; // general purpose bit flag
    uint16_t compressionMethod = 0;
    uint16_t modifiedTime = 0;
    uint16_t modifiedDate = 0;
    uint32_t crc = 0;
    uint32_t compressedSize = 0;
    uint32_t uncompressedSize = 0;
    uint16_t nameSize = 0;
    uint16_t extraSize = 0;
    uint16_t commentSize = 0;
    uint16_t diskNumStart = 0;
    uint16_t internalAttr = 0;
    uint32_t externalAttr = 0;
    uint32_t localHeaderOffset = 0;
};

struct __attribute__((packed)) EndDir {
    uint32_t signature = 0;
    uint16_t numDisk = 0;
    uint16_t startDiskOfCentralDir = 0;
    uint16_t totalEntriesInThisDisk = 0;
    uint16_t totalEntries = 0;
    uint32_t sizeOfCentralDir = 0;
    uint32_t offset = 0;
    uint16_t commentLen = 0;
};

// Data descriptor:
//    data descriptor signature       4 bytes  (0x06054b50)
//    crc-32                          4 bytes
//    compressed size                 4 bytes
//    uncompressed size               4 bytes
// This descriptor MUST exist if bit 3 of the general purpose bit flag is set (see below).
// It is byte aligned and immediately follows the last byte of compressed data.
struct __attribute__((packed)) DataDesc {
    uint32_t signature = 0;
    uint32_t crc = 0;
    uint32_t compressedSize = 0;
    uint32_t uncompressedSize = 0;
};

struct ZipEntry {
    ZipEntry() = default;
    explicit ZipEntry(const CentralDirEntry &centralEntry);
    ~ZipEntry() = default;

    uint16_t compressionMethod = 0;
    uint32_t uncompressedSize = 0;
    uint32_t compressedSize = 0;
    uint32_t localHeaderOffset = 0;
    uint32_t crc = 0;
    uint16_t flags = 0;
    std::string fileName;
};

// zip file extract class for bundle format.
class ZipFile {
public:
    explicit ZipFile(const std::string &pathName);
    ~ZipFile();

    bool Open();
    void Close();
    // set this zip content start offset and length in the zip file form pathName.
    void SetContentLocation(ZipPos start, size_t length);

    const ZipEntryMap &GetAllEntries() const;
    bool GetEntry(const std::string &entryName, ZipEntry &resultEntry) const;
    bool ExtractFile(const std::string &file, std::ostream &dest) const;
    const std::vector<std::string> &GetFileNames() const;

private:
    bool CheckEndDir(const EndDir &endDir) const;
    bool ParseEndDirectory();
    bool ParseAllEntries();
    size_t GetLocalHeaderSize(const uint16_t nameSize = 0, const uint16_t extraSize = 0) const;
    bool CheckDataDesc(const ZipEntry &zipEntry, const LocalHeader &localHeader) const;
    bool CheckCoherencyLocalHeader(const ZipEntry &zipEntry, uint16_t &extraSize) const;
    bool UnzipWithStore(const ZipEntry &zipEntry, const uint16_t extraSize, std::ostream &dest) const;
    bool UnzipWithInflated(const ZipEntry &zipEntry, const uint16_t extraSize, std::ostream &dest) const;
    bool SeekToEntryStart(const ZipEntry &zipEntry, const uint16_t extraSize) const;
    bool InitZStream(z_stream &zstream) const;
    bool ReadZStream(const BytePtr &buffer, z_stream &zstream, uint32_t &remainCompressedSize) const;

private:
    std::string pathName_;
    FILE* file_ = nullptr;
    EndDir endDir_;
    ZipEntryMap entriesMap_;
    // offset of central directory relative to zip file.
    ZipPos centralDirPos_ = 0;
    // this zip content length in the zip file.
    ZipPos fileLength_ = 0;
    // entryName vector
    std::vector<std::string> fileNames_;
    bool isOpen_ = false;
};
} // namespace OHOS
#endif // OHOS_BUNDLE_ZIP_FILE_H