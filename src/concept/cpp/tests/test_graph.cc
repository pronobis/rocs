// ==================================================================
// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2011  André Susano Pinto
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

#include <boost/assign/list_of.hpp>
#include <boost/test/unit_test.hpp>

#include <map>
#include <set>

#include "rocs/concept/Graph.h"

using namespace std;
using boost::assign::list_of;

#define ROCSDIR "../../../"
#define TESTDATA_DIR ROCSDIR "data/concept/"

/*!
 * a test case for loading files from Configuration,
 */
BOOST_AUTO_TEST_CASE(caseLoadGraphInformation)
{
	rocs::concept::GraphInformation gi;
	gi.LoadConfig(TESTDATA_DIR "test_loadgraphinfo.xml");

	BOOST_CHECK(gi.types.size() == 3);

	BOOST_CHECK(gi.types["room_category"].values
			== list_of("corridor")("kitchen")("living_room")("office"));
	BOOST_CHECK(gi.types["shape"].values
			== list_of("circular")("elongated")("square"));
	BOOST_CHECK(gi.types["appearance"].values
			== list_of("corridor")("kitchen")("office"));

	BOOST_CHECK(gi.factors.size() == 4);
	BOOST_CHECK(gi.factors["room_category_appearance"].potential.size() == 16);

	vector<string> index = list_of("office")("office");
	BOOST_CHECK_CLOSE_FRACTION(0.91,
			gi.factors["room_category_appearance"].potential[index], 1e-7);
}
