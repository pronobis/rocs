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
 * Example test suite.
 * For more information see:
 * http://www.boost.org/doc/libs/1_44_0/libs/test/doc/html/utf/user-guide.html
 * \author Andrzej Pronobis
 * \file test_test1.cc
 */

// Boost
#include <boost/test/unit_test.hpp>
// ROCS
/* Nothing for now. This is just an example*/

#include <boost/shared_ptr.hpp>

class A
{
	int a;
};


class B: public A
{
public:
	B(): b(int()), e(11) {}
	int b;
	double d;
	double e;
};


class C: public A
{
public:
	C(): c(double()) {}
	double c;
};


/*! Define first test case. */
BOOST_AUTO_TEST_CASE( case1 )
{
	boost::shared_ptr<A> p1(new B());
	boost::shared_ptr<A> p2(new C());

	boost::shared_ptr<B> p3 = boost::static_pointer_cast<B, A>(p1);
	boost::shared_ptr<B> p4 = boost::static_pointer_cast<B, A>(p2);

	BOOST_CHECK( p3->e == 11);
	BOOST_CHECK( p4->e == 11);


	BOOST_CHECK( 0 == 0 );
	BOOST_REQUIRE( 0 == 0 );
}

/*! Define second test case. */
BOOST_AUTO_TEST_CASE( case2 )
{
	BOOST_CHECK( 1 == 1 );
	BOOST_REQUIRE( 1 == 1 );
}

