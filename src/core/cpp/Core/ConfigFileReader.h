/*
 * ConfigFileReader.h
 *
 *  Created on: Aug 2, 2010
 *      Author: arnaud
 *
 *  More info on http://wiki.github.com/pronobis/rocs/config-files
 */

#ifndef CONFIGFILEREADER_H_
#define CONFIGFILEREADER_H_

// stl and BOOST includes
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/info_parser.hpp>

#include <boost/foreach.hpp>
// rocs includes
#include "Core.h"
#include "Types.h"

/*!
 * A class for I/O with config files
 *
 */
namespace rocs {
namespace core {

using boost::property_tree::ptree;

class ConfigFileReader {
public:
	static void readFileAndCheckIncludes(string filename, ptree* tree,
			bool include_allowed);

	/*!
	 * open a file, parse it
	 * \param filename
	 *          the name of the file to parse
	 * \param include_allowed
	 * 	        if <code>true</code>, allow the xml include tags :
	 *          will parse the corresponding files and replace them
	 */
	//	void readFileAndCheckIncludes(string filename, bool include_allowed =
	//			true);

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
	static inline void printTree(ptree* tree) {
		cout << "<root>";
		cout << " (" << tree->size() << " sons)" << endl;
		printPtreeRec(tree, 0);
	}

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
	static string getValueAsString(ptree* tree, string path, bool& was_found) {
		debugPrintf_lvl3("getValueAsString('%s')", path.c_str());
		was_found = false;
		bool search_for_son_value = false;
		string key_to_search, son_key_to_search;

		/* determine the key to search */
		size_t dot_position = path.find_first_of('.');
		if (dot_position == string::npos) {
			// there is no dot in the path -> last step, find the good son
			search_for_son_value = true;
			key_to_search = path;
		} else {
			search_for_son_value = false;
			key_to_search = path.substr(0, dot_position);
			son_key_to_search = path.substr(dot_position + 1);
		}
		debugPrintf_lvl2("Searching the key '%s' in the sons...", key_to_search.c_str());

		/* serarch it */
		// backwards search
		for (ptree::reverse_iterator son_iter = tree->rbegin(); son_iter
				!= tree->rend(); ++son_iter) {
			string son_node_name = son_iter->first;
			ptree son_tree = son_iter->second;
			string son_node_value = son_tree.get_value("");
			debugPrintf_lvl3("Node:'%s' = '%s'", son_node_name.c_str(), son_node_value.c_str());

			if (son_node_name == key_to_search) {
				// we found the key
				if (search_for_son_value) {
					was_found = true;
					return son_node_value;
				} else
					return getValueAsString(&son_tree, son_key_to_search,
							was_found);
			}
		} // end loop sons

		// we didin't find the key in the sons
		debugPrintf_lvl1("Couldn't find the key '%s' in the sons !", key_to_search.c_str());
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
	static _T getValue(ptree* tree, string path, _T default_value,
			bool& was_found) {
		debugPrintf_lvl3("getValue<_T>(%s)", path.c_str());
		Error(-1, "Templated function non implemented");
	}

	static void getChildren(ptree* tree, string path, int& nb_found, vector<
			ptree>* answer) {
		nb_found = 0;
		debugPrintf_lvl3("get_children('%s')", path.c_str());

		if (path == "") { // we need to return these nodes
			debugPrintf_lvl1("We found the key ! Returning the %i sons.", (int) tree->size());
			answer->clear();
			nb_found = 0;
			for (ptree::iterator son_iter = tree->begin(); son_iter
					!= tree->end(); ++son_iter) {
				ptree son_tree = son_iter->second;
				answer->push_back(son_tree);
				++nb_found;
			} // end loop sons
			return;
		} // end path empty

		/* determine the key to search */
		string key_to_search, son_key_to_search;
		size_t dot_position = path.find_first_of('.');
		if (dot_position == string::npos) {
			key_to_search = path;
			son_key_to_search = "";
		} else {
			key_to_search = path.substr(0, dot_position);
			son_key_to_search = path.substr(dot_position + 1);
		}
		debugPrintf_lvl2("Searching the key '%s' in the sons...", key_to_search.c_str());

		/* serarch it */
		// backwards search
		for (ptree::reverse_iterator son_iter = tree->rbegin(); son_iter
				!= tree->rend(); ++son_iter) {
			string son_node_name = son_iter->first;
			ptree son_tree = son_iter->second;
			string son_node_value = son_tree.get_value("");
			debugPrintf_lvl3("Node:'%s' = '%s'", son_node_name.c_str(), son_node_value.c_str());

			if (son_node_name == key_to_search) {
				getChildren(&son_tree, son_key_to_search, nb_found, answer);
				return;
			}
		} // end loop sons

		// we didin't find the key in the sons
		debugPrintf_lvl1("Couldn't find the key '%s' in the sons !", key_to_search.c_str());
	}

	/*!
	 * Returns a list of values.
	 * For instance, getValueList(A, "", ""key)
	 * will return [3, 1]
	 *
	 A
	 |
	 |--B
	 | |
	 | |--key=3
	 |
	 |--foo
	 | |
	 | |--key2=3
	 |
	 |--
	 | |
	 | |--key=1
	 | |
	 | |--key2=5

	 * \param tree
	 *          the tree to search in
	 * \param path
	 *          the path to follow from the root of the tree
	 * \param ans
	 *          the vector where to store the answers
	 */
	template<class _T>
	static void getValueList(ptree* tree, string path, string key,
			int& nb_found, vector<_T>* ans) {
		debugPrintf_lvl3("get_children(path:'%s', key:'%s')", path.c_str(), key.c_str());

		ans->clear();
		nb_found = 0;

		// get the wanted sons
		int nb_sons;
		vector<ptree> sons;
		getChildren(tree, path, nb_sons, &sons);
		debugPrintf_lvl3("children obtained, nb:%i", nb_sons);
		if (nb_sons == 0)
			return;

		// get the values
		for (vector<ptree>::iterator it = sons.begin(); it < sons.end(); ++it) {
			bool was_found = false;
			_T value = getValue<_T> (&(*it), key, Type<_T>::defaultValue(), was_found);
			if (was_found) {
				//				ostringstream msg;
				//				msg << "value found:" << value;
				//				debugPrint_lvl3(msg.str().c_str());
				++nb_found;
				ans->push_back(value);
			}
		}
	}

	/*!
	 * get a parameter from a config file
	 *
	 * \param     filename the file where we can parse the variable (XML, JSON, INI or INFO file)
	 * \param     variable_name
	 *              the name of the variable
	 * \param     default_value
	 *              the return value  in case of trouble
	 * \return    the parsed value, or the default value
	 *            if the file is not found, cannot be parsed or
	 *            there is no variable with the given name
	 */
	//	template<class _T>
	//	static _T autoload(string filename, string variable_name, _T default_value) {
	//		ConfigFileReader file_reader;
	//		file_reader.readFileAndCheckIncludes(filename);
	//		return file_reader.get_variable<_T> (variable_name, default_value);
	//	}

private:
	/*!
	 * Parses a file into the tree
	 * \param filename
	 *          the file to parse
	 * \param tree
	 *          the tree to populate with the parsed file
	 * \param include_allowed
	 *          if <code>true</code>, allow the xml include tags :
	 *          will parse the corresponding files and replace them
	 */
	static void readFfile(string filename, ptree* tree);

	/*!
	 * parse a file to be able to extract the variables inside
	 *
	 * \param     filename
	 *              the file where we can parse the variable (XML, JSON, INI or INFO file)
	 */
	static void checkIncludes(string relative_path, ptree* tree);

	/*!
	 * delete the \<xmlattr\> nodes made by RapidXML
	 *
	 * \param     tree
	 *              the tree to clean from its \<xmlattr\> nodes
	 */
	static void removeXmlattr(ptree* tree);
}; // class ConfigFileReader

/* template specs */
template<> // string
string ConfigFileReader::getValue(ptree* tree, string path,
		string default_value, bool& was_found);
template<> // int
int ConfigFileReader::getValue(ptree* tree, string path, int default_value,
		bool& was_found);
template<> // double
double ConfigFileReader::getValue(ptree* tree, string path,
		double default_value, bool& was_found);

} // namespace core
} // namespace rocs


#endif /* CONFIGFILEREADER_H_ */
