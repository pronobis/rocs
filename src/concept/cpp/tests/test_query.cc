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
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include <map>
#include <set>

#include "rocs/concept/Graph.h"
#include "rocs/concept/Query.h"

using namespace std;
using boost::assign::list_of;
using boost::scoped_ptr;
using rocs::concept::GraphInformation;
using rocs::concept::Graph;
using rocs::concept::Variable;
using rocs::concept::VariableType;
using rocs::concept::FactorData;
using rocs::concept::Query;

namespace {

// This function is the simplest way to calculate marginal probabilities.
// It should be very easy to trust its correctness.
// FullProb is a map describing all possible states of the world.
// Variables describes which variables we are interested in.
vector<double> SimpleMarginalize(const map<vector<string>, double> &fullProb,
                                 const vector<int> &variables)
{
	typedef pair<vector<string>, double> ProbStateIt;
	map<vector<string>, double> sum;

	vector<string> index(variables.size());
	BOOST_FOREACH(const ProbStateIt &it, fullProb)
	{
		for (size_t i = 0; i < variables.size(); ++i)
			index[i] = it.first[variables[i]];
		sum[index] += it.second;
	}

	vector<double> output;
	BOOST_FOREACH(const ProbStateIt &it, sum)
		output.push_back(it.second);

	return output;
}

class TestData {
 public:
	typedef pair<vector<string>, double> Potential;

	TestData() : gi(new GraphInformation())
	{}

	virtual ~TestData() {}

	// Test samples should overload this.
	virtual void Run() = 0;

	void CheckQuery(const vector<const Variable*> &variables,
					const vector<double> &expected)
	{
		Query q(graph.get());
		vector<double> output;
		BOOST_CHECKPOINT("Calling Query Marginalization");
		q.Marginalize(variables, &output);
		BOOST_CHECKPOINT("Marginalization Completed");
		BOOST_REQUIRE(output.size() == expected.size());
		for (size_t i = 0; i < output.size(); ++i)
			BOOST_CHECK_CLOSE_FRACTION(expected[i], output[i], 1e-5);
	}

	void AddVarType(const string &name, const vector<string> &values)
	{
		rocs::concept::VariableType type;

		// Ensure values are sorted and without duplicates.
		set<string> vals(values.begin(), values.end());
		type.values = vector<string>(vals.begin(), vals.end());

		gi->Add(name, type);
	}

	void AddFactorData(const string &name,
	                   const vector<pair<string, string> > &variables,
	                   const vector<Potential> &potentials)
	{
		rocs::concept::FactorData f;
		f.variables = variables;
		BOOST_FOREACH(const Potential &pot, potentials)
			f.potential[pot.first] = pot.second;

		gi->Add(name, f);
	}

	scoped_ptr<rocs::concept::Graph> graph;
	scoped_ptr<rocs::concept::GraphInformation> gi;
};


/*!
 * a test case for query marginalization,
 * if you plan on adding another sample input consider
 * following the same scheme as this function.
 */
class SampleTestData1 : public TestData {
 public:

	SampleTestData1()
	{
		AddVarType("room", list_of("kitchen")("corridor")("office"));
		AddVarType("object", list_of("beer")("notebook"));
		AddVarType("shape", list_of("square")("oval")("circular")("rect"));

		// Use very distinct values to avoid generating symmetric cases.
		AddFactorData(
			"room_connectivity",
			list_of(std::make_pair(string("room1"), string("room")))
			       (std::make_pair(string("room2"), string("room"))),
			list_of(Potential(list_of("kitchen")("kitchen"),   0.1/4.5))
			       (Potential(list_of("kitchen")("corridor"),  0.2/4.5))
				   (Potential(list_of("kitchen")("office"),    0.3/4.5))
				   (Potential(list_of("corridor")("kitchen"),  0.4/4.5))
				   (Potential(list_of("corridor")("corridor"), 0.5/4.5))
				   (Potential(list_of("corridor")("office"),   0.6/4.5))
				   (Potential(list_of("office")("kitchen"),    0.7/4.5))
				   (Potential(list_of("office")("corridor"),   0.8/4.5))
				   (Potential(list_of("office")("office"),     0.9/4.5)));

		AddFactorData(
			"room_object",
			list_of(std::make_pair(string("room"),   string("room"))  )
			       (std::make_pair(string("object"), string("object"))),
			list_of(Potential(list_of("kitchen")("beer"),      0.19))
			       (Potential(list_of("kitchen")("notebook"),  0.28))
				   (Potential(list_of("corridor")("beer"),     0.47))
				   (Potential(list_of("corridor")("notebook"), 0.56))
				   (Potential(list_of("office")("beer"),       0.85))
				   (Potential(list_of("office")("notebook"),   0.94)));

		BOOST_REQUIRE(gi->CheckConsistency());
	}

	void Run()
	{
		const VariableType *ROOM_TYPE = &gi->types["room"];
		const FactorData   *ROOM_CONN = &gi->factors["room_connectivity"];

		// Create a very simple graph: 2 nodes connected by 1 factor.
		const Variable *room1, *room2;
		graph.reset(new Graph());
		BOOST_REQUIRE(room1 = graph->CreateVariable(ROOM_TYPE));
		BOOST_REQUIRE(room2 = graph->CreateVariable(ROOM_TYPE));
		BOOST_REQUIRE(
			graph->CreateFactor(ROOM_CONN, list_of(room1)(room2)));

		// Check marginalization over 1 variable:
		CheckQuery(list_of(room1), SimpleMarginalize(ROOM_CONN->potential, list_of(0)));
		CheckQuery(list_of(room2), SimpleMarginalize(ROOM_CONN->potential, list_of(1)));

		// Check marginalization over 2 variables:
		// including correct output order is respected.
		CheckQuery(list_of(room1)(room2),
				SimpleMarginalize(ROOM_CONN->potential, list_of(0)(1)));

		CheckQuery(list_of(room2)(room1),
				SimpleMarginalize(ROOM_CONN->potential, list_of(1)(0)));
	}
};

BOOST_AUTO_TEST_CASE(caseTestQueryMarginalization)
{
	SampleTestData1 data;
	data.Run();
}

class SampleTestData2 : public SampleTestData1 {
 public:
	void Run()
	{
		const VariableType *ROOM_TYPE = &gi->types["room"];
		const FactorData   *ROOM_CONN = &gi->factors["room_connectivity"];

		// Create a very simple graph: 2 nodes connected by 1 factor.
		const Variable *room1, *room2;
		graph.reset(new Graph());
		BOOST_REQUIRE(room1 = graph->CreateVariable(ROOM_TYPE));
		BOOST_REQUIRE(room2 = graph->CreateVariable(ROOM_TYPE));
		BOOST_REQUIRE(
			graph->CreateFactor(ROOM_CONN, list_of(room1)(room2)));

		// Create an Imaginary Graph and marginalize on a new node of it.
		vector<double> im_output;
		{
			scoped_ptr<rocs::concept::ImaginaryGraph> im_graph(
					new rocs::concept::ImaginaryGraph(graph.get()));
			const Variable *im_room;
			BOOST_REQUIRE(im_room = im_graph->CreateVariable(ROOM_TYPE));
			BOOST_REQUIRE(im_graph->CreateFactor(ROOM_CONN, list_of(room1)(im_room)));

			Query im_q(im_graph.get());
			im_q.Marginalize(list_of(im_room), &im_output);
		}

		// Perform the same on a Graph.
		vector<double> re_output;
		{
			const Variable *room3;
			BOOST_REQUIRE(room3 = graph->CreateVariable(ROOM_TYPE));
			BOOST_REQUIRE(graph->CreateFactor(ROOM_CONN, list_of(room1)(room3)));

			Query q(graph.get());
			q.Marginalize(list_of(room3), &re_output);
		}

		BOOST_CHECK(re_output == im_output);
	}
};

BOOST_AUTO_TEST_CASE(caseTestQueryOnImaginaryGraph)
{
	SampleTestData2 data;
	data.Run();
}

}  // end anonymous namespace


