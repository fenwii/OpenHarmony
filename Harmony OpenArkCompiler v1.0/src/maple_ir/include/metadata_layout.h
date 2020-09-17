/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reserved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *     http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
 */
#ifndef MAPLE_IR_INCLUDE_METADATA_LAYOUT_H
#define MAPLE_IR_INCLUDE_METADATA_LAYOUT_H
#include <cstdlib>

// metadata layout is shared between maple compiler and runtime, thus not in namespace maplert
#ifdef __cplusplus
extern "C" {
#endif

// data types for address offset
#ifdef USE_32BIT_REF
using AddrOffset = int32_t;
#else
using AddrOffset = int64_t;
#endif

// some of the reference field of metadata is stored as relative offset
// for example, declaring class of Fields/Methods
// which can be negative
#ifdef USE_32BIT_REF
using MetaRef = uint32_t;      // consistent with reffield_t in address.h
using MetaRefOffset = int32_t;
#else
using MetaRef = uintptr_t;     // consistent with reffield_t in address.h
using MetaRefOffset = int64_t;
#endif // USE_32BIT_REF

using MetadataRelOffset = MetaRefOffset;

static inline void *DecodeValueAsRelOffset32(const int32_t *addr) {
  intptr_t realAddr = reinterpret_cast<intptr_t>(addr) + *addr;
  return reinterpret_cast<void*>(realAddr);
}

static inline void *DecodeValueAsRelOffset64(const int64_t *addr) {
  intptr_t realAddr = reinterpret_cast<intptr_t>(addr) + *addr;
  return reinterpret_cast<void*>(realAddr);
}

static inline void *DecodeValueAsMetadataRelOffset(const MetadataRelOffset *addr) {
  intptr_t realAddr = reinterpret_cast<intptr_t>(addr) + *addr;
  return reinterpret_cast<void*>(realAddr);
}

static inline void EncodeValueAsRelOffset32(const void *value, int32_t *addr) {
  int32_t offset = reinterpret_cast<intptr_t>(value) - reinterpret_cast<intptr_t>(addr);
  *addr = offset;
  if (DecodeValueAsRelOffset32(addr) != value) {
    std::abort();
  }
}

static inline void EncodeValueAsRelOffset64(const void *value, int64_t *addr) {
  int64_t offset = reinterpret_cast<intptr_t>(value) - reinterpret_cast<intptr_t>(addr);
  *addr = offset;
  if (DecodeValueAsRelOffset64(addr) != value) {
    std::abort();
  }
}

static inline void EncodeValueAsMetadataRelOffset(const void *value, MetadataRelOffset *addr) {
  MetadataRelOffset offset = reinterpret_cast<intptr_t>(value) - reinterpret_cast<intptr_t>(addr);
  *addr = offset;
  if (DecodeValueAsMetadataRelOffset(addr) != value) {
    std::abort();
  }
}

inline void MRTSetMetaRefOffset(MetaRefOffset *pOffset, char *addr) {
  (*pOffset) = (MetaRefOffset)(addr - reinterpret_cast<char*>(pOffset));
}

inline void *MRTGetAddressFromMetaRefOffset(MetaRefOffset *pOffset) {
  return reinterpret_cast<void*>(reinterpret_cast<char*>(pOffset) + (*pOffset));
}

struct FieldInfo {
  AddrOffset offset;
  uint32_t mod;
  uint16_t flag;
  uint16_t index;
  AddrOffset typeName;
  int32_t fieldName;
  int32_t annotation;
  int64_t declaringClass;
};

struct MethodInfo {
  AddrOffset methodInVtabIndex;
  AddrOffset addr;
  AddrOffset declaringClass;
  uint32_t mod;
  int32_t methodName;
  int32_t signatureName;
  int32_t annotationValue;
  uint16_t flag;
  uint16_t argSize;
#ifndef USE_32BIT_REF
  uint32_t paddind;
#endif
};

// MethodDesc contains MethodMetadata and stack map
struct MethodDesc {
  // relative offset for method metadata relative to current PC.
  // method metadata is in compact format if this offset is odd.
  uint32_t metadataOffset;

  uint16_t localRefOffset;
  uint16_t localRefNumber;

  // stack map for a methed might be placed here
};

// Note: class init in maplebe and cg is highly dependent on this type.
// update aarch64rtsupport.h if you modify this definition.
struct ClassMetadataRO {
  char *className;
  int64_t fields;  // point to info of fields
  int64_t methods; // point to info of methods
  union {  // Element classinfo of array, others parent classinfo
    struct ClassMetadata **superclass;
    struct ClassMetadata *componentClass;
  } familyClass;

  uint16_t numOfFields;
  uint16_t numOfMethods;

#ifndef USE_32BIT_REF
  uint16_t flag;
  uint16_t numOfSuperclasses;
  uint32_t padding;
#endif // !USE_32BIT_REF

  uint32_t mod; // 32 bit 0X00000000    modifier: 0x00FFFFFF   override: 0x80000000
  int32_t annotation;
  int32_t clinitAddr;
};

struct DexFile;
struct DexClassDef;
struct DexClassData;

struct ClassMetadata {
  // object common fields
  MetaRef shadow;  // point to classinfo of java/lang/Class
  int32_t monitor;

  // other fields
  uint16_t clIndex; // 8bit ClassLoader index, used for querying the address of related ClassLoader instance.
  union {
    uint16_t objSize;
    uint16_t componentSize;
  } sizeInfo;

#ifdef USE_32BIT_REF // for alignment purpose
  uint16_t flag;
  uint16_t numOfSuperclasses;
#endif // USE_32BIT_REF

  void *iTable;  // iTable of current class, used for virtual call, will insert the content into classinfo
  void *vTable;  // vTable of current class, used for interface call, will insert the content into classinfo
  void *gctib; // for rc
  ClassMetadataRO *classInfoRo;

  union {
    intptr_t initState;    // if class is not initialized
    void *staticFields;    // if class is already initialized
  }; // class init state, this field must be accessed atomically.
};

static inline intptr_t ClassMetadataOffsetOfInitFlag() {
  ClassMetadata *base = reinterpret_cast<ClassMetadata*>(0);
  return reinterpret_cast<intptr_t>(&(base->initState));
}

static inline intptr_t ClassMetadataOffsetOfStaticFields() {
  ClassMetadata *base = reinterpret_cast<ClassMetadata*>(0);
  return reinterpret_cast<intptr_t>(&(base->staticFields));
}

#ifdef __cplusplus
}
#endif

// function to set Class/Field/Method metadata's shadow field to avoid type conversion
// Note 1: here we don't do NULL-check and type-compatibility check
// NOte 2: C should be of jclass/ClassMetata* type
template<typename M, typename C>
static inline void MRTSetMetadataShadow(M *meta, C cls) {
  meta->shadow = (MetaRef)(uintptr_t)cls;
}

// help function to set Field/Method's declaringclass field to avoid type conversion
// Note: here we don't do NULL-check and type-compatibility check
// Note: Declaring class is encoded as relative offset which can be negative
// Note: here declaring class is stored as an offset rather than a raw pointer
template<typename M, typename C>
static inline void MRTSetMetadataDeclaringClass(M *meta, C cls) {
  meta->declaringclass = (MetaRefOffset)(intptr_t)cls;
}

#endif // METADATA_LAYOUT_H
