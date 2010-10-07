/*
 * tests_input_mixer.cc
 *
 *  Created on: Aug 17, 2010
 *      Author: arnaud
 */

#include "InputMixer.h"

#define ROCSDIR "../../../"
#define DATADIR ROCSDIR "data/"

#include <iostream>
using namespace std;
using rocs::core::InputMixer;

/*!
 * this builds an input mixer with 2 config files and [argc, argc]
 */
inline Configuration test_input_mixer(int argc, char **argv) {
	debugPrintf_lvl3("test_input_mixer(argc=%i)", argc);
	Configuration inputMixer;

	// through an object
	char filename_in[100];
	sprintf(filename_in, "%s%s", DATADIR, "configfiles/debug_settings.xml");
	inputMixer.addAllowedConfigFile(filename_in);

	sprintf(filename_in, "%s%s", DATADIR, "configfiles/include3.xml");
	inputMixer.addAllowedConfigFile(filename_in);

	inputMixer.addCommandlineArgs(argc, argv);

	printf("\ntree:\n");
	rocs::core::ConfigFileReader::printTree(&inputMixer.tree);

	return inputMixer;
}

/*!
 * this function will break a single line instruction into the usual [argc, argv]
 */
inline Configuration test_input_mixer_string(string line_string) {
	debugPrintf_lvl3("test_input_mixer('%s')", line_string.c_str());

	/* conversion argc argv */
	char line_char[500], *argv[80], *token;
	int argc = 0;
	memcpy(line_char, line_string.c_str(), line_string.length() + 1);
	token = strtok(line_char, " ");
	while (token != NULL) {
		argc++;
		argv[argc] = token;
		//printf("%s\n", pch);
		token = strtok(NULL, " ");//continue to tokenize the string
	}
	//	debugPrintf_lvl3("argc:%i", argc);
	/* end conversion argc argv */

	return test_input_mixer(argc, argv);
}

/*!
 *
 */
inline void test_input_mixer_simple() {
	Configuration inputMixer = test_input_mixer_string(
			"./test.exe -command_line_arg OK --toto 25 -x");
	// read from command line first
	bool was_found;
	string query, result;

	query = "debug.filename";
	result = inputMixer.getValue<string> (query, "default_value", was_found);
	printf("query:'%s', was_found:%i, result:'%s'\n\n", query.c_str(),
			was_found, result.c_str());

	query = "command_line_arg";
	result = inputMixer.getValue<string> (query, "default_value", was_found);
	printf("query:'%s', was_found:%i, result:'%s'\n\n", query.c_str(),
			was_found, result.c_str());

	// read something not existing
	query = "debug2.filename";
	result = inputMixer.getValue<string> (query, "default_value", was_found);
	printf("query:'%s', was_found:%i, result:'%s'\n\n", query.c_str(),
			was_found, result.c_str());

}

/*!
 *
 */
inline void test_input_mixer_list() {
	string instr = "./test.exe -new_item.id xxx -new_item2.id xyz";
	Configuration inputMixer = test_input_mixer_string(instr);

	// read a list of values
	vector<string> values;
	int nb_found;
	inputMixer.getValueList<string> ("", "id", nb_found, &values);
	printf("nb_found:%i\n", nb_found);
	for (vector<string>::iterator it = values.begin(); it < values.end(); ++it) {
		printf(" -> item:%s\n", (*it).c_str());
	}
}

int main(int argc, char **argv) {
	//test_input_mixer_string(argc, argv);
	//test_input_mixer_simple();
	test_input_mixer_list();

	std::cout << "end of main()" << std::endl;
}
