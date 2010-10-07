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

// Set debug level
#define ROCS_DEBUG_LEVEL 3

// Boost & Stl
#include <vector>
#include <boost/test/unit_test.hpp>
// ROCS
#include <rocs/core/Configuration.h>

using namespace rocs::core;
using namespace std;

/*!
 * Case 1
 * Testing command line argument parsing for single keys.
 */
BOOST_AUTO_TEST_CASE( command_line_args_single )
{
	// Define some arguments
	int argc = 2;
	char const *argv[] = { "test", "--one.two.three", "1" };

	// Let configuration parse the arguments
	Configuration config(argc, argv);
	bool wasFound;
	int value1 = config.getValue("one.two.three", 2, wasFound);
	int value2 = config.getValue("one.two.three", 2);

	// Print the configuration
	config.printConfiguration();

	// Check the output
	BOOST_REQUIRE( wasFound );
	BOOST_REQUIRE( value1 == 1 );
	BOOST_REQUIRE( value2 == 1 );
}

/*!
 * Case 2
 * Testing command line argument parsing for lists.
 */
BOOST_AUTO_TEST_CASE( command_line_args_list1 )
{
	// Define some arguments
	int argc = 4;
	char const *argv[] = { "test", "--list.item1.key", "1", "--list.item2.key",
			"2" };

	// Let configuration parse the arguments
	Configuration config(argc, argv);
	vector<int> values;
	int nbFound;
	config.getValueList("list", "key", nbFound, values);

	// Print the configuration
	config.printConfiguration();

	// Check the output
	BOOST_REQUIRE( nbFound == 2 );
	BOOST_REQUIRE( values[0] == 1 );
	BOOST_REQUIRE( values[1] == 2 );
}

/*!
 * Case 2
 * Testing command line argument parsing for lists.
 */
BOOST_AUTO_TEST_CASE( command_line_args_list2 )
{
	// Define some arguments
	int argc = 8;
	char const *argv[] = { "test", "--list.item.key", "1", "--list.item.key",
			"2", "--list.item.key3", "3" , "--list.item4.key", "4"};

	// Let configuration parse the arguments
	Configuration config(argc, argv);
	vector<int> values;
	int nbFound;
	config.getValueList("list", "key", nbFound, values);

	// Print the configuration
	config.printConfiguration();

	// Check the output
	BOOST_REQUIRE( nbFound == 3 );
	BOOST_REQUIRE( values[0] == 1 );
	BOOST_REQUIRE( values[1] == 2 );
	BOOST_REQUIRE( values[2] == 4 );
}

