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
 *
 * \author Arnaud Ramey
 * \file InputMixer.h
 */

#ifndef _ROCS_CORE_INPUTMIXER_H_
#define _ROCS_CORE_INPUTMIXER_H_

// stl includes
#include <vector>
#include <iostream>
using namespace std;

// rocs includes
#include "ConfigFileReader.h"
#include "CommandLineHelp.h"
/*!
 * A class for I/O with config files
 *
 */

namespace rocs {
namespace core {

using boost::property_tree::ptree;

class InputMixer {
public:
	InputMixer();

	virtual ~InputMixer();

	CommandLineHelp command_line_help;

	/*
	 * data sources
	 */
	ptree tree;

	/*!
	 * clear all the info parsed till now
	 */
	inline void clear() {
		tree.clear();
	}

	/* ********************************************************
	 * Adding args
	 **********************************************************/
	/*!
	 * Add the manually specified command line args
	 * \param argc
	 * \param argv
	 */
	void addCommandlineArgs(int argc, char **argv);

	void addAllowedConfigFile(string filename);

	inline void addAllowedConfigFile(vector<string>::iterator first, vector<
			string>::iterator last) {
		for (vector<string>::iterator it = first; it != last; ++it)
			addAllowedConfigFile(*it);
	}

	/* ********************************************************
	 * Getting values
	 **********************************************************/
	template<class _T>
	_T getValue(string path, _T default_value, bool& was_found) {
		return ConfigFileReader::getValue<_T>(&tree, path, default_value,
				was_found);
	}
	void getChildren(string path, int& nb_found, vector<ptree>* answer) {
		ConfigFileReader::getChildren(&tree, path, nb_found, answer);
	}
	template<class _T>
	void getValueList(string path, string key, int& nb_found, vector<_T>* ans) {
		ConfigFileReader::getValueList<_T>(&tree, path, key, nb_found, ans);
	}

}; // end class inutMixer

} // namespace core
} // namespace rocs

#endif /* _ROCS_CORE_INPUTMIXER_H_ */
