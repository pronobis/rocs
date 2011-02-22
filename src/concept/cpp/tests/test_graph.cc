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
			== list_of("elongated")("square"));
	BOOST_CHECK(gi.types["appearance"].values
			== list_of("corridor")("kitchen")("office"));

	BOOST_CHECK(gi.factors.size() == 4);

	BOOST_CHECK(gi.factors["room_category_appearance"].potential.size() == 12);

	vector<string> index = list_of("office")("office");
	BOOST_CHECK_CLOSE_FRACTION(0.91,
			gi.factors["room_category_appearance"].potential[index], 1e-7);
}

/*!
 * a test case for consistency check.
 */
BOOST_AUTO_TEST_CASE(caseTestGraphInformationConsistency)
{
	rocs::concept::GraphInformation gi;
	gi.LoadConfig(TESTDATA_DIR "test_loadgraphinfo.xml");

	BOOST_CHECK(gi.CheckConsistency());

	rocs::concept::VariableType type;
	BOOST_CHECK(false == gi.CheckVarTypeConsistency("EmptyType", type));
	type.values.push_back("zoom");
	type.values.push_back("bar");
	BOOST_CHECK(false == gi.CheckVarTypeConsistency("UnorderedType", type));
	sort(type.values.begin(), type.values.end());
	BOOST_CHECK(true == gi.CheckVarTypeConsistency("OkType", type));

	rocs::concept::FactorData factor;
	BOOST_CHECK(false == gi.CheckFactorConsistency("EmptyFactor", factor));
	factor.variables.push_back(make_pair(string("testVar"), string("OkType")));
	BOOST_CHECK(false == gi.CheckFactorConsistency("UnknownVar", factor));
	gi.Add("OkType", type);
	BOOST_CHECK(false == gi.CheckFactorConsistency("NotAllIndexs", factor));
	factor.potential[list_of("zoom")] = 0.1;
	factor.potential[list_of("bar")]  = 0.2;
	BOOST_CHECK(true == gi.CheckFactorConsistency("OkFactor", factor));
	factor.potential[list_of("zoom")] = 0.1;
	factor.potential[list_of("bar")]  = -0.2;
	BOOST_CHECK(false == gi.CheckFactorConsistency("NegPotential", factor));
}
