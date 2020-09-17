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
#ifndef MAPLE_UTIL_INCLUDE_MPL_LOGGING_H
#define MAPLE_UTIL_INCLUDE_MPL_LOGGING_H

#include <string>

/***************************************************************************

   This file defines the APIs that govern all messaging-styled output from
   a running program under MAPLE, which can be a compiler or a runtime component.

   There are two overall classes of messages:

   (1) Those of interest only to developers, and thus should be suppressed in the
   production release version of the software.  The message content will include
   the source file and line number of the trigger point of the message.

   (2) Those intended to be visible to users of the software in general,  in
   addition to the developers.

   Messages are divided into 6 types, or levels, from 0 to 5.  Conceptually,
   the lower the level, the higher the frequency of occurrences, the larger the
   output volume, the smaller the audience of interest and the more often they need
   to be filtered out. In addition, the higher the level, the greater the severity.

   Level 0 (DBG) - These are messages for debugging purposes, used by the
   developer during development to debug his code.

   Level 1 (LOG) - These are log messages, also for helping the developer in
   debugging, but at a higher level of algorithmic operation.

   Level 2 (INFO) - These provide information that are of general usefulness in
   the normal operation of the SW.

   Level 3 (WARN) - These provide warning messages.

   Level 4 (ERR) - These provide error messages.

   Level 5 (FATAL) - These indicate errors of such severity that the program r
   execution cannot continue.

   DBG and LOG are only for developers' use.  INFO, WARN, ERR and FATAL are
   intended for general visibility.  There is an additional type of ERR that
   designate developer errors that arise out of checking code inserted by the
   developers, which has the following 4 usage patterns:

   CHECK - If the specified program condition is not satisfied, output the error
   message. The program will continue execution.

   DCHECK - Same as CHECK, but the check is suppressed in the release version of
   the SW.

   CHECK_FATAL - If the specified program condition is not satisfied, output the error
   message. The program will stop execution at that point.

   ASSERT - Same as CHECK_FATAL, but the check is suppressed in the release version of
   the SW.

   The macro setting DEBUG=1 picks developer and DEBUG=0 picks release builds.

   the macro PRINT_LEVEL_DEV is a filter for DBG messages in developer builds.
   When PRINT_LEVEL_DEV is set to kLlLog, DBG messages are not printed.

   Instantiated object c_logInfo, of class LogInfo, provides finer control of
   the logging behavior during execution.  Use emitLogDevice() to change the
   message destination.  Use setLogMode() to change the verbosity of the messages.

   In the case of DBG and LOG, the message needs to print the name of the SW
   component as the volume of messages can be huge.  Use enum LOG_TAGS to define
   the component ID and its name string.

   Since INFO, WARN, ERR and FATAL are for general consumption, each message
   should provide an number code under enum LogNumberCode.

   Following are usage examples for the 10 types of logging actions supported:

   GDB(LT_MPLME, "symbol %s SSA version %d made required during DSE",
    vers->origsym->name, vers->id);

   LOG(LT_MPLME, "deleting BB %d because it is unreachable", bb->id_.GetIdx());

   INFO(kLncInfo, "function %s inlined into %s", callee->name, caller->name);

   WARN(kLncWarn, "variable %s defined but never used", sym->name);

   ERR(kLncErr, "syntax error at file %s line %d", filename, lineno);

   FATAL(kLncFatal, "segmentation error");

   CHECK(tyidx < type_table.size(), "%d is not a valid type index", tyidx);

   DCHECK(tyidx < type_table.size(), "%d is not a valid type index", tyidx);

   CHECK_FATAL(tyidx < type_table.size(), "%d is not a valid type index", tyidx);

   ASSERT(tyidx < type_table.size(), "%d is not a valid type index", tyidx);

   Each of the above are mapped to one of the following 3 methods in class LogInfo:

   EmitLogForDev() - for DBG and LOG

   EmitLogForUser() - for INFO, WARN, ERR and FATAL

   EmitErrorMessage() - for CHECK, DCHECK, CHECK_FATAL and ASSERT

   DBG and LOG send their messages to stdout, and provide additional date and time
   information.  For the rest, the messages are sent to stderr.

   In debugging the program, the developer can set breakpoint in one of the above
   3 methods depending on the type of message. For ASSERT, abort() is called
   instead of exit(1) so that the program will not completely exit, to allow the
   developer to print stack trace and peruse the program environment at the point
   of the assertion.

***************************************************************************/

#include <cstdio>
#include <stdarg.h>
#include <sstream>
#include <iostream>

namespace maple {
extern class LogInfo logInfo;

enum LogLevel { kLlDbg, kLlLog, kLlInfo, kLlWarn, kLlErr, kLlFatal, kLlMax };

enum LogTags { kLtThread, kLtLooper, kLtAll };

enum LogMode {
  kLmSimple,
  kLmComplex,

  kLmMax
};

enum LogNumberCode {
  kLncInfo = 0,

  kLncWarn = 20,

  kLncErr = 40,

  kLncFatal = 60,

  kLncMax = 99
};

class LogInfo {
 public:
  static std::ostream &MapleLogger(LogLevel l = kLlLog);
  LogInfo &operator=(const LogInfo &p) = delete;
  LogInfo(const LogInfo &p) = delete;
  LogInfo() : outStream(stdout), outMode(kLmComplex) {}

  ~LogInfo() {
    fclose(outStream);
  }

  void SetLogDevice(FILE *stream) {
    outStream = stream;
  }

  void SetLogMode(LogMode lm) {
    outMode = lm;
  }

  void EmitLogForDevelop(enum LogTags tag, enum LogLevel ll, const char *file, const char *func, int line,
                         const char *fmt, ...);
  void EmitLogForUser(enum LogNumberCode num, enum LogLevel ll, const char *fmt, ...) const;
  void EmitLogForUser(enum LogNumberCode num, enum LogLevel ll, const std::string &message) const;
  void EmitErrorMessage(const char *cond, const char *file, unsigned int line, const char *fmt, ...) const;

 private:
  FILE *outStream;
  LogMode outMode;
};

#ifdef DEBUG
#define DEBUG_STMT(x) x
#define DEBUG_TEST 1
#define ENABLE_ASSERT 1
#else
#define DEBUG_STMT(x)
#define DEBUG_TEST 0
#define ENABLE_ASSERT 0
#endif  // DEBUG

// for developer
#define PRINT_LEVEL_DEV kLlLog

#define DBG(tag, fmt, ...)                                                                      \
  do {                                                                                          \
    if (PRINT_LEVEL_DEV <= kLlLog)                                                              \
      maple::logInfo.EmitLogForDev(tag, kLlLog, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__); \
  } while (0)
#define LOG(tag, fmt, ...)                                                                      \
  do {                                                                                          \
    if (PRINT_LEVEL_DEV <= kLlLog)                                                              \
      maple::logInfo.EmitLogForDev(tag, kLlLog, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__); \
  } while (0)
#define CHECK(cond, fmt, ...)                                                       \
  do {                                                                              \
    if (!(cond))                                                                    \
      maple::logInfo.EmitErrorMessage(#cond, __FILE__, __LINE__, fmt "\n", ##__VA_ARGS__); \
  } while (0)
#define DCHECK(cond, fmt, ...)                   \
  do {                                           \
    DEBUG_STMT(CHECK(cond, fmt, ##__VA_ARGS__)); \
  } while (0)

#define CHECK_FATAL(cond, fmt, ...)                                                 \
  do {                                                                              \
    if (!(cond)) {                                                                  \
      maple::logInfo.EmitErrorMessage(#cond, __FILE__, __LINE__, fmt "\n", ##__VA_ARGS__); \
      if (DEBUG_TEST)                                                               \
        abort();                                                                    \
      else                                                                          \
        exit(1);                                                                    \
    }                                                                               \
  } while (0)

#if ENABLE_ASSERT
#define ASSERT(cond, fmt, ...)                                                      \
  do {                                                                              \
    if (!(cond)) {                                                                  \
      maple::logInfo.EmitErrorMessage(#cond, __FILE__, __LINE__, fmt "\n", ##__VA_ARGS__); \
      abort();                                                                      \
    }                                                                               \
  } while (0)
#else
#define ASSERT(cond, fmt, ...)
#endif  // ENABLE_ASSERT

// for user
#define PRINT_LEVEL_USER kLlInfo

#define INFO(num, fmt, ...)                                     \
  do {                                                          \
    if (PRINT_LEVEL_USER <= kLlInfo)                            \
      maple::logInfo.EmitLogForUser(num, kLlInfo, fmt, ##__VA_ARGS__); \
  } while (0)
#define INFO_V(verbose, num, fmt, ...)                          \
  if (verbose) {                                                \
    if (PRINT_LEVEL_USER <= kLlInfo)                            \
      maple::logInfo.EmitLogForUser(num, kLlInfo, fmt, ##__VA_ARGS__); \
  }
#define WARN(num, fmt, ...)                                     \
  do {                                                          \
    if (PRINT_LEVEL_USER <= kLlWarn)                            \
      maple::logInfo.EmitLogForUser(num, kLlWarn, fmt, ##__VA_ARGS__); \
  } while (0)
#define ERR(num, fmt, ...)                                     \
  do {                                                         \
    if (PRINT_LEVEL_USER <= kLlErr)                            \
      maple::logInfo.EmitLogForUser(num, kLlErr, fmt, ##__VA_ARGS__); \
  } while (0)

#define FATAL(num, fmt, ...)                                     \
  do {                                                           \
    if (PRINT_LEVEL_USER <= kLlFatal)                            \
      maple::logInfo.EmitLogForUser(num, kLlFatal, fmt, ##__VA_ARGS__); \
    if (DEBUG_TEST)                                              \
      abort();                                                   \
    else                                                         \
      exit(1);                                                   \
  } while (0)

}  // namespace maple
#endif  // MAPLE_UTIL_INCLUDE_MPL_LOGGING_H
