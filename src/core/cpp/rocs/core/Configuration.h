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
 * \file Configuration.h
 */


#ifndef _ROCS_CORE_INPUTMIXER_H_
#define _ROCS_CORE_INPUTMIXER_H_

// Stl includes
#include <vector>
#include <iostream>
// ROCS includes
#include "ConfigFileReader.h"
#include "CommandLineHelp.h"


namespace rocs {
namespace core {

using boost::property_tree::ptree;

/*!
 * Class providing access to configuration options for the ROCS components.
 */
class Configuration
{
public:

	/*! Constructor */
	Configuration();

	/*! Destructor. */
	virtual ~Configuration();

	CommandLineHelp commandLineHelp;

	/*!
	 * Add the manually specified command line args
	 * \param argc
	 * \param argv
	 */
	void addCommandlineArgs(int argc, char **argv);

	void addConfigFile(std::string filename);

	inline void addConfigFile(std::vector<std::string>::iterator first,
			std::vector<std::string>::iterator last)
	{
		for (std::vector<std::string>::iterator it = first; it != last; ++it)
			addConfigFile(*it);
	}

	template<class _T>
	_T getValue(std::string path, _T default_value, bool& was_found)
	{
		return ConfigFileReader::getValue<_T>(&_tree, path, default_value, was_found);
	}

	void getChildren(std::string path, int& nb_found, std::vector<ptree>* answer)
	{
		ConfigFileReader::getChildren(&_tree, path, nb_found, answer);
	}

	template<class _T>
	void getValueList(std::string path, std::string key, int& nb_found, std::vector<_T>* ans)
	{
		ConfigFileReader::getValueList<_T>(&_tree, path, key, nb_found, ans);
	}


private:

	/*! Clear all the info parsed till now */
	inline void clear()
	{
		_tree.clear();
	}


private:

	/** The property tree. */
	ptree _tree;

}; // Configuration

} // namespace core
} // namespace rocs

#endif /* _ROCS_CORE_INPUTMIXER_H_ */
