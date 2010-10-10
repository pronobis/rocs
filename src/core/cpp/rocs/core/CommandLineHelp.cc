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
 * \file CommandLineHelp.cc
 *
 * \date Sep 7, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
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
		//rocsDebug3("Comparing '%s' and '%s'", name.c_str(), it->c_str());
		if (*it == name) {
			rocsDebug3("We found an option corresponding to '%s' ( first name:'%s')", name.c_str(), firstName().c_str());
			return true;
		}
	} // end for names
	return false;
} // end containsName()
