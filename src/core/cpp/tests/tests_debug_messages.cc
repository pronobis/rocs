// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2010  Arnaud Ramey, Andrzej Pronobis
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
 * \file tests_debug_messages.cc
 *
 * \date Aug 17, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#include "Core.h"

inline void test_debug() {
	DEBUGPRINT("DEBUGPRINT");
	DEBUGPRINTF("DEBUGPRINTF, %s", "info");
	debugPrint_lvl1("debugPrintf_lvl1");
	debugPrintf_lvl1("debugPrintf_lvl1 info:%s", "info");
	debugPrint_lvl2("debugPrintf_lvl2");
	debugPrintf_lvl2("debugPrintf_lvl2 info:%s", "info");
	debugPrint_lvl3("debugPrintf_lvl3");
	debugPrintf_lvl3("debugPrintf_lvl3 info:%s", "info");
}

inline void test_assert() {
	for (int var = 0; var < 100; ++var) {
		cout << "DbgAssert '" << var << " < 5'" << endl;
		DbgAssert(var < 5);
		cout << "Assert '" << var << " < 9'" << endl;
		Assert(var < 9);
	}
}

inline void test_error() {
	Error(-1, "error message");
}

inline void test_split() {
	debugPrint_lvl1("test_split()");

	vector<string> words;
	string sentence = "Hello+world test";
	rocs::core::split_string(sentence, words, " +");
	for (vector<string>::iterator it = words.begin() ; it < words.end() ; ++it)
		cout << "Word:" << *it << endl;
}

int main(int argc, char **argv) {
	//      test_debug();
	//test_assert();
	//      test_error();
	test_split();

	std::cout << "end of main()" << std::endl;
}
