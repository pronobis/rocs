// ===============================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (c) 2010-2012, the ROCS authors. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met: 
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution. 
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ===============================================================================

/*!
 * Config test case.
 * \author Andrzej Pronobis
 * \file test_config.cc
 */

// ROCS inludes
#include <rocs/core/Config.h>
// Boost & STL includes
#include <vector>
#include <boost/assign/list_of.hpp>
// Google Test
#include "gtest/gtest.h"

using namespace rocs::core;
using namespace std;
using namespace boost::assign;

// ------------------------------------------------------------
// Testing command line argument parsing for single keys.
// ------------------------------------------------------------
TEST(config, command_line_args_single)
{
  // Define some arguments
  int argc = 2;
  char const *argv[] =
    { "test", "--one.two.three", "1" };
  
  // Let configuration parse the arguments
  Config config(argc, argv);

  // Print the configuration
  config.printConfiguration();

  // Get values
  bool wasFound;
  int value1 = config.getValue("one.two.three", 2, wasFound);
  int value2 = config.getValue("one.two.three", 2);

  // Check the output
  ASSERT_TRUE(wasFound);
  ASSERT_EQ(value1, 1);
  ASSERT_EQ(value2, 1);
}


// ------------------------------------------------------------
// Testing command line argument parsing for lists.
// ------------------------------------------------------------
TEST(config, command_line_args_list1)
{
  // Define some arguments
  int argc = 4;
  char const *argv[] =
    { "test", "--list.item1.key", "1", "--list.item2.key", "2" };
  
  // Let configuration parse the arguments
  Config config(argc, argv);

  // Print the configuration
  config.printConfiguration();

  // Get values
  vector<int> values;
  config.getValueList("list", "key", values);

  // Check the output
  ASSERT_EQ(values.size(), 2U);
  ASSERT_EQ(values[0], 1);
  ASSERT_EQ(values[1], 2);
}


// ------------------------------------------------------------
// Testing command line argument parsing for lists.
// ------------------------------------------------------------
TEST(config, command_line_args_list2)
{
  // Define some arguments
  int argc = 8;
  char const *argv[] =
    { "test", "--list.item.key", "1", "--list.item.key", "2",
      "--list.item.key3", "3", "--list.item4.key", "4" };

  // Let configuration parse the arguments
  Config config(argc, argv);

  // Print the configuration
  config.printConfiguration();

  // Get values
  vector<int> values;
  config.getValueList("list", "key", values);

  // Check the output
  ASSERT_EQ(values.size(), 3U);
  ASSERT_EQ(values[0], 1); 
  ASSERT_EQ(values[1], 2);
  ASSERT_EQ(values[2], 4);
}


// ------------------------------------------------------------
// Testing file parsing.
// ------------------------------------------------------------
/*!
 * A function to test some simple getters in the config files
 * \param filenameIn
 *        the config file
 * \param canHaveDepthHigherThanOne
 *        true if you can have lists in the file (false for INI)
 */
void simpleFileTest(const string filenameIn,
                    bool canHaveDepthHigherThanOne = true)
{
  Config config;
  config.addConfigFile(filenameIn);

  // Print the configuration
  config.printConfiguration();

  // Get values
  // Single
  bool wasFound1;
  int value1 = config.getValue("one1", 100, wasFound1);
  bool wasFound2;
  float value2 = config.getValue("one2", 100.0, wasFound2);
  bool wasFound3;
  string value3 = config.getValue("one3", string(""), wasFound3);
  bool wasFound4;
  int value4 = config.getValue("one4.two4_1", 100, wasFound4);
  bool wasFound5;
  const char* value5 = config.getValue("one4.two4_2", "", wasFound5);
  bool wasFound6;
  float value6 = config.getValue("one5.two5", 100.0, wasFound6);

  // Default
  bool wasFound8;
  int value8 = config.getValue("one10.two10", 100, wasFound8);

  // Check the output
  ASSERT_TRUE(wasFound1);
  ASSERT_EQ(value1, 1);
  ASSERT_TRUE(wasFound2);
  ASSERT_GT(value2, 2.29);
  ASSERT_LT(value2, 2.31);
  ASSERT_TRUE(wasFound3);
  ASSERT_EQ( value3, string("This is text"));
  ASSERT_TRUE(wasFound4);
  ASSERT_EQ( value4, 1 );
  ASSERT_TRUE(wasFound5);
  ASSERT_STREQ( value5, "This is text" );
  ASSERT_TRUE(wasFound6);
  ASSERT_GT( value6, 2.29 );
  ASSERT_LT( value6, 2.31 );
  ASSERT_TRUE(!wasFound8);
  ASSERT_EQ(value8, 100);

  /*
   * part with depth higher than 1 (impossible for ini files)
   */
  if (!canHaveDepthHigherThanOne)
    return;

  bool wasFound7;
  int value7 = config.getValue("one6.two6.three6", 100, wasFound7);
  // Lists
  vector<int> values1;
  config.getValueList("list1", "key1", values1);
  vector<int> values2;
  config.getValueList("list2", "key2", values2);
  ASSERT_TRUE(wasFound7);
  ASSERT_EQ(value7, 6);
  ASSERT_EQ(values1.size(), 3U);
  ASSERT_EQ(values1[0], 1);
  ASSERT_EQ(values1[1], 2);
  ASSERT_EQ(values1[2], 4);
  ASSERT_EQ(values2.size(), 3U);
  ASSERT_EQ(values2[0], 1);
  ASSERT_EQ(values2[1], 2);
  ASSERT_EQ(values2[2], 4);
}


// ------------------------------------------------------------
// Testing xml file parsing.
// ------------------------------------------------------------
TEST(config, xml_simple)
{
  simpleFileTest(ROCS_SRC_ROOT "/config/test/test.xml");
}


// ------------------------------------------------------------
// Testing json file parsing.
// ------------------------------------------------------------
TEST(config, json_simple)
{
  simpleFileTest(ROCS_SRC_ROOT "/config/test/test.json");
}


// ------------------------------------------------------------
// Testing info file parsing.
// ------------------------------------------------------------
TEST(config, info_simple)
{
  simpleFileTest(ROCS_SRC_ROOT "/config/test/test.info");
}


// ------------------------------------------------------------
// Testing ini file parsing. */
// ------------------------------------------------------------
TEST(config, ini_simple)
{
  simpleFileTest(ROCS_SRC_ROOT "/config/test/test.ini", false);
}


// ------------------------------------------------------------
// Testing missing file or incorrect filename parsing.
// ------------------------------------------------------------
TEST(config, missingFile)
{
  Config config;
  ASSERT_THROW(config.addConfigFile(ROCS_SRC_ROOT "/config/test/missing.xml"), rocs::core::IOException);
  ASSERT_THROW(config.addConfigFile(ROCS_SRC_ROOT "/config/test/missing.fooext"), rocs::core::IOException);
}


// ------------------------------------------------------------
// Testing broken file parsing.
// ------------------------------------------------------------
TEST(config, brokenXmlFile)
{
  Config config;
  ASSERT_THROW(config.addConfigFile(ROCS_SRC_ROOT "/config/test/test_broken.xml"), rocs::core::IOException);
  ASSERT_THROW(config.addConfigFile(ROCS_SRC_ROOT "/config/test/test_broken2.xml"), rocs::core::IOException);
}


// ------------------------------------------------------------
// Testing includes
// ------------------------------------------------------------
/*!
 * A function to test the include tags
 * @param filenameIn
 *        the file containing the include tags
 * @param checkList
 *        true if you can have lists in the file (false for INI)
 */
void testIncludeFile(const string filenameIn, bool checkList = true)
{
  Config config;
  config.addConfigFile(filenameIn);

  // Print the configuration
  config.printConfiguration();

  // Get values
  // Single
  bool wasFound1;
  int value1 = config.getValue("foo", -1, wasFound1);
  bool wasFound2;
  int value2 = config.getValue("bar", -1, wasFound2);

  // Check the output
  ASSERT_TRUE( wasFound1 );
  ASSERT_EQ( value1, 1 );
  ASSERT_TRUE( wasFound2 );
  ASSERT_EQ( value2, 2 );

  if (checkList)
  {
    // Lists
    vector<string> values1;
    config.getValueList("list", "value", values1);
    ASSERT_EQ(values1.size(), 3U);
    ASSERT_EQ(values1[0], string("item1"));
    ASSERT_EQ(values1[1], string("item2"));
    ASSERT_EQ(values1[2], string("item3"));
  }
}


// ------------------------------------------------------------
// Testing xml file with includes parsing.
// ------------------------------------------------------------
TEST(config,  includeXmlFile)
{
  testIncludeFile(ROCS_SRC_ROOT "/config/test/test_include1.xml");
}


// ------------------------------------------------------------
// Testing json file with includes parsing. 
// ------------------------------------------------------------
TEST(config,  includejsonFile)
{
  testIncludeFile(ROCS_SRC_ROOT "/config/test/test_include1.json");
}


// ------------------------------------------------------------
// Testing info file with includes parsing.
// ------------------------------------------------------------
TEST(config,  includeinfoFile)
{
  testIncludeFile(ROCS_SRC_ROOT "/config/test/test_include1.info");
}


// ------------------------------------------------------------
// Testing ini file with includes parsing. 
// ------------------------------------------------------------
TEST(config,  includeiniFile)
{
  testIncludeFile(ROCS_SRC_ROOT "/config/test/test_include1.ini", false);
}


// ------------------------------------------------------------
// Testing ini file with includes parsing. 
// ------------------------------------------------------------
void testListChildren(const Config& config,
                      const string& path, const vector<string> &expected)
{
  vector<string> output;
  config.getChildren(path, &output);
  ASSERT_EQ(output, expected);
}


TEST(config, listChilds)
{
  Config config;
  config.addConfigFile(ROCS_SRC_ROOT "/config/test/test.xml");
  testListChildren(config, "", list_of("list1")("list2")("one1")("one2")("one3")("one4")("one5")("one6"));
  testListChildren(config, "one4", list_of("one4.two4_1")("one4.two4_2"));
  testListChildren(config, "list2.item", list_of("list2.item.key2")("list2.item.key2X"));
}
