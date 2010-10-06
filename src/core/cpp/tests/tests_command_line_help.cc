/*
 * tests_command_line_help.cc
 *
 *  Created on: Sep 7, 2010
 *      Author: arnaud
 */

#include "InputMixer.h"

#define ROCSDIR "../../../"
#define DATADIR ROCSDIR "data/"
using namespace rocs::core;

inline void test_command_line_help(int argc, char** argv) {
	debugPrintf_lvl3("test_command_line_help(argc=%i)", argc);

	// set up the mixer
	InputMixer mixer;
	char filename_in[100];
	sprintf(filename_in, "%s%s", DATADIR, "configfiles/debug_settings.xml");
	mixer.addAllowedConfigFile(filename_in);

	// config the command line
	CommandLineHelp* help = &mixer.command_line_help;
	vector<string> names;
	names.push_back("--h");
	names.push_back("-help");
	help->addOptionWithoutValue(&names, "display this help");

	mixer.addCommandlineArgs(argc, argv);
}

/*!
 * this function will break a single line instruction into the usual [argc, argv]
 */
inline void test_command_line_help_string(string line_string) {
	debugPrintf_lvl3("test_command_line_help_string('%s')", line_string.c_str());

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

	test_command_line_help(argc, argv);
}

int main(int argc, char **argv) {
	if (argc > 1)
		test_command_line_help(argc, argv);
	else
		test_command_line_help_string("./test --h");

	cout << "end of main()" << endl;
}
