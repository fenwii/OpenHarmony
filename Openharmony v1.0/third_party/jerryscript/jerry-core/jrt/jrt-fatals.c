/* Copyright JS Foundation and other contributors, http://js.foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Implementation of exit with specified status code.
 */

#include "jmem.h"
#include "jrt.h"
#include "jrt-libc-includes.h"

#ifdef _WIN32
#  ifdef _WIN64
#    define PRI_SIZET "lu"
#    define MSG_SIZE_TYPE unsigned long
#  else
#    define PRI_SIZET "zu"
#    define MSG_SIZE_TYPE size_t
#  endif
#else
#  define PRI_SIZET "zu"
#  define MSG_SIZE_TYPE size_t
#endif

#if ENABLED (JERRY_MEM_STATS)
static void
jerry_dump_memstats_on_error (void)
{
  /* Dump memory stats */
  jmem_heap_stats_t jmem_heap_stats;
  jmem_heap_get_stats (&jmem_heap_stats);

  JERRY_ERROR_MSG ("\tMemory info:\n");
  JERRY_ERROR_MSG ("\theap total size: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.size));

  JERRY_ERROR_MSG ("\tcurrently allocated bytes: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.allocated_bytes));
  JERRY_ERROR_MSG ("\tpeak allocated bytes: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.peak_allocated_bytes));

  JERRY_ERROR_MSG ("\tbytes waste due to blocks filled partially: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.waste_bytes));
  JERRY_ERROR_MSG ("\tpeak wasted bytes: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.peak_waste_bytes));

  JERRY_ERROR_MSG ("\tallocated memory for byte code: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.byte_code_bytes));
  JERRY_ERROR_MSG ("\tpeak allocated memory for byte code: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.peak_byte_code_bytes));

  JERRY_ERROR_MSG ("\tallocated memory for strings: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.string_bytes));
  JERRY_ERROR_MSG ("\tpeak allocated memory for strings: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.peak_string_bytes));

  JERRY_ERROR_MSG ("\tallocated memory for objects: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.object_bytes));
  JERRY_ERROR_MSG ("\tpeak allocated memory for objects: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.peak_object_bytes));

  JERRY_ERROR_MSG ("\tallocated memory for properties: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.property_bytes));
  JERRY_ERROR_MSG ("\tpeak allocated memory for properties: %"PRI_SIZET"\n", (MSG_SIZE_TYPE)(jmem_heap_stats.peak_property_bytes));
}
#endif

/*
 * Exit with specified status code.
 *
 * If !JERRY_NDEBUG and code != 0, print status code with description
 * and call assertion fail handler.
 */
void JERRY_ATTR_NORETURN
jerry_fatal (jerry_fatal_code_t code) /**< status code */
{
#if defined (_WIN32) || defined (_WIN64) || !defined (JERRY_NDEBUG)
  switch (code)
  {
    case ERR_OUT_OF_MEMORY:
    {
      JERRY_ERROR_MSG ("Error: ERR_OUT_OF_MEMORY\n");
      break;
    }
    case ERR_REF_COUNT_LIMIT:
    {
      JERRY_ERROR_MSG ("Error: ERR_REF_COUNT_LIMIT\n");
      break;
    }
    case ERR_DISABLED_BYTE_CODE:
    {
      JERRY_ERROR_MSG ("Error: ERR_DISABLED_BYTE_CODE\n");
      break;
    }
    case ERR_FAILED_INTERNAL_ASSERTION:
    {
      JERRY_ERROR_MSG ("Error: ERR_FAILED_INTERNAL_ASSERTION\n");
      break;
    }
    default:
    {
      JERRY_ERROR_MSG ("Error: ERR_UNKNOWN_FATAL\n");
      break;
    }
  }

#if ENABLED (JERRY_MEM_STATS)
  jerry_dump_memstats_on_error ();
#endif
#endif

  jerry_port_fatal (code);

  /* to make compiler happy for some RTOS: 'control reaches end of non-void function' */
  while (true)
  {
  }
} /* jerry_fatal */

#ifndef JERRY_NDEBUG
/**
 * Handle failed assertion
 */
void JERRY_ATTR_NORETURN
jerry_assert_fail (const char *assertion, /**< assertion condition string */
                   const char *file, /**< file name */
                   const char *function, /**< function name */
                   const uint32_t line) /**< line */
{
  JERRY_ERROR_MSG ("ICE: Assertion '%s' failed at %s(%s):%lu.\n",
                   assertion,
                   file,
                   function,
                   (unsigned long) line);

  jerry_fatal (ERR_FAILED_INTERNAL_ASSERTION);
} /* jerry_assert_fail */

/**
 * Handle execution of control path that should be unreachable
 */
void JERRY_ATTR_NORETURN
jerry_unreachable (const char *file, /**< file name */
                   const char *function, /**< function name */
                   const uint32_t line) /**< line */
{
  JERRY_ERROR_MSG ("ICE: Unreachable control path at %s(%s):%lu was executed.\n",
                   file,
                   function,
                   (unsigned long) line);

  jerry_fatal (ERR_FAILED_INTERNAL_ASSERTION);
} /* jerry_unreachable */
#endif /* !JERRY_NDEBUG */
