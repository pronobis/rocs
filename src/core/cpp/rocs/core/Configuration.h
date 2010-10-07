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

// ROCS includes
#include "rocs/core/debug.h"
#include "rocs/core/error.h"
#include "rocs/core/types.h"
//#include "ConfigFileReader.h"
#include "CommandLineHelp.h"
// BOOST includes
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/foreach.hpp>
// STL includes
#include <vector>
#include <iostream>

namespace rocs
{
namespace core
{

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
		return getValue<_T> (&_tree, path, default_value, was_found);
	}

	/*!
	 *
	 */
	template<class _T>
	_T getValue(std::string path, _T default_value)
	{
		bool wasFound;
		return getValue<_T> (path, default_value, wasFound);
	}

	/*!
	 *
	 */
	void getChildren(std::string path, int& nb_found,
			std::vector<ptree>* answer)
	{
		getChildren(&_tree, path, nb_found, answer);
	}

	/*!
	 *
	 */
	template<class _T>
	void getValueList(std::string path, std::string key, std::vector<_T>& ans)
	{
		getValueList<_T> (&_tree, path, key, ans);
	}

	/*!
	 * Prints the the whole configuration loaded.
	 */
	void printConfiguration()
	{
		printTree(&_tree);
	}

private:

	/** the command line help */
	CommandLineHelp commandLineHelp;

	/** The property tree. */
	ptree _tree;

	/*! Clear all the info parsed till now */
	inline void clear()
	{
		_tree.clear();
	}

	/*!
	 * open a file, parse it
	 * \param filename
	 *          the name of the file to parse
	 * \param tree
	 *          the tree to poulate
	 * \param include_allowed
	 * 	        if <code>true</code>, allow the xml include tags :
	 *          will parse the corresponding files and replace them
	 */
	static void readFileAndCheckIncludes(std::string filename, ptree* tree,
			bool include_allowed);

	/*!
	 * Parses a file into the tree
	 * \param filename
	 *          the file to parse
	 * \param tree
	 *          the tree to populate with the parsed file
	 */
	static void readFfile(std::string filename, ptree* tree);

	/*!
	 * Determine if a string corresponds to a variable name,
	 * that is starts with "-" or "--".
	 * \param word		The string to analyze.
	 * \param varName	The cleaned name of the variable, if it was a variable.
	 * \return			True if valid variable name.
	 */
	static bool isVariableName(const std::string& word, std::string& varName);

	/*!
	 * check if a tree contains some include tags
	 *
	 * \param     relative_path
	 *              the path of the file that generated the tree
	 * \param     tree
	 *              the tree that might contain some include tags
	 */
	static void checkIncludes(std::string relative_path, ptree* tree);

	/*!
	 * delete the \<xmlattr\> nodes made by RapidXML
	 *
	 * \param     tree
	 *              the tree to clean from its \<xmlattr\> nodes
	 */
	static void removeXmlattr(ptree* tree);

	/*!
	 * display the structure of a given tree
	 *
	 * \param     tree
	 *              the tree to display
	 * \param     depth
	 *              the depth of the current node (for indentation)
	 */
	static void printPtreeRec(ptree* tree, int depth);

	/*!
	 * display the structure of the tree inside the config file
	 */
	static void printTree(ptree* tree);

	/*!
	 *
	 * \param tree
	 *          the tree to search in
	 * \param path
	 *          the path to follow from the root of the tree
	 * \param was_found
	 *          is changed to true if we found the wanted value
	 * \return
	 *          the found value in the tree
	 */
	static std::string getValueAsString(ptree* tree, std::string path,
			bool& was_found)
	{
		rocsDebug3("getValueAsString('%s')", path.c_str());
		was_found = false;
		bool search_for_son_value = false;
		std::string key_to_search, son_key_to_search;

		if (path == "")
		{
			rocsDebug3("Returning the value of the current tree.");
			was_found = true;
			return tree->get_value("");
		}

		/* determine the key to search */
		size_t dot_position = path.find_first_of('.');
		if (dot_position == std::string::npos)
		{
			// there is no dot in the path -> last step, find the good son
			search_for_son_value = true;
			key_to_search = path;
		}
		else
		{
			search_for_son_value = false;
			key_to_search = path.substr(0, dot_position);
			son_key_to_search = path.substr(dot_position + 1);
		}
		rocsDebug2("Searching the key '%s' in the sons...",
				key_to_search.c_str());

		/* serarch it */
		// backwards search
		for (ptree::reverse_iterator son_iter = tree->rbegin(); son_iter
				!= tree->rend(); ++son_iter)
		{
			std::string son_node_name = son_iter->first;
			ptree son_tree = son_iter->second;
			std::string son_node_value = son_tree.get_value("");
			rocsDebug3("Node:'%s' = '%s'", son_node_name.c_str(),
					son_node_value.c_str());

			if (son_node_name == key_to_search)
			{
				// we found the key
				if (search_for_son_value)
				{
					was_found = true;
					return son_node_value;
				}
				else
					return getValueAsString(&son_tree, son_key_to_search,
							was_found);
			}
		} // end loop sons

		// we didin't find the key in the sons
		rocsDebug1("Couldn't find the key '%s' in the sons !",
				key_to_search.c_str());
		return "";
	}

	/*!
	 *
	 * \param tree
	 *          the tree to search in
	 * \param path
	 *          the path to follow from the root of the tree
	 * \param was_found
	 *          is changed to true if we found the wanted value
	 * \param default_value
	 *          the value to return if we can't find the given path
	 * \return
	 *          the found value in the tree
	 */
	template<class _T>
	static _T getValue(ptree* tree, std::string path, _T default_value,
			bool& was_found)
	{
		rocsDebug3("getValue<_T>(%s)", path.c_str());
		rocsError("Templated function non implemented");
	}

	/*!
	 * return the children of a tree following a given path
	 * \param tree
	 *          the tree where to search
	 * \param path
	 *          the path to follow
	 * \param nb_found
	 *          the number of sons
	 * \param answer
	 *          the vector to populate with the answers
	 */
	static void getChildren(ptree* tree, std::string path, int& nb_found,
			std::vector<ptree>* answer)
	{
		nb_found = 0;
		rocsDebug3("get_children(path:'%s')", path.c_str());

		if (path == "")
		{ // we need to return these nodes
			rocsDebug1(
					"Searched path is empty, meaning we want the sons ! Returning the %i sons.",
					(int) tree->size());
			//printTree(tree);
			answer->clear();
			nb_found = 0;
			for (ptree::iterator son_iter = tree->begin(); son_iter
					!= tree->end(); ++son_iter)
			{
				ptree sonTree = son_iter->second;
				//rocsDebug3("pushing back :");
				//printTree(&sonTree);
				answer->push_back(sonTree);
				++nb_found;
			} // end loop sons
			return;
		} // end path empty

		/* determine the key to search */
		std::string key_to_search, son_key_to_search;
		size_t dot_position = path.find_first_of('.');
		if (dot_position == std::string::npos)
		{
			key_to_search = path;
			son_key_to_search = "";
		}
		else
		{
			key_to_search = path.substr(0, dot_position);
			son_key_to_search = path.substr(dot_position + 1);
		}
		rocsDebug2("Searching the key '%s' in the sons...",
				key_to_search.c_str());

		/* serarch it */
		// backwards search
		for (ptree::reverse_iterator son_iter = tree->rbegin(); son_iter
				!= tree->rend(); ++son_iter)
		{
			std::string son_node_name = son_iter->first;
			ptree son_tree = son_iter->second;
			std::string son_node_value = son_tree.get_value("");
			rocsDebug3("Node:'%s' = '%s'", son_node_name.c_str(),
					son_node_value.c_str());

			if (son_node_name == key_to_search)
			{
				getChildren(&son_tree, son_key_to_search, nb_found, answer);
				return;
			}
		} // end loop sons

		// we didin't find the key in the sons
		rocsDebug1("Couldn't find the key '%s' in the sons !",
				key_to_search.c_str());
	}

	/*!
	 * Returns a list of values.
	 * For instance, getValueList(A, "", "key")
	 * will return [3, 1]
	 *
	 * A
	 * |
	 * |--B
	 * | |
	 * | |--key=3
	 * |
	 * |--foo
	 * | |
	 * | |--key2=3
	 * |
	 * |--
	 * | |
	 * | |--key=1
	 * | |
	 * | |--key2=5
	 *
	 * \param tree
	 *          the tree to search in
	 * \param path
	 *          the path to follow from the root of the tree
	 * \param key
	 *          the tag to find
	 * \param nb_found
	 *          the number of found values (should be equal to ans->size())
	 * \param ans
	 *          the vector where to store the answers
	 */
	template<class _T>
	static void getValueList(ptree* tree, std::string path, std::string key,
			std::vector<_T>& ans)
	{
		rocsDebug3("getValueList(path:'%s', key:'%s')", path.c_str(),
				key.c_str());

		ans.clear();

		// get the wanted sons
		int nb_sons;
		std::vector<ptree> sons;
		getChildren(tree, path, nb_sons, &sons);
		rocsDebug3("children obtained, nb:%i", nb_sons);
		for (std::vector<ptree>::iterator it = sons.begin(); it < sons.end(); ++it)
			printTree(&(*it));
		if (nb_sons == 0)
			return;

		/* get the values */
		std::string::size_type dot_pos = key.find(".");
		std::string keyHead = (dot_pos == std::string::npos ? key : key.substr(
				0, dot_pos - 1));
		std::string keyTail = (dot_pos == std::string::npos ? "" : key.substr(
				dot_pos + 1));
		rocsDebug3("We remove the first path, keyHead, '%s', keyTail:'%s'",
				keyHead.c_str(), keyTail.c_str());
		for (std::vector<ptree>::iterator son_it = sons.begin(); son_it
				< sons.end(); ++son_it)
		{
			//rocsDebug3("Current son:");
			//printTree(&(*son_it));
			for (ptree::iterator sonson_it = (*son_it).begin(); sonson_it
					!= (*son_it).end(); ++sonson_it)
			{
				if (sonson_it->first != keyHead)
					continue;
				bool was_found = false;
				ptree sonson = sonson_it->second;
				_T value = getValue<_T> (&sonson, keyTail,
						Type<_T>::defaultValue(), was_found);
				if (was_found)
					ans.push_back(value);
			} // end loop grandsons
		} // end loop sons
	}

}; // Configuration

/* template specs */
template<> // string
std::string Configuration::getValue(ptree* tree, std::string path,
		std::string default_value, bool& was_found);
template<> // int
int Configuration::getValue(ptree* tree, std::string path, int default_value,
		bool& was_found);
template<> // double
double Configuration::getValue(ptree* tree, std::string path,
		double default_value, bool& was_found);

} // namespace core
} // namespace rocs

#endif /* _ROCS_CORE_INPUTMIXER_H_ */
