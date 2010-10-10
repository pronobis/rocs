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
 * \file tests_config_files.cc
 *
 * \date Aug 17, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */
#include "ConfigFileReader.h"

//#include "tests_boost_property_tree.cc"

#define ROCSDIR "../../../"
#define DATADIR ROCSDIR "data/"

using boost::property_tree::ptree;
using rocs::core::ConfigFileReader;

inline void test_config_file_reader_without_includes() {
	// through an object
	char filename_in[100];
	sprintf(filename_in, "%s%s", DATADIR, "configfiles/include1.xml");

	ptree tree;
	printf("\nread_file_and_check_includes() without includes...\n");
	ConfigFileReader::readFileAndCheckIncludes(filename_in, &tree, false);
	ConfigFileReader::printTree(&tree);

	printf("\nread_file_and_check_includes() with includes...\n");
	ConfigFileReader::readFileAndCheckIncludes(filename_in, &tree, true);
	ConfigFileReader::printTree(&tree);
}

inline void test_config_file_reader() {
	// through an object
	char filename_in[100];
	sprintf(filename_in, "%s%s", DATADIR, "configfiles/debug_settings.xml");

	ptree tree;
	ConfigFileReader::readFileAndCheckIncludes(filename_in, &tree, true);
	ConfigFileReader::printTree(&tree);

	bool was_found;
	int value = ConfigFileReader::getValue<int>(&tree, "debug.level", -1,
			was_found);
	printf("was_found:%d, value:'%i'\n", was_found, value);
	return;

	// static autoload
	char filename_in2[100];
	sprintf(filename_in2, "%s%s", DATADIR, "configfiles/john.json");
	//	string lastName = rocs::core::ConfigFileReader::autoload<string>(
	//			filename_in2, "firstName", "default");
	//	cout << "lastName:" << lastName << endl;
}

using boost::property_tree::ptree;
inline void test_config_file_reader_sons_xml() {
	// read the file
	char filename_in[100];
	sprintf(filename_in, "%s%s", DATADIR, "configfiles/include1.xml");

	ptree tree;
	ConfigFileReader::readFileAndCheckIncludes(filename_in, &tree, true);
	ConfigFileReader::printTree(&tree);
	bool was_found;

	// string
	printf("\nget_value<string>()\n");
	string value = ConfigFileReader::getValue<string>(&tree, "book.name", "",
			was_found);
	printf("was_found:%d, Value:'%s'\n", was_found, value.c_str());
	// int
	int value_int = ConfigFileReader::getValue<int>(&tree, "book.year", -1,
			was_found);
	printf("was_found:%d, value_int:'%i'\n", was_found, value_int);

	// sons
	printf("\nget_children()\n");
	vector<ptree> sons;
	int nb_found;
	ConfigFileReader::getChildren(&tree, "listName", nb_found, &sons);
	printf("nb_found:%i\n", nb_found);
	for (vector<ptree>::iterator it = sons.begin(); it < sons.end(); ++it)
		ConfigFileReader::printTree(&(*it));

	// get value list
	printf("\nget_value_list()\n");
	vector<int> values;
	ConfigFileReader::getValueList<int>(&tree, "listName", "prop", nb_found,
			&values);
	printf("nb_found:%i\n", nb_found);
	for (vector<int>::iterator it = values.begin(); it < values.end(); ++it)
		printf(" -> value:%i\n", *it);
}

inline void test_config_file_reader_sons_json() {
	// read the file
	char filename_in[100];
	sprintf(filename_in, "%s%s", DATADIR, "configfiles/john.json");

	ptree tree;
	ConfigFileReader::readFileAndCheckIncludes(filename_in, &tree, true);
	ConfigFileReader::printTree(&tree);

	// get value list
	printf("\nget_value_list()\n");
	vector<double> values;
	int nb_found;
	ConfigFileReader::getValueList<double>(&tree, "foo", "bar", nb_found,
			&values);
	printf("nb_found:%i\n", nb_found);
	for (vector<double>::iterator it = values.begin(); it < values.end(); ++it)
		printf(" -> value:%g\n", *it);
}

int main(int argc, char **argv) {
	//	test_property_tree();
	//	test_config_file_reader_without_includes();
	//	test_config_file_reader();
	test_config_file_reader_sons_xml();
	//	test_config_file_reader_sons_json();

	std::cout << "end of main()" << std::endl;
}
