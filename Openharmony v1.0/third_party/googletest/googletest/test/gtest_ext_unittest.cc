/*
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "gtest/gtest.h"

using namespace testing::ext;
TEST(GTestExtUnittest_testflag, test_checkFlagsLegality) {
  const int TEST_FLAGS_NUM = 6;
  const int flags[TEST_FLAGS_NUM] = { Platform.Hisi | Device.Dual_Sim | TestSize.Medium,
    Platform.Hisi | Platform.Qcom,
    Device.Dual_Sim | Chip.Kirin960 | Chip.Kirin970,
    0, 66, -2
  };
  const bool nice[TEST_FLAGS_NUM] = { true, true, true, true, false, false };
  for (int i = 0; i < TEST_FLAGS_NUM; i++) {
    EXPECT_EQ(checkFlagsLegality(flags[i]), nice[i]);
  }
}

TEST(GTestExtUnittest_testflag, test_flagForName) {
  const int DEFAULT_FLAGS = -1;
  const int TEST_COMBINE_NUM = 8;
  const char* sets[TEST_COMBINE_NUM] = { "", "??", "platform", "Platform", "Platform", "Platform", "Platform", "Device" };
  const char* eles[TEST_COMBINE_NUM] = { "", "hisi", "hisi", "QCOM", "xxx" ,"Qcom|Hisi", "Qcom|HisiX", "Device.DUAL_SIM|SDCARD" };
  const bool nice[TEST_COMBINE_NUM] = { false, false, true, true, false, true, false, true };
  const int exp_flags[] = { DEFAULT_FLAGS, DEFAULT_FLAGS, Platform.Hisi, Platform.Qcom, DEFAULT_FLAGS,  Platform.Hisi | Platform.Qcom, DEFAULT_FLAGS, Device.Dual_Sim | Device.Sdcard };
  for (int i = 0; i < TEST_COMBINE_NUM; i++) {
    int result = DEFAULT_FLAGS;
    printf("[%d]:: set='%s', ele='%s', exp_nice='%d', exp_flags='0x%08x'\n",
      i + 1, sets[i], eles[i], nice[i], exp_flags[i]);
    const bool ok = flagForName(sets[i], eles[i], result);
    EXPECT_EQ(ok, nice[i]);
    EXPECT_EQ(result, exp_flags[i]);
  }
}

///////////////////////////////////////////////////////////////////// >>>>>>>>
// mock disabled tests, don't actually run them
// TODO::add test for TEST_P, TYPED_TEST, TYPED_TEST_P
TEST(EmptyCase, test0) { ; }
HWTEST(EmptyCase, test1, Platform.Qcom | TestSize.Large, req1) { ; }
HWTEST(EmptyCase, test2, Platform.Hisi | Platform.Qcom | Device.Sim, req1) { ; }

class EmptyCase_F : public testing::Test {
protected:
  static const int integer = 0;
};

HWTEST_F(EmptyCase_F, test1, Platform.Qcom | TestSize.Large, req2) { ; }

HWTEST_F(EmptyCase_F, test2, Platform.Hisi | Platform.Qcom | Device.Sim, req2) { ; }

static int flagsForTest(const std::map<const char*, int>& map, const char* full_test_name, int def_flags) {
  std::map<const char*, int>::const_iterator c_iter;
  for (c_iter = map.begin(); c_iter != map.end(); c_iter++) {
    if (strcmp(c_iter->first, full_test_name) == 0) {
      return c_iter->second;
    }
  }
  return def_flags;
}

static const char* reqForTest(const std::map<const char*, const char*>& map, const char* full_test_name) {
  std::map<const char*, const char*>::const_iterator c_iter;
  for (c_iter = map.begin(); c_iter != map.end(); c_iter++) {
    if (strcmp(c_iter->first, full_test_name) == 0) {
      return c_iter->second;
    }
  }
  return NULL;
}

static bool refreshFilter(testing::ext::TestFilter* filter, const char** ks, const char** vs, int len) {
  filter->reset();
  std::map<const char*, string*>& mapping = filter->getAllFilterFlagsKv();
  // gracefully clear the map
  map<const char*, string*>::iterator iter;
  for (iter = mapping.begin(); iter != mapping.end(); iter++) {
    // free the newed strings
    delete iter->second;
  }
  mapping.clear();
  // insert new pairs
  for (int i = 0; i < len; i++) {
    mapping.insert(pair<const char*, string*>(ks[i], new string(vs[i])));
  }
  return filter->postParsingArguments();
}

TEST(GTestExtUnittest_testdefmgr, test_queryFlagsFor) {
  // expected actual_flags >>>>
  std::map<const char*, int> exp_flags_map;
  exp_flags_map.insert(pair<const char*, int>("EmptyCase.test0", 0));
  exp_flags_map.insert(pair<const char*, int>("EmptyCase.test1", Platform.Qcom | TestSize.Large));
  exp_flags_map.insert(pair<const char*, int>("EmptyCase.test2", Platform.Hisi | Platform.Qcom | Device.Sim));
  exp_flags_map.insert(pair<const char*, int>("EmptyCase_F.test1", Platform.Qcom | TestSize.Large));
  exp_flags_map.insert(pair<const char*, int>("EmptyCase_F.test2", Platform.Hisi | Platform.Qcom | Device.Sim));
  // <<<<
  int count = 0;
  ::testing::UnitTest* ut = ::testing::UnitTest::GetInstance();
  const int case_num = ut->total_test_case_count();
  for (int i = 0; i < case_num; i++) {
    const ::testing::TestCase* tc = ut->GetTestCase(i);
    if (strstr(tc->name(), "EmptyCase") == NULL) {
      continue;
    }
    const int test_num = tc->total_test_count();
    for (int j = 0; j < test_num; j++) {
      count++;
      const ::testing::TestInfo* test = tc->GetTestInfo(j);
      const string test_full_name = string(tc->name()) + "." + test->name();
      const int exp_flags = flagsForTest(exp_flags_map, test_full_name.c_str(), TestFlag::None);
      std::map<const char*, int>::const_iterator c_iter = exp_flags_map.find(test_full_name.c_str());
      const int actual_flags = TestDefManager::cinstance()->queryFlagsFor(test, TestFlag::None);
      printf("[%d]:: test='%s', exp_flags='0x%08x', actu_flags='0x%08x'\n", count, test_full_name.c_str(), exp_flags, actual_flags);
      EXPECT_EQ(actual_flags, exp_flags);
    }
  }
}

TEST(GTestExtUnittest_testdefmgr, test_queryReqFor) {
  // expected actual_flags >>>>
  std::map<const char*, const char*> exp_reqs_map;
  exp_reqs_map.insert(pair<const char*, const char*>("EmptyCase.test0", NULL));
  exp_reqs_map.insert(pair<const char*, const char*>("EmptyCase.test1", "req1"));
  exp_reqs_map.insert(pair<const char*, const char*>("EmptyCase.test2", "req1"));
  exp_reqs_map.insert(pair<const char*, const char*>("EmptyCase_F.test1", "req2"));
  exp_reqs_map.insert(pair<const char*, const char*>("EmptyCase_F.test2", "req2"));
  // <<<<
  int count = 0;
  ::testing::UnitTest* ut = ::testing::UnitTest::GetInstance();
  const int case_num = ut->total_test_case_count();
  for (int i = 0; i < case_num; i++) {
    const ::testing::TestCase* tc = ut->GetTestCase(i);
    if (strstr(tc->name(), "EmptyCase") == NULL) {
      continue;
    }
    const int test_num = tc->total_test_count();
    for (int j = 0; j < test_num; j++) {
      count++;
      const ::testing::TestInfo* test = tc->GetTestInfo(j);
      const string test_full_name = string(tc->name()) + "." + test->name();
      const char* exp_reqno = reqForTest(exp_reqs_map, test_full_name.c_str());
      const char* actual_reqno = TestDefManager::cinstance()->queryRqNoFor(test);
      printf("[%d]:: test='%s', exp_reqno='%s', actual_reqno='%s\n", count, test_full_name.c_str(), exp_reqno, actual_reqno);
      EXPECT_STREQ(actual_reqno, exp_reqno);
    }
  }
}
///////////////////////////////////////////////////////////////////// <<<<<<<<

TEST(GTestExtUnittest_testfilter, requiredFlags) {
  const int FILTER_CONFIGS_NUM = 4;
  testing::ext::TestFilter* filter = testing::ext::TestFilter::instance();
  const char* ks[4] = { "platform", "chip", "device", "testsize" };
  const char* vs[FILTER_CONFIGS_NUM][4] = {
    {"Platform.qcom", "", "sim|sdcard", "medium"},
    { "", "", "", "medium" },
    { "", "", "", "" },
    { "HISI", "xyz", "SIM", "" } // cause flags parsing failure
  };
  const int exp_parse_success[4] = { true, true, true, false };
  const int exp_rflags[4] = {
    Platform.Qcom | Device.Sim | Device.Sdcard | TestSize.Medium,
    TestSize.Medium,
    TestFlag::None,
    TestFlag::None };

  for (int i = 0; i < FILTER_CONFIGS_NUM; i++) {
    // initialize filter
    const bool parse_success = refreshFilter(filter, ks, vs[i], 4);
    // do test
    EXPECT_EQ(exp_parse_success[i], parse_success);
    if (parse_success)
      EXPECT_EQ(exp_rflags[i], filter->requireFlags());
  }
}

TEST(GTestExtUnittest_testfilter, acceptByFlags) {
  const int FILTER_CONFIGS_NUM = 3;
  const int TEST_FLAGS_NUM = 4;
  testing::ext::TestFilter* filter = testing::ext::TestFilter::instance();
  const char* ks[4] = { "platform", "chip", "device", "testsize" };
  const char* vs[FILTER_CONFIGS_NUM][4] = {
    { "", "", "", "" },
    { "Platform.qcom", "", "sim|sdcard", "medium" },
    { "", "", "sdcard", "medium" }
  };
  const int exp_rflag[FILTER_CONFIGS_NUM] = {
    TestFlag::None,
    Platform.Qcom | Device.Sim | Device.Sdcard | TestSize.Medium,
    Device.Sdcard | TestSize.Medium };
  const int test_flags[TEST_FLAGS_NUM] = {
    TestFlag::None,
    Platform.Qcom | Device.Sim,
    Platform.Qcom | Device.Sim | Device.Sdcard | TestSize.Medium,
    Platform.Qcom | Device.Sim | Device.Sdcard | TestSize.Medium | Chip.Q8639
  };
  // exp accept for each flag at each filter configuration
  const bool exp_accepts[FILTER_CONFIGS_NUM][TEST_FLAGS_NUM] = {
    { true, true, true, true },
    { false, false, true, true },
    { false, false, true, true }
  };

  int count = 0;
  for (int m = 0; m < FILTER_CONFIGS_NUM; m++) {
    // initialize filter with each configuration
    const bool parse_success = refreshFilter(filter, ks, vs[m], 4);
    // test required_flag under this filter configuration
    EXPECT_EQ(true, parse_success);
    if (!parse_success) {
      continue;
    }
    EXPECT_EQ(exp_rflag[m], filter->requireFlags());
    // test tests-acception under this filter configuration
    for (int p = 0; p < TEST_FLAGS_NUM; p++) {
      count++;
      printf("[%d]:: required_flags='0x%08x', test_flags='0x%08x', exp_accept='%d'\n",
        count, filter->requireFlags(), test_flags[p], exp_accepts[m][p]);
      EXPECT_EQ(exp_accepts[m][p], filter->accept(test_flags[p], NULL));
    }
  }
}

TEST(GTestExtUnittest_testfilter, acceptByReqs) {
  const int FILTER_CONFIGS_NUM = 3;
  const int TEST_REQS_NUM = 4;
  testing::ext::TestFilter* filter = testing::ext::TestFilter::instance();
  const char* k_req = "req_no";
  const char* v_reqs[FILTER_CONFIGS_NUM] = { "", "req1", "req1;req2" };
  const char* test_reqs[TEST_REQS_NUM] = { NULL, "", "req1", "req2" };
  // exp accept for each req at each filter configuration (req_no)
  const bool exp_accepts[FILTER_CONFIGS_NUM][TEST_REQS_NUM] = {
    { true, true, true, true },
    { false, false, true, false },
    { false, false, true, true }
  };

  int count = 0;
  for (int m = 0; m < FILTER_CONFIGS_NUM; m++) {
    // initialize filter with each configuration
    const bool parse_success = refreshFilter(filter, &k_req, &v_reqs[m], 1);
    // test required_flag under this filter configuration
    EXPECT_EQ(true, parse_success);
    if (!parse_success) {
      continue;
    }
    // test tests-acception under this filter configuration
    for (int p = 0; p < TEST_REQS_NUM; p++) {
      count++;
      printf("[%d]:: required_reqs='%s', test_reqs='%s', exp_accept='%d'\n",
        count, v_reqs[m], test_reqs[p], exp_accepts[m][p]);
      EXPECT_EQ(exp_accepts[m][p], filter->accept(TestFlag::None, test_reqs[p]));
    }
  }
}

TEST(GTestExtUnittest_testfilter, accept) {
  const int FILTER_CONFIGS_NUM = 4;
  const int TEST_COMBINES_NUM = 4;
  testing::ext::TestFilter* filter = testing::ext::TestFilter::instance();
  const char* ks[5] = { "platform", "chip", "device", "testsize", "req_no" };
  const char* vs[FILTER_CONFIGS_NUM][5] = {
    { "", "", "", "", "" },
    { "", "", "", "", "req1" },
    { "Qcom", "", "", "", "" },
    { "Qcom", "", "", "", "req2" }
  };
  const int test_flags[TEST_COMBINES_NUM] = { TestFlag::None,TestFlag::None,Platform.Qcom,Platform.Qcom };
  const char* test_reqs[TEST_COMBINES_NUM] = { NULL, "req1", NULL, "req2" };

  const bool exp_accepts[FILTER_CONFIGS_NUM][TEST_COMBINES_NUM] = {
    { true, true, true, true },
    { false, true, false, false },
    { false, false, true, true },
    { false, false, false, true }
  };
  int count = 0;
  for (int m = 0; m < FILTER_CONFIGS_NUM; m++) {
    // initialize filter with each configuration
    const bool parse_success = refreshFilter(filter, ks, vs[m], 5);
    // test required_flag under this filter configuration
    EXPECT_EQ(true, parse_success);
    if (!parse_success) {
      continue;
    }
    // test tests-acception under this filter configuration
    for (int p = 0; p < TEST_COMBINES_NUM; p++) {
      count++;
      printf("[%d]:: filter=0x%08x/%s, tested=0x%08x/%s, exp_accept=%d\n", count, filter->requireFlags(), filter->requireReq(), test_flags[p], test_reqs[p], exp_accepts[m][p]);
      EXPECT_EQ(exp_accepts[m][p], filter->accept(test_flags[p], test_reqs[p]));
    }
  }
}

TEST(GTestExtUnittest_testfilter, strictAccept) {
  const int FILTER_CONFIGS_NUM = 4;
  const int TEST_COMBINES_NUM = 4;
  testing::ext::TestFilter* filter = testing::ext::TestFilter::instance();
  const char* ks[6] = { "platform", "chip", "device", "testsize", "req_no" ,"strict_tags" };
  const char* vs[FILTER_CONFIGS_NUM][6] = {
    { "", "", "", "", "", "true" },
    { "", "", "", "", "req1", "true" },
    { "Qcom", "", "", "", "", "true" },
    { "Qcom", "", "", "", "req2", "true" }
  };
  const int test_flags[TEST_COMBINES_NUM] = { TestFlag::None,TestFlag::None,Platform.Qcom,Platform.Qcom };
  const char* test_reqs[TEST_COMBINES_NUM] = { NULL, "req1", NULL, "req2" };

  const bool exp_accepts[FILTER_CONFIGS_NUM][TEST_COMBINES_NUM] = {
    { true, false, false, false },
    { false, true, false, false },
    { false, false, true, false },
    { false, false, false, true }
  };
  int count = 0;
  for (int m = 0; m < FILTER_CONFIGS_NUM; m++) {
    // initialize filter with each configuration
    const bool parse_success = refreshFilter(filter, ks, vs[m], 6);
    // test required_flag under this filter configuration
    EXPECT_EQ(true, parse_success);
    if (!parse_success) {
      continue;
    }
    // test tests-acception under this filter configuration
    for (int p = 0; p < TEST_COMBINES_NUM; p++) {
      count++;
      printf("[%d]:: strict_filter=0x%08x/%s, tested=0x%08x/%s, exp_accept=%d\n", count, filter->requireFlags(), filter->requireReq(), test_flags[p], test_reqs[p], exp_accepts[m][p]);
      EXPECT_EQ(exp_accepts[m][p], filter->accept(test_flags[p], test_reqs[p]));
    }
  }
}

// no-automatic tests:::::::::::::::::::::::::::::::::::::
//1) run .exe without any flags:: should run all tests
//2) run .exe with "--gtest_platform=qcom":: should just run {EmptyCase.test1,EmptyCase.test2,EmptyCase_F.test1,EmptyCase_F.test2}
//3) run .exe with "--gtest_platform=qcom,hisi":: should just run {EmptyCase.test2, EmptyCase_F.test2}
//4) run .exe with "--gtest_platform=qcom --gtest_device=sim":: should just run {EmptyCase.test2, EmptyCase_F.test2}
//5) run .exe with "--gtest_platform=qcom --gtest_device=simXX":: test should abort due to arguments error
