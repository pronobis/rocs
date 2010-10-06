/*
 * tests_debug_messages.cc
 *
 *  Created on: Aug 17, 2010
 *      Author: arnaud
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
