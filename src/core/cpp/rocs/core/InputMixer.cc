/*
 * InputMixer.cc
 *
 *  Created on: Aug 17, 2010
 *      Author: arnaud
 */

#include "InputMixer.h"

rocs::core::InputMixer::InputMixer() {
	clear();
}

rocs::core::InputMixer::~InputMixer() {
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
static inline bool is_variable_name(string& word, string& ans) {
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

void rocs::core::InputMixer::addCommandlineArgs(int argc, char **argv) {
	debugPrintf_lvl3("add_commandline_args(%i args)", argc);

	// check the help
	for (int word_index = 1; word_index <= argc; ++word_index) {
		string current_word = argv[word_index];
		//debugPrintf_lvl1("Current word:'%s'", current_word.c_str());
		int word_found = command_line_help.containsName(current_word);
		//debugPrintf_lvl1("word_found :'%i'", word_found);
		if (word_found != -1) {
			CommandLineHelp::OptionDescription op =
					command_line_help.options.at(word_found);
			debugPrintf_lvl1("Description:%s", op.description.c_str());
			if (!op.with_complement)
				return;
		}
	}

	// parse the tree
	for (int word_index = 1; word_index <= argc; ++word_index) {
		string current_word = argv[word_index];
		string variable_name;
		debugPrintf_lvl1("Current word:'%s'", current_word.c_str());

		bool is_correct_variable_name = is_variable_name(current_word,
				variable_name);

		// if the current variable name is not conform, skip
		if (!is_correct_variable_name) {
			debugPrintf_lvl1("'%s' is not a correct variable name !", current_word.c_str());
			continue;
		}

		if (word_index >= argc) {
			debugPrintf_lvl1("'%s' is a correct variable name, but the last argument!", current_word.c_str());
			continue;
		}

		// adding the next value
		++word_index;
		string value = argv[word_index];
		debugPrintf_lvl1("New value : '%s'='%s'", variable_name.c_str(), value.c_str());

		// add the variable
		tree.add(variable_name, value);
	} // end loop words
}

void rocs::core::InputMixer::addAllowedConfigFile(string filename) {
	debugPrintf_lvl3("add_allowed_config_file('%s')", filename.c_str());
	// read the new file in a new tree
	ptree new_tree;
	ConfigFileReader::readFileAndCheckIncludes(filename, &new_tree, true);
	// add it to the root of our tree
	tree.insert(tree.end(), new_tree.begin(), new_tree.end());

	ConfigFileReader::printTree(&tree);
}
