/*
 * CommandLineHelp.cc
 *
 *  Created on: Sep 7, 2010
 *      Author: arnaud
 */


// ROCS
#include "rocs/core/CommandLineHelp.h"
#include "rocs/core/debug.h"

using namespace rocs::core;

CommandLineHelp::CommandLineHelp() {
	// TODO Auto-generated constructor stub

}

CommandLineHelp::~CommandLineHelp() {
	// TODO Auto-generated destructor stub
}


bool CommandLineHelp::OptionDescription::containsName(std::string name)
{
	for (std::vector<std::string>::iterator it = names.begin(); it < names.end(); ++it) {
		//debug3("Comparing '%s' and '%s'", name.c_str(), it->c_str());
		if (*it == name) {
			debug3("We found an option corresponding to '%s' ( first name:'%s')", name.c_str(), firstName().c_str());
			return true;
		}
	} // end for names
	return false;
} // end containsName()
