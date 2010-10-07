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
 * \file configuration.cc
 */

// Set debug level
#define ROCS_DEBUG_LEVEL 3

// Boost
#include <boost/test/unit_test.hpp>
// ROCS
#include <rocs/core/Configuration.h>
using namespace rocs::core;


/*! Define first test case. */
BOOST_AUTO_TEST_CASE( case1 )
{
	Configuration c;

	/*BOOST_CHECK( 0 == 0 );
	BOOST_REQUIRE( 0 == 0 );*/
}

