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
#ifndef MAPLE_UTIL_INCLUDE_NAME_MANGLER_H
#define MAPLE_UTIL_INCLUDE_NAME_MANGLER_H
#include <string>
#include <vector>

// This is a general name mangler which is shared between maple compiler and runtime.
// maple-compiler-specific data structure may NOT be used here.
namespace NameMangler {

#define TO_STR(s)  TO_STR2(s)
#define TO_STR2(s) #s


#define VTAB_PREFIX               __vtb_
#define ITAB_PREFIX               __itb_
#define ITAB_CONFLICT_PREFIX      __itbC_
#define CLASSINFO_PREFIX          __cinf_
#define CLASSINFO_RO_PREFIX       __classinforo__
#define SUPERCLASSINFO_PREFIX     __superclasses__
#define PRIMITIVECLASSINFO_PREFIX __pinf_
#define CLASS_INIT_BRIDGE_PREFIX  __ClassInitBridge__
#define GCTIB_PREFIX              MCC_GCTIB__
#define JARRAY_PREFIX             A

#define VTAB_PREFIX_STR               TO_STR(VTAB_PREFIX)
#define ITAB_PREFIX_STR               TO_STR(ITAB_PREFIX)
#define ITAB_CONFLICT_PREFIX_STR      TO_STR(ITAB_CONFLICT_PREFIX)
#define CLASSINFO_PREFIX_STR          TO_STR(CLASSINFO_PREFIX)
#define CLASSINFO_RO_PREFIX_STR       TO_STR(CLASSINFO_RO_PREFIX)
#define SUPERCLASSINFO_PREFIX_STR     TO_STR(SUPERCLASSINFO_PREFIX)
#define PRIMITIVECLASSINFO_PREFIX_STR TO_STR(PRIMITIVECLASSINFO_PREFIX)
#define CLASS_INIT_BRIDGE_PREFIX_STR  TO_STR(CLASS_INIT_BRIDGE_PREFIX)
#define GCTIB_PREFIX_STR              TO_STR(GCTIB_PREFIX)
#define JARRAY_PREFIX_STR             TO_STR(JARRAY_PREFIX)

// Names of all compiler-generated tables and accessed by runtime
static constexpr const char kMuidPrefixStr[] = "__muid_";
static constexpr const char kMuidFuncDefTabPrefixStr[] = "__muid_func_def_tab";
static constexpr const char kMuidFuncDefOrigTabPrefixStr[] = "__muid_func_def_orig_tab";
static constexpr const char kMuidFuncInfTabPrefixStr[] = "__muid_func_inf_tab";
static constexpr const char kMuidFuncMuidIdxTabPrefixStr[] = "__muid_func_muid_idx_tab";
static constexpr const char kMuidDataDefTabPrefixStr[] = "__muid_data_def_tab";
static constexpr const char kMuidDataDefOrigTabPrefixStr[] = "__muid_data_def_orig_tab";
static constexpr const char kMuidFuncUndefTabPrefixStr[] = "__muid_func_undef_tab";
static constexpr const char kMuidDataUndefTabPrefixStr[] = "__muid_data_undef_tab";
static constexpr const char kMuidFuncDefMuidTabPrefixStr[] = "__muid_func_def_muid_tab";
static constexpr const char kMuidDataDefMuidTabPrefixStr[] = "__muid_data_def_muid_tab";
static constexpr const char kMuidFuncUndefMuidTabPrefixStr[] = "__muid_func_undef_muid_tab";
static constexpr const char kMuidDataUndefMuidTabPrefixStr[] = "__muid_data_undef_muid_tab";
static constexpr const char kMuidVtabPrefixStr[] = "__muid_vtab";
static constexpr const char kMuidItabPrefixStr[] = "__muid_itab";
static constexpr const char kMuidVtabOffsetPrefixStr[] = "__muid_vtab_offset_tab";
static constexpr const char kMuidFieldOffsetPrefixStr[] = "__muid_field_offset_tab";
static constexpr const char kMuidVtabOffsetKeyPrefixStr[] = "__muid_vtable_offset_key_tab";
static constexpr const char kMuidFieldOffsetKeyPrefixStr[] = "__muid_field_offset_key_tab";
static constexpr const char kMuidValueOffsetPrefixStr[] = "__muid_offset_value_table";
static constexpr const char kMuidLocalClassInfoStr[] = "__muid_local_classinfo_tab";
static constexpr const char kMuidSuperclassPrefixStr[] = "__muid_superclass";
static constexpr const char kMuidGlobalRootlistPrefixStr[] = "__muid_globalrootlist";
static constexpr const char kMuidClassMetadataPrefixStr[] = "__muid_classmetadata";
static constexpr const char kMuidClassMetadataBucketPrefixStr[] = "__muid_classmetadata_bucket";
static constexpr const char kMuidJavatextPrefixStr[] = "__muid_java_text";
static constexpr const char kMuidRangeTabPrefixStr[] = "__muid_range_tab";
static constexpr const char kMuidConststrPrefixStr[] = "__muid_conststr";
static constexpr const char kVtabOffsetTabStr[] = "__vtable_offset_table";
static constexpr const char kFieldOffsetTabKeyStr[] = "__field_offset_key_table";
static constexpr const char kFieldOffsetTabStr[] = "__field_offset_table";
static constexpr const char kVtableKeyOffsetTabStr[] = "__vtable_offset_key_table";
static constexpr const char kVtableOffsetTabKeyStr[] = "__vtable_offset_key_table";
static constexpr const char kFieldKeyOffsetTabStr[] = "__field_offset_table";
static constexpr const char kOffsetTabStr[] = "__offset_value_table";
static constexpr const char kLocalClassInfoStr[] = "__local_classinfo_table";
static constexpr const char kMethodsInfoPrefixStr[] = "__methods_info__";
static constexpr const char kMethodsInfoCompactPrefixStr[] = "__methods_infocompact__";
static constexpr const char kFieldsInfoPrefixStr[] = "__fields_info__";
static constexpr const char kFieldsInfoCompactPrefixStr[] = "__fields_infocompact__";
static constexpr const char kRegJNITabPrefixStr[] = "__reg_jni_tab";
static constexpr const char kRegJNIFuncTabPrefixStr[] = "__reg_jni_func_tab";
static constexpr const char kReflectionStrtabPrefixStr[] = "__reflection_strtab";
static constexpr const char kReflectionStartHotStrtabPrefixStr[] = "__reflection_start_hot_strtab";
static constexpr const char kReflectionBothHotStrTabPrefixStr[] = "__reflection_both_hot_strtab";
static constexpr const char kReflectionRunHotStrtabPrefixStr[] = "__reflection_run_hot_strtab";
static constexpr const char kReflectionNoEmitStrtabPrefixStr[] = "__reflection_no_emit_strtab";
static constexpr const char kMarkMuidFuncDefStr[] = "muid_func_def:";
static constexpr const char kMarkMuidFuncUndefStr[] = "muid_func_undef:";
static constexpr const char kGcRootList[] = "gcRootNewList";
static constexpr const char kDecoupleOption[] = "__decouple_option";
static constexpr const char kDecoupleStr[] = "__decouple";
static constexpr const char kCompilerVersionNum[] = "__compilerVersionNum";
static constexpr const char kCompilerVersionNumStr[] = "__compilerVersionNumTab";

static constexpr const char kStaticFieldNamePrefixStr[] = "__static_field_name";
static constexpr const char kPackageNameSplitterStr[] = "_2F";
static constexpr const char kFileNameSplitterStr[] = "$$";
static constexpr const char kNameSplitterStr[] = "_7C";  // 7C is the ascii code for |
static constexpr const char kRigthBracketStr[] = "_29";  // 29 is the ascii code for )
static constexpr const char kClassNameSplitterStr[] = "_3B_7C";
static constexpr const char kJavaLangClassStr[] = "Ljava_2Flang_2FClass_3B";
static constexpr const char kJavaLangObjectStr[] = "Ljava_2Flang_2FObject_3B";
static constexpr const char kJavaLangObjectStrJVersion[] = "Ljava/lang/Object;";
static constexpr const char kJavaLangStringStr[] = "Ljava_2Flang_2FString_3B";
static constexpr const char kJavaLangExceptionStr[] = "Ljava_2Flang_2FException_3B";
static constexpr const char kThrowClassStr[] = "Ljava_2Flang_2FThrowable_3B";
static constexpr const char kReflectionClassesPrefixStr[] = "Ljava_2Flang_2Freflect_2F";
static constexpr const char kClassMetadataTypeName[] = "__class_meta__";
static constexpr const char kPtrPrefixStr[] = "_PTR";
static constexpr const char kClassINfoPtrPrefixStr[] = "_PTR__cinf_";
static constexpr const char kArrayClassInfoPrefixStr[] = "__cinf_A";
static constexpr const char kShadowClassName[] = "shadow_24__klass__";
static constexpr const char kClinitSuffix[] = "_7C_3Cclinit_3E_7C_28_29V";
static constexpr const char kCinitStr[] = "_7C_3Cinit_3E_7C_28";
static constexpr const char kClinitSubStr[] = "7C_3Cinit_3E_7C";

static constexpr const char kFunctionLayoutStr[] = "__func_layout__";

static constexpr const char kFunctionProfileTabPrefixStr[] = "__muid_profile_func_tab";

static constexpr const char kBindingProtectedRegionStr[] = "__BindingProtectRegion__";

// Serve as a global flag to indicate whether frequent strings have been compressed
extern bool doCompression;

// Return the input string if the compression is not on; otherwise, return its compressed version
std::string GetInternalNameLiteral(const char *name);
std::string GetOriginalNameLiteral(const char *name);

std::string EncodeName(const std::string &name);
std::string EncodeName(const char *name);
std::string DecodeName(const std::string &name);
std::string DecodeName(const char *name);
void DecodeMapleNameToJavaDescriptor(const std::string &nameIn, std::string &nameOut);

std::string NativeJavaName(const char *name, bool overloaded = true);

__attribute__((visibility("default"))) unsigned UTF16ToUTF8(std::string &str, const std::u16string &str16,
                                                            unsigned short num = 0, bool isbigendian = false);
__attribute__((visibility("default"))) unsigned UTF8ToUTF16(std::u16string &str16, const std::string &str,
                                                            unsigned short num = 0, bool isbigendian = false);
void GetUnsignedLeb128Encode(std::vector<uint8_t> &dest, uint32_t value);
uint32_t GetUnsignedLeb128Decode(const uint8_t **data);
uint64_t GetUleb128Encode(uint64_t val);
uint64_t GetSleb128Encode(int64_t val);
uint64_t GetUleb128Decode(uint64_t val);
int64_t  GetSleb128Decode(uint64_t val);
size_t GetUleb128Size(uint64_t val);
size_t GetSleb128Size(int32_t val);

} // namespace NameMangler

#endif
