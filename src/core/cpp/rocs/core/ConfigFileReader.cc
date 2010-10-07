/*
 * ConfigFileReader.cc
 *
 *  Created on: Aug 2, 2010
 *      Author: arnaud
 */

#include "ConfigFileReader.h"

// cf http://www.boost.org/doc/libs/1_41_0/doc/html/boost_propertytree/parsers.html
#define TYPE_UNKNOWN  -1
#define TYPE_XML      1
#define TYPE_JSON     2
#define TYPE_INI      3
#define TYPE_INFO     4

// reference to the boost ptree
using boost::property_tree::ptree;
using namespace std;

/*!
 * guess the type of file according to the extension
 * \param     filename the config filename
 * \return    the guess type of file
 */
inline int guessType(std::string filename) {
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

void rocs::core::ConfigFileReader::checkIncludes(string relative_path,
		ptree* tree) {
	//debug3("checkIncludes()");
	const char* tag_to_find1 = "xi:include";
	const char* tag_to_find2 = "<xmlattr>.href";

	// if we allow the include tags, check if there are some
	for (ptree::iterator son_iter = tree->begin(); son_iter != tree->end(); ++son_iter) {
		string son_node_name = son_iter->first;
		//debug3("Son-node_name:'%s'", son_node_name.c_str());

		boost::optional<ptree &> found_son =
				son_iter->second.get_child_optional(tag_to_find2);
		bool found_tag1 = (son_node_name == tag_to_find1);
		bool found_tag2 = (found_son != NULL);
		bool is_include = found_tag1 && found_tag2;
		//debugPrintf_lvl2("found_tag1:%d, found_tag2:%d, is_include:%d", found_tag1, found_tag2, is_include);

		if (is_include) {
			// TODO
			debug3("'%s' found !", tag_to_find2);
			/*
			 * get the filename
			 */
			ptree real_found_son = (*found_son);
			string file_to_include = real_found_son.get_value("");
			file_to_include = relative_path + file_to_include;
			debug3("Including the file:'%s'", file_to_include.c_str());
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
		} else
			// node is not an include - check if it contains some includes
			checkIncludes(relative_path, &(son_iter->second));
	} // end loop on sons
}

void rocs::core::ConfigFileReader::readFfile(string filename, ptree* tree)
{
	debug3("read_file('%s')", filename.c_str());

	// store the filename
	//	this->filename = filename;

	// guess the type of the file
	int guessed_filetype = guessType(filename);

	// read the file
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
		debug1("Impossible to guess the config file type");
		break;
	}
}

void rocs::core::ConfigFileReader::removeXmlattr(ptree* tree) {
	//debug3("removeXmlattr()");
	//printTree(tree);

	for (ptree::iterator son_iter = tree->begin(); son_iter != tree->end(); ++son_iter) {
		string son_node_name = son_iter->first;
		ptree* son_tree = &son_iter->second;
		//string node_value = son_tree.getValue("");
		//debug3("node_name:'%s'", son_node_name.c_str());

		if (son_node_name == "<xmlattr>") {
			debug3("<xmlattr> found !");
			/* insert the sons */
			for (ptree::iterator sonson = son_tree->begin(); sonson
					!= son_tree->end(); ++sonson) {
				son_iter = tree->insert(son_iter, *sonson);
				son_iter++;
				//debug3("node_name:'%s'", node_name.c_str());
			} // end loop sons

			/* remove the node */
			son_iter = tree->erase(son_iter);
			son_iter--;
		} else
			removeXmlattr(son_tree);
	}
}

void rocs::core::ConfigFileReader::readFileAndCheckIncludes(
		string filename, ptree* tree, bool include_allowed) {
	debug3("read_file_and_check_includes('%s') - tree version",
			filename.c_str());
	/*
	 * parsing
	 */
	readFfile(filename, tree);
	/*
	 * taking care of the includes
	 */
	if (include_allowed) {
		// get the relative path
		string relative_path = "./";
		size_t last_slash_pos = filename.find_last_of('/');
		if (last_slash_pos != string::npos)
			relative_path = filename.substr(0, last_slash_pos + 1);
		debug3("relative_path:'%s'", relative_path.c_str());
		debug3("check_includes()");
		checkIncludes(relative_path, tree);
	}
	/*
	 * remove the <xmlattr>
	 */
	debug3("remove_xmlattr()");
	removeXmlattr(tree);
}

//void rocs::core::ConfigFileReader::readFileAndCheckIncludes(
//		string filename, bool include_allowed /*= true*/) {
//	debug3("readFileAndCheckIncludes('%s')", filename.c_str());
//	readFileAndCheckIncludes(filename, &pt, include_allowed);
//}

void rocs::core::ConfigFileReader::printPtreeRec(ptree* tree, int depth) {
	++depth;
	for (ptree::iterator son_iter = tree->begin(); son_iter != tree->end(); ++son_iter) {
		string son_node_name = son_iter->first;
		ptree son_tree = son_iter->second;
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

/* template specifications */
// string
template<>
string rocs::core::ConfigFileReader::getValue<string>(ptree* tree,
		string path, string default_value, bool& was_found) {
	debug3("getValue<string>(%s)", path.c_str());
	string return_value = getValueAsString(tree, path, was_found);
	return (was_found ? return_value : default_value);
}
// int
template<>
int rocs::core::ConfigFileReader::getValue<int>(ptree* tree, string path,
		int default_value, bool& was_found) {
	debug3("getValue<int>(%s)", path.c_str());
	string return_value = getValueAsString(tree, path, was_found);
	return (was_found ? atoi(return_value.c_str()) : default_value);
}
// double
template<>
double rocs::core::ConfigFileReader::getValue<double>(ptree* tree,
		string path, double default_value, bool& was_found) {
	debug3("getValue<double>(%s)", path.c_str());
	string return_value = getValueAsString(tree, path, was_found);
	return (was_found ? atof(return_value.c_str()) : default_value);
}


void rocs::core::ConfigFileReader::printTree(ptree* tree)
{
	cout << "<root>";
	cout << " (" << tree->size() << " sons)" << endl;
	printPtreeRec(tree, 0);
}
