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
 * \file tests_boost_property_tree.cc
 *
 * \date Aug 2, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////// boost config tree
////////////////////////////////////////////////////////////////////////////////
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <set>

struct debug_settings {
	std::string m_file; // log filename
	int m_level; // debug level
	std::set<string> m_modules; // modules where logging is enabled
	void load(const std::string &filename);
	void save(const std::string &filename);
};

//// Loads debug_settings structure from the specified XML file
void debug_settings::load(const std::string &filename) {
	// Create an empty property tree object
	using boost::property_tree::ptree;
	ptree pt;

	// Load the XML file into the property tree. If reading fails
	// (cannot open file, parse error), an exception is thrown.
	read_xml(filename, pt);

	// Get the filename and store it in the m_file variable.
	// Note that we construct the path to the value by separating
	// the individual keys with dots. If dots appear in the keys,
	// a path type with a different separator can be used.
	// If the debug.filename key is not found, an exception is thrown.
	m_file = pt.get<std::string> ("debug.filename");

	// Get the debug level and store it in the m_level variable.
	// This is another version of the get method: if the value is
	// not found, the default value (specified by the second
	// parameter) is returned instead. The type of the value
	// extracted is determined by the type of the second parameter,
	// so we can simply write get(...) instead of get<int>(...).
	m_level = pt.get("debug.level", 0);

	// Iterate over the debug.modules section and store all found
	// modules in the m_modules set. The get_child() function
	// returns a reference to the child at the specified path; if
	// there is no such child, it throws. Property tree iterators
	// are models of BidirectionalIterator.
	BOOST_FOREACH(ptree::value_type &v, pt.get_child("debug.modules"))
m_modules	.insert(v.second.data());

}

void debug_settings::save(const std::string &filename) {
	// Create empty property tree object
	using boost::property_tree::ptree;
	ptree pt;

	// Put log filename in property tree
	pt.put("debug.filename", m_file);

	// Put debug level in property tree
	pt.put("debug.level", m_level);

	// Iterate over modules in set and put them in property
	// tree. Note that put function places new key at the
	// end of list of keys. This is fine in most of the
	// situations. If you want to place item at some other
	// place (i.e. at front or somewhere in the middle),
	// this can be achieved using combination of insert
	// and put_value functions
	BOOST_FOREACH(const std::string &name, m_modules)
{	cout << "name:" << name << endl;
	pt .add("debug.modules.module", name);
}

// Write property tree to XML file
write_xml(filename, pt);

}

struct person {
	std::string firstName;
	std::string lastName;
	int age; // debug level
	void load(const std::string &filename);
	void save(const std::string &filename);
};

//// Loads debug_settings structure from the specified XML file
void person::load(const std::string &filename) {
	// Create an empty property tree object
	using boost::property_tree::ptree;
	ptree pt;
	read_json(filename, pt);
	firstName = pt.get<std::string> ("firstName");
	lastName = pt.get<std::string> ("lastName");
	age = pt.get("age", 0);
}

int test_property_tree() {
	try {
		debug_settings ds;
		char filename_in[100];
		sprintf(filename_in, "%s%s", DATADIR, "configfiles/debug_settings.xml");
		char filename_out[100];
		sprintf(filename_out, "%s%s", DATADIR,
				"configfiles/debug_settings_out.xml");
		ds.load(filename_in);
		ds.save(filename_out);

		person p;
		char filename_in2[100];
		sprintf(filename_in2, "%s%s", DATADIR, "configfiles/john.json");
		p.load(filename_in2);
		std::cout << "Success\n";
	} catch (std::exception &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
