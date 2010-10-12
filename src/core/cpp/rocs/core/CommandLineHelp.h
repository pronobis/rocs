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
 * \file CommandLineHelp.h
 *
 * \date Sep 7, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 *
 *  More info on http://wiki.github.com/pronobis/rocs/config-files
 */

#ifndef COMMANDLINEHELP_H_
#define COMMANDLINEHELP_H_

// Stl
#include <vector>
#include <string>

namespace rocs {
namespace core {

class CommandLineHelp {
public:
	class OptionDescription {
	public:
		std::vector<std::string> names;
		std::string description;
		bool with_complement;

		std::string firstName() {
			return names.front();
		}

		bool containsName(std::string name);

	}; // end class OptionDescription

	CommandLineHelp();
	virtual ~CommandLineHelp();

	// storage structures
	std::vector<OptionDescription> options;

	template<class T>
	void addOption(std::vector<std::string>* names, std::string description, T default_value)
	{
		OptionDescription option;
				for (std::vector<std::string>::iterator it = names->begin(); it < names->end(); ++it)
					option.names.push_back(*it);
				option.description = description;
				option.with_complement = true;

				// adding the object
				options.push_back(option);
	}

	void addOptionWithoutValue(std::vector<std::string>* names, std::string description) {
		addOption<int>(names, description, -1);
		options.back().with_complement = false;
	}

	inline int containsName(std::string name)
	{
		int index = 0;
		for (std::vector<OptionDescription>::iterator it = options.begin(); it
				< options.end(); ++it) {
			if (it->containsName(name))
				return index;
			++index;
		}
		return -1;
	}

	//	template<class T>
	//	inline void addOption(string name, string description) {
	//		vector<string> names;
	//		names.push_back(name);
	//		addOption<T> (&names, description);
	//	}
	//
	//	template<class T>
	//	inline void addOption(string name, string name2, string description) {
	//		vector<string> names;
	//		names.push_back(name);
	//		names.push_back(name2);
	//		addOption<T> (&names, description);
	//	}
};

}
}

#endif /* COMMANDLINEHELP_H_ */
