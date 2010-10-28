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

#include "rocs/core/utils.h" // for fileExists()
#include "rocs/core/error.h"

using namespace rocs::core;
using namespace std;

// cf http://www.boost.org/doc/libs/1_41_0/doc/html/boost_propertytree/parsers.html

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

// ---------------------------------------------
bool Configuration::isVariableName(const string& word, string& varName)
{
	if (word[0] != '-')
		return false;

	uint variable_name_begin_index = 0;
	while (word[variable_name_begin_index] == '-')
	{
		++variable_name_begin_index;
		if (variable_name_begin_index >= word.size())
			return false;
	}
	varName = word.substr(variable_name_begin_index);
	return true;
}

// ---------------------------------------------
void Configuration::addCommandLineArgs(int argc, char const **argv)
{
	rocsDebug3("add_commandline_args(%i args)", argc);

	// check the help
	for (int word_index = 1; word_index <= argc; ++word_index)
	{
		string current_word = argv[word_index];
		//rocsDebug1("Current word:'%s'", current_word.c_str());
		int word_found = commandLineHelp.containsName(current_word);
		//rocsDebug1("word_found :'%i'", word_found);
		if (word_found != -1)
		{
			CommandLineHelp::OptionDescription op = commandLineHelp.options.at(
					word_found);
			rocsDebug1("Description:%s", op.description.c_str());
			if (!op.with_complement)
				return;
		}
	}

	// parse the tree
	for (int word_index = 1; word_index <= argc; ++word_index)
	{
		string current_word = argv[word_index];
		string variable_name;
		rocsDebug1("Current word:'%s'", current_word.c_str());

		bool is_correct_variable_name = isVariableName(current_word,
				variable_name);

		// if the current variable name is not conform, skip
		if (!is_correct_variable_name)
		{
			rocsDebug1("'%s' is not a correct variable name !",
					current_word.c_str());
			continue;
		}

		if (word_index >= argc)
		{
			rocsDebug1(
					"'%s' is a correct variable name, but the last argument!",
					current_word.c_str());
			continue;
		}

		// adding the next value
		++word_index;
		string value = argv[word_index];
		rocsDebug1("New value : '%s'='%s'", variable_name.c_str(),
				value.c_str());

		// add the variable
		_tree.add(variable_name, value);
		//printConfiguration();
	} // end loop words
}

// ---------------------------------------------
void rocs::core::Configuration::addConfigFile(string filename)
		throw (core::IOException)
{
	rocsDebug3("add_allowed_config_file('%s')", filename.c_str());
	/*
	 * check the file exists
	 */
	if (!rocs::core::fileExists(filename))
		rocsIOException("The given file '%s' does not exist.", filename.c_str());
	// read the new file in a new tree
	ptree new_tree;
	readFileAndCheckIncludes(filename, &new_tree, true);
	// add it to the root of our tree
	_tree.insert(_tree.end(), new_tree.begin(), new_tree.end());
}

/*!
 * guess the type of file according to the extension
 * \param     filename the config filename
 * \return    the guess type of file
 */
inline int guessType(std::string filename)
{
	size_t last_dot_pos = filename.find_last_of('.');
	//	cout << "last_dot_pos:" << last_dot_pos << endl;
	// if there is no dot in the filename, return unknown type
	// TODO soemthing smarter ? (read the file and see if it starts with a tag ?
	if (last_dot_pos == std::string::npos)
		return TYPE_UNKNOWN;

	// get the extension of the filename
	std::string extension = filename.substr(last_dot_pos + 1);
	//	cout << "extension:" << extension << endl;
	if (extension == "xml")
		return TYPE_XML;
	else if (extension == "json" || extension == "jso" || extension == "jsn")
		return TYPE_JSON;
	else if (extension == "ini")
		return TYPE_INI;
	else if (extension == "info" || extension == "inf" || extension == "nfo")
		return TYPE_INFO;
	return TYPE_UNKNOWN;
}

void rocs::core::Configuration::checkIncludes(const string relative_path,
		ptree* tree, const string tagToFind1, const string tagToFind2)
{
	//rocsDebug3("checkIncludes()");
	//const char* tag_to_find1 = "xi:include";
	//const char* tag_to_find2 = "<xmlattr>.href";

	// if we allow the include tags, check if there are some
	for (ptree::iterator son_iter = tree->begin(); son_iter != tree->end(); ++son_iter)
	{
		string son_node_name = son_iter->first;
		//rocsDebug3("Son-node_name:'%s'", son_node_name.c_str());

		boost::optional<ptree &> found_son =
				son_iter->second.get_child_optional(tagToFind2);
		bool found_tag1 = (son_node_name == tagToFind1);
		bool found_tag2 = (found_son != NULL);
		bool is_include = found_tag1 && found_tag2;
		//debugPrintf_lvl2("found_tag1:%d, found_tag2:%d, is_include:%d", found_tag1, found_tag2, is_include);

		if (is_include)
		{
			rocsDebug3("'%s' found !", tagToFind2.c_str());
			/*
			 * get the filename
			 */
			ptree real_found_son = (*found_son);
			string file_to_include = real_found_son.get_value("");
			file_to_include = relative_path + file_to_include;
			rocsDebug3("Including the file:'%s'", file_to_include.c_str());
			/*
			 * parse the file
			 */
			ptree pt;
			readFileAndCheckIncludes(file_to_include, &pt, true);
			/*
			 * remove the node
			 */
			son_iter = tree->erase(son_iter);
			//son_iter = tree->begin();
			//tree->erase(son_iter);
			/*
			 * insert the created tree at this place
			 */
			// typedef basic_ptree<Key, Data, KeyCompare> self_type;
			// typedef std::pair<const Key, self_type>      value_type;
			// iterator insert(iterator where, const value_type &value);
			//ptree::value_type vt("", pt);
			//tree->insert(son_iter, vt);
			tree->insert(son_iter, pt.begin(), pt.end());
			son_iter--;
		}
		else
			// node is not an include - check if it contains some includes
			checkIncludes(relative_path, &(son_iter->second), tagToFind1,
					tagToFind2);
	} // end loop on sons
}

int rocs::core::Configuration::readFfile(string filename, ptree* tree)
		throw (core::IOException)
{
	rocsDebug3("read_file('%s')", filename.c_str());

	// store the filename
	//	this->filename = filename;

	// guess the type of the file
	int guessed_filetype = guessType(filename);

	// read the file
	try
	{
		switch (guessed_filetype)
		{
		case TYPE_XML:
			read_xml(filename, *tree);
			break;
		case TYPE_JSON:
			read_json(filename, *tree);
			break;
		case TYPE_INI:
			read_ini(filename, *tree);
			break;
		case TYPE_INFO:
			read_info(filename, *tree);
			break;
		case TYPE_UNKNOWN:
		default:
			rocsIOException("Impossible to guess the config file type of '%s'", filename.c_str())
			;
			break;
		} // end switch
	} // end try
	catch (boost::property_tree::file_parser_error e)
	{
		string msg = e.what();
		rocsIOException("'%s'", msg.c_str());
	} // end catch

	return guessed_filetype;
}

void rocs::core::Configuration::removeXmlattr(ptree* tree)
{
	//rocsDebug3("removeXmlattr()");
	//printTree(tree);

	for (ptree::iterator son_iter = tree->begin(); son_iter != tree->end(); ++son_iter)
	{
		string son_node_name = son_iter->first;
		ptree* son_tree = &son_iter->second;
		//string node_value = son_tree.getValue("");
		//rocsDebug3("node_name:'%s'", son_node_name.c_str());

		if (son_node_name == "<xmlattr>")
		{
			rocsDebug3("<xmlattr> found !");
			/* insert the sons */
			for (ptree::iterator sonson = son_tree->begin(); sonson
					!= son_tree->end(); ++sonson)
			{
				son_iter = tree->insert(son_iter, *sonson);
				son_iter++;
				//rocsDebug3("node_name:'%s'", node_name.c_str());
			} // end loop sons

			/* remove the node */
			son_iter = tree->erase(son_iter);
			son_iter--;
		}
		else
			removeXmlattr(son_tree);
	}
}

inline void determineTagsToFind(int fileType, string& tag1, string& tag2)
{
	switch (fileType)
	{
	case TYPE_XML:
		tag1 = "xi:include";
		tag2 = "<xmlattr>.href";
		break;
	case TYPE_JSON:
	case TYPE_INI:
	case TYPE_INFO:
		tag1 = "include";
		tag2 = "href";
		break;

	case TYPE_UNKNOWN:
	default:
		tag1 = "Error";
		tag2 = "Error";
		break;
	}
}

void rocs::core::Configuration::readFileAndCheckIncludes(string filename,
		ptree* tree, bool include_allowed) throw (core::IOException)
{
	rocsDebug3("read_file_and_check_includes('%s') - tree version",
			filename.c_str());
	/*
	 * parsing
	 */
	int guessedFileType = readFfile(filename, tree);
	/*
	 * taking care of the includes
	 */
	if (include_allowed)
	{
		// get the relative path
		string relative_path = "./";
		size_t last_slash_pos = filename.find_last_of('/');
		if (last_slash_pos != string::npos)
			relative_path = filename.substr(0, last_slash_pos + 1);
		rocsDebug3("relative_path:'%s'", relative_path.c_str());
		// obtain the tags to search in the tree
		string tagToFind1, tagToFind2;
		determineTagsToFind(guessedFileType, tagToFind1, tagToFind2);
		rocsDebug3("check_includes(), tags:'%s', '%s'", tagToFind1.c_str(), tagToFind2.c_str());
		checkIncludes(relative_path, tree, tagToFind1, tagToFind2);
	}
	/*
	 * remove the <xmlattr>
	 */
	if (guessedFileType == TYPE_XML)
	{
		rocsDebug3("remove_xmlattr()");
		removeXmlattr(tree);
	}
}

//void rocs::core::Configuration::readFileAndCheckIncludes(
//		string filename, bool include_allowed /*= true*/) {
//	rocsDebug3("readFileAndCheckIncludes('%s')", filename.c_str());
//	readFileAndCheckIncludes(filename, &pt, include_allowed);
//}

void rocs::core::Configuration::printPtreeRec(const ptree* tree, int depth)
{
	++depth;
	for (ptree::const_iterator son_iter = tree->begin(); son_iter
			!= tree->end(); ++son_iter)
	{
		string son_node_name = son_iter->first;
		const ptree son_tree = son_iter->second;
		string son_node_value = son_tree.get_value("");
		//cout << "second:" << typeid(i->second).name() << endl;
		for (int var = 0; var < depth; ++var)
			cout << ". ";
		cout << "Node: '" << son_node_name;
		cout << "' = '" << son_node_value << "'";
		int nb_sons = son_tree.size();
		if (nb_sons > 0)
			cout << "(" << nb_sons << " sons)";
		cout << endl;
		printPtreeRec(&son_tree, depth);
	}
}

void rocs::core::Configuration::printTree(const ptree* tree)
{
	cout << "<root>";
	cout << " (" << tree->size() << " sons)" << endl;
	printPtreeRec(tree, 0);
}

std::string rocs::core::Configuration::getValueAsString(const ptree* tree,
		const std::string path, bool& was_found)
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
	for (ptree::const_reverse_iterator son_iter = tree->rbegin(); son_iter
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
				return getValueAsString(&son_tree, son_key_to_search, was_found);
		}
	} // end loop sons

	// we didin't find the key in the sons
	rocsDebug1("Couldn't find the key '%s' in the sons !",
			key_to_search.c_str());
	return "";
}

void rocs::core::Configuration::getChildren(const ptree* tree,
		const std::string path, int& nb_found, std::vector<ptree>* answer)
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
		for (ptree::const_iterator son_iter = tree->begin(); son_iter
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
	for (ptree::const_reverse_iterator son_iter = tree->rbegin(); son_iter
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

/* template specifications */
// string
template<>
string rocs::core::Configuration::getValue<string>(const ptree* tree,
		const string path, const string default_value, bool& was_found)
{
	rocsDebug3("getValue<string>('%s')", path.c_str());
	string return_value = getValueAsString(tree, path, was_found);
	return (was_found ? return_value : default_value);
}
// int
template<>
int rocs::core::Configuration::getValue<int>(const ptree* tree,
		const string path, const int default_value, bool& was_found)
{
	rocsDebug3("getValue<int>('%s')", path.c_str());
	string return_value = getValueAsString(tree, path, was_found);
	return (was_found ? atoi(return_value.c_str()) : default_value);
}
// double
template<>
double rocs::core::Configuration::getValue<double>(const ptree* tree,
		const string path, const double default_value, bool& was_found)
{
	rocsDebug3("getValue<double>('%s')", path.c_str());
	string return_value = getValueAsString(tree, path, was_found);
	return (was_found ? atof(return_value.c_str()) : default_value);
}
// const char*
template<>
const char* rocs::core::Configuration::getValue<const char*>(const ptree* tree,
		const string path, const char* default_value, bool& was_found)
{
	rocsDebug3("getValue<const char*>('%s')", path.c_str());
	string return_value = getValueAsString(tree, path, was_found);
	return (was_found ? return_value.c_str() : default_value);
}
