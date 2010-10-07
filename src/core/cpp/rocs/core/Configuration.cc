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
 * Configuration class.
 * \author Arnaud Ramey
 * \file Configuration.cc
 */


#include "Configuration.h"

using namespace rocs::core;
using namespace std;


// ---------------------------------------------
Configuration::Configuration()
{
	clear();
}


// ---------------------------------------------
Configuration::~Configuration()
{
	clear();
}


/*!
 * determine if a string corresponds to a variable name, that is starts with "-" or "--"
 *
 * \param     word
 *              the string to analyze
 * \param     ans
 *              the cleaned name of the variable, if it was a variable
 * \return
 */
static inline bool is_variable_name(string& word, string& ans)
{
	if (word[0] != '-')
		return false;

	uint variable_name_begin_index = 0;
	while (word[variable_name_begin_index] == '-') {
		++variable_name_begin_index;
		if (variable_name_begin_index >= word.size())
			return false;
	}
	ans = word.substr(variable_name_begin_index);
	return true;
}

void rocs::core::Configuration::addCommandlineArgs(int argc, char **argv) {
	debug3("add_commandline_args(%i args)", argc);

	// check the help
	for (int word_index = 1; word_index <= argc; ++word_index) {
		string current_word = argv[word_index];
		//debug1("Current word:'%s'", current_word.c_str());
		int word_found = commandLineHelp.containsName(current_word);
		//debug1("word_found :'%i'", word_found);
		if (word_found != -1) {
			CommandLineHelp::OptionDescription op =
					commandLineHelp.options.at(word_found);
			debug1("Description:%s", op.description.c_str());
			if (!op.with_complement)
				return;
		}
	}

	// parse the tree
	for (int word_index = 1; word_index <= argc; ++word_index) {
		string current_word = argv[word_index];
		string variable_name;
		debug1("Current word:'%s'", current_word.c_str());

		bool is_correct_variable_name = is_variable_name(current_word,
				variable_name);

		// if the current variable name is not conform, skip
		if (!is_correct_variable_name) {
			debug1("'%s' is not a correct variable name !", current_word.c_str());
			continue;
		}

		if (word_index >= argc) {
			debug1("'%s' is a correct variable name, but the last argument!", current_word.c_str());
			continue;
		}

		// adding the next value
		++word_index;
		string value = argv[word_index];
		debug1("New value : '%s'='%s'", variable_name.c_str(), value.c_str());

		// add the variable
		_tree.add(variable_name, value);
	} // end loop words
}

void rocs::core::Configuration::addConfigFile(string filename) {
	debug3("add_allowed_config_file('%s')", filename.c_str());
	// read the new file in a new tree
	ptree new_tree;
	ConfigFileReader::readFileAndCheckIncludes(filename, &new_tree, true);
	// add it to the root of our tree
	_tree.insert(_tree.end(), new_tree.begin(), new_tree.end());

	ConfigFileReader::printTree(&_tree);
}
