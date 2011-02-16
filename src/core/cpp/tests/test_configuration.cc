// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2010  Andrzej Pronobis
//
// This file is part of ROCS.
//
// ROCS is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3
// of the License, or (at your option) any later version.
//
// ROCS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ROCS. If not, see <http://www.gnu.org/licenses/>.
// ==================================================================

/*!
 * Configuration test suite.
 * \author Andrzej Pronobis
 * \file test_configuration.cc
 */

// Boost & Stl
#include <vector>
#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>

// ROCS
#include <rocs/core/Configuration.h>

using namespace rocs::core;
using namespace std;
using namespace boost::assign;

/*!Case 1 - Testing command line argument parsing for single keys. */
BOOST_AUTO_TEST_CASE( command_line_args_single )
{
	// Define some arguments
	int argc = 2;
	char const *argv[] =
	{ "test", "--one.two.three", "1" };

	// Let configuration parse the arguments
	Configuration config(argc, argv);

	// Print the configuration
	config.printConfiguration();

	// Get values
	bool wasFound;
	int value1 = config.getValue("one.two.three", 2, wasFound);
	int value2 = config.getValue("one.two.three", 2);

	// Check the output
	BOOST_REQUIRE( wasFound );
	BOOST_REQUIRE_EQUAL( value1, 1 );
	BOOST_REQUIRE_EQUAL( value2, 1 );
}

/*! Case 2 - Testing command line argument parsing for lists.*/
BOOST_AUTO_TEST_CASE( command_line_args_list1 )
{
	// Define some arguments
	int argc = 4;
	char const *argv[] =
	{ "test", "--list.item1.key", "1", "--list.item2.key", "2" };

	// Let configuration parse the arguments
	Configuration config(argc, argv);

	// Print the configuration
	config.printConfiguration();

	// Get values
	vector<int> values;
	config.getValueList("list", "key", values);

	// Check the output
	BOOST_REQUIRE( values.size() == 2 );
	BOOST_REQUIRE_EQUAL( values[0], 1 );
	BOOST_REQUIRE_EQUAL( values[1], 2 );
}

/*! Case 3 - Testing command line argument parsing for lists. */
BOOST_AUTO_TEST_CASE( command_line_args_list2 )
{
	// Define some arguments
	int argc = 8;
	char const *argv[] =
	{ "test", "--list.item.key", "1", "--list.item.key", "2",
			"--list.item.key3", "3", "--list.item4.key", "4" };

	// Let configuration parse the arguments
	Configuration config(argc, argv);

	// Print the configuration
	config.printConfiguration();

	// Get values
	vector<int> values;
	config.getValueList("list", "key", values);

	// Check the output
	BOOST_REQUIRE_EQUAL( values.size(), 3 );
	BOOST_REQUIRE_EQUAL( values[0], 1 );
	BOOST_REQUIRE_EQUAL( values[1], 2 );
	BOOST_REQUIRE_EQUAL( values[2], 4 );
}

/*!
 * a function to test some simple getters in the config files
 * @param filenameIn
 *          the config file
 * @param canHaveDepthHigherThanOne
 *          <code>true</code> if you can have lists in the file (false for INI)
 */
void simpleFileTest(const string filenameIn, bool canHaveDepthHigherThanOne =
		true)
{
	Configuration config;
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
	BOOST_REQUIRE( wasFound1 );
	BOOST_REQUIRE_EQUAL( value1, 1 );
	BOOST_REQUIRE( wasFound2 );
	BOOST_REQUIRE_GT( value2, 2.29 );
	BOOST_REQUIRE_LT( value2, 2.31 );
	BOOST_REQUIRE( wasFound3 );
	BOOST_REQUIRE_EQUAL( value3, string("This is text") );
	BOOST_REQUIRE( wasFound4 );
	BOOST_REQUIRE_EQUAL( value4, 1 );
	BOOST_REQUIRE( wasFound5 );
	BOOST_REQUIRE_EQUAL( value5, "This is text" );
	BOOST_REQUIRE( wasFound6 );
	BOOST_REQUIRE_GT( value6, 2.29 );
	BOOST_REQUIRE_LT( value6, 2.31 );
	BOOST_REQUIRE( !wasFound8 );
	BOOST_REQUIRE_EQUAL( value8, 100 );

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
	BOOST_REQUIRE( wasFound7 );
	BOOST_REQUIRE_EQUAL( value7, 6 );
	BOOST_REQUIRE_EQUAL( values1.size(), 3 );
	BOOST_REQUIRE_EQUAL( values1[0], 1 );
	BOOST_REQUIRE_EQUAL( values1[1], 2 );
	BOOST_REQUIRE_EQUAL( values1[2], 4 );
	BOOST_REQUIRE_EQUAL( values2.size(), 3 );
	BOOST_REQUIRE_EQUAL( values2[0], 1 );
	BOOST_REQUIRE_EQUAL( values2[1], 2 );
	BOOST_REQUIRE_EQUAL( values2[2], 4 );
}

/*! Case 4 - Testing xml file parsing. */
BOOST_AUTO_TEST_CASE( xml_simple )
{
	simpleFileTest(ROCS_DIR "/config/test/test.xml");
}
/*! Case 5 - Testing json file parsing. */
BOOST_AUTO_TEST_CASE( json_simple )
{
	simpleFileTest(ROCS_DIR "/config/test/test.json");
}
/*! Case 6 - Testing info file parsing. */
BOOST_AUTO_TEST_CASE( info_simple )
{
	simpleFileTest(ROCS_DIR "/config/test/test.info");
}
/*! Case 7 - Testing ini file parsing. */
BOOST_AUTO_TEST_CASE( ini_simple )
{
	simpleFileTest(ROCS_DIR "/config/test/test.ini", false);
}

/*! Case 8 - Testing missing file or incorrect filename parsing. */
BOOST_AUTO_TEST_CASE( missingFile )
{
	Configuration config;
	BOOST_REQUIRE_THROW(config.addConfigFile(ROCS_DIR "/config/test/missing.xml"), rocs::core::IOException);
	BOOST_REQUIRE_THROW(config.addConfigFile(ROCS_DIR "/config/test/missing.fooext"), rocs::core::IOException);
}

/*! Case 9 - Testing broken file parsing. */
BOOST_AUTO_TEST_CASE( brokenXmlFile )
{
	Configuration config;
	BOOST_REQUIRE_THROW(config.addConfigFile(ROCS_DIR "/config/test/test_broken.xml"), rocs::core::IOException);
	BOOST_REQUIRE_THROW(config.addConfigFile(ROCS_DIR "/config/test/test_broken2.xml"), rocs::core::IOException);
}

/*!
 * a function to test the include tags
 * @param filenameIn
 *          the file containing the include tags
 * @param checkList
 *          <code>true</code> if you can have lists in the file (false for INI)
 */
void testIncludeFile(const string filenameIn, bool checkList = true)
{
	Configuration config;
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
	BOOST_REQUIRE( wasFound1 );
	BOOST_REQUIRE_EQUAL( value1, 1 );
	BOOST_REQUIRE( wasFound2 );
	BOOST_REQUIRE_EQUAL( value2, 2 );

	if (checkList)
	{
		// Lists
		vector<string> values1;
		config.getValueList("list", "value", values1);
		BOOST_REQUIRE_EQUAL( values1.size(), 3 );
		BOOST_REQUIRE( values1[0] == (string) "item1" );
		BOOST_REQUIRE( values1[1] == (string) "item2" );
		BOOST_REQUIRE( values1[2] == (string) "item3" );
	}
}

/*! Case 10 - Testing xml file with includes parsing. */
BOOST_AUTO_TEST_CASE( includeXmlFile )
{
	testIncludeFile(ROCS_DIR "/config/test/test_include1.xml");
}
/*! Case 11 - Testing json file with includes parsing. */
BOOST_AUTO_TEST_CASE( includejsonFile )
{
	testIncludeFile(ROCS_DIR "/config/test/test_include1.json");
}
/*! Case 12 - Testing info file with includes parsing. */
BOOST_AUTO_TEST_CASE( includeinfoFile )
{
	testIncludeFile(ROCS_DIR "/config/test/test_include1.info");
}
/*! Case 13 - Testing ini file with includes parsing. */
BOOST_AUTO_TEST_CASE( includeiniFile )
{
	testIncludeFile(ROCS_DIR "/config/test/test_include1.ini", false);
}
/*! Case 14 - Testing ini file with includes parsing. */
void testListChildren(const Configuration& config,
		const string& path, const vector<string> &expected)
{
	vector<string> output;
	config.getChildren(path, &output);
	BOOST_CHECK(output == expected);
}
BOOST_AUTO_TEST_CASE( listChilds )
{
	Configuration config;
	config.addConfigFile(ROCS_DIR "/config/test/test.xml");
	testListChildren(config, "", list_of("list1")("list2")("one1")("one2")("one3")("one4")("one5")("one6"));
	testListChildren(config, "one4", list_of("one4.two4_1")("one4.two4_2"));
	testListChildren(config, "list2.item", list_of("list2.item.key2")("list2.item.key2X"));
}
