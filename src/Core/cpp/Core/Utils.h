/*
 * Utils.h
 *
 *  Created on: Sep 30, 2010
 *      Author: arnaud
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>
//#include <iterator>
//#include <iostream>
//#include <sstream>
using namespace std;

#include <boost/algorithm/string.hpp>

namespace rocs {
namespace core {

static inline void split_string(string sentence, vector<string>& sentence_words,
		string separators) {
	//	istringstream iss(sentence);
	//	copy(istream_iterator<string> (iss), istream_iterator<string> (),
	//			back_inserter<vector<string> > (sentence_words));
	boost::split(sentence_words, sentence, boost::is_any_of(separators));
}

} // namespace core
} // namespace rocs


#endif /* UTILS_H_ */
