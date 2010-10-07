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

	/*! Default constructor. */
	Configuration();

	/*! Constructor, processes command line arguments. */
	Configuration(int argc, char const **argv)
	{
		addCommandLineArgs(argc, argv);
	}

	/*! Destructor. */
	virtual ~Configuration();

	/*!
	 * Add command line arguments to be processed.
	 * \param argc	Number of arguments
	 * \param argv	Arrays of arguments. The first argument is ignored.
	 */
	void addCommandLineArgs(int argc, char const **argv);

	/*!
	 * Adds a single config file.
	 * \param fileName	Full path to the file.
	 */
	void addConfigFile(std::string fileName);

	inline void addConfigFile(std::vector<std::string>::iterator first,
			std::vector<std::string>::iterator last)
	{
		for (std::vector<std::string>::iterator it = first; it != last; ++it)
			addConfigFile(*it);
	}

	/*!
	 *
	 */
	template<class _T>
	_T getValue(std::string path, _T default_value, bool& was_found)
	{
		return ConfigFileReader::getValue<_T>(&_tree, path, default_value, was_found);
	}

	/*!
	 *
	 */
	template<class _T>
	_T getValue(std::string path, _T default_value)
	{
		bool wasFound;
		return getValue<_T>(path, default_value, wasFound);
	}

	/*!
	 *
	 */
	void getChildren(std::string path, int& nb_found, std::vector<ptree>* answer)
	{
		ConfigFileReader::getChildren(&_tree, path, nb_found, answer);
	}

	/*!
	 *
	 */
	template<class _T>
	void getValueList(std::string path, std::string key, std::vector<_T>& ans)
	{
		ConfigFileReader::getValueList<_T>(&_tree, path, key, ans);
	}

	/*!
	 * Prints the the whole configuration loaded.
	 */
	void printConfiguration()
	{
		rocs::core::ConfigFileReader::printTree(&_tree);
	}


private:

	/*! Clear all the info parsed till now */
	inline void clear()
	{
		_tree.clear();
	}

	/*!
	 * Determine if a string corresponds to a variable name,
	 * that is starts with "-" or "--".
	 * \param word		The string to analyze.
	 * \param varName	The cleaned name of the variable, if it was a variable.
	 * \return			True if valid variable name.
	 */
	bool isVariableName(const std::string& word, std::string& varName) const;


private:

	CommandLineHelp commandLineHelp;

	/** The property tree. */
	ptree _tree;

}; // Configuration

} // namespace core
} // namespace rocs

#endif /* _ROCS_CORE_INPUTMIXER_H_ */
