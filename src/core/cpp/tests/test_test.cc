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
 * Example of a test case. Also serves as a "test" of google test.
 * For more information see:
 * https://code.google.com/p/googletest/wiki
 * \author Andrzej Pronobis
 * \file test_test.cc
 */

// ROCS includes
/* Nothing for now. This is just an example. */
// Google Test
#include "gtest/gtest.h"


// ------------------------------------------------------------
// First test in this test case. Tests assertions.
// ------------------------------------------------------------
TEST(test, asserts)
{
  ASSERT_FALSE(false);
  ASSERT_TRUE(true);
}


// ------------------------------------------------------------
// Second test in this test case. Tests expects.
// ------------------------------------------------------------
TEST(test, expects)
{
  EXPECT_FALSE(false);
  EXPECT_TRUE(true);
}

