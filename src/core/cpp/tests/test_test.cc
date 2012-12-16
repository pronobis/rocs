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
 * Example of a test case. Also serves as a "test" of google test.
 * For more information see:
 * https://code.google.com/p/googletest/wiki/V1_6_Documentation
 * \author Andrzej Pronobis
 * \file test_test1.cc
 */

// Google Test
#include "gtest/gtest.h"
// ROCS
/* Nothing for now. This is just an example*/


/*! Define first test in this test case. */
TEST(Test, Asserts) {
  ASSERT_FALSE(false);
  ASSERT_TRUE(true);
}


/*! Define second test in this test case. */
TEST(Test, Expects) {
  EXPECT_FALSE(false);
  EXPECT_TRUE(true);
}

