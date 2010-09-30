/*
 * CommandLineHelp.h
 *
 *  Created on: Sep 7, 2010
 *      Author: arnaud
 *
 *  More info on http://wiki.github.com/pronobis/rocs/config-files
 */

#ifndef COMMANDLINEHELP_H_
#define COMMANDLINEHELP_H_

//#include "InputMixer.h"
#include "Core.h"

class CommandLineHelp {
public:
	class OptionDescription {
	public:
		vector<string> names;
		string description;
		bool with_complement;

		string firstName() {
			return names.front();
		}

		bool containsName(string name) {
			for (vector<string>::iterator it = names.begin(); it < names.end(); ++it) {
				//debugPrintf_lvl3("Comparing '%s' and '%s'", name.c_str(), it->c_str());
				if (*it == name) {
					debugPrintf_lvl3("We found an option corresponding to '%s' ( first name:'%s')", name.c_str(), firstName().c_str());
					return true;
				}
			} // end for names
			return false;
		} // end containsName()

	}; // end class OptionDescription

	CommandLineHelp();
	virtual ~CommandLineHelp();

	// storage structures
	vector<OptionDescription> options;

	template<class T>
	void addOption(vector<string>* names, string description, T default_value) {
		OptionDescription option;
				for (vector<string>::iterator it = names->begin(); it < names->end(); ++it)
					option.names.push_back(*it);
				option.description = description;
				option.with_complement = true;

				// adding the object
				options.push_back(option);
	}

	void addOptionWithoutValue(vector<string>* names, string description) {
		addOption<int>(names, description, -1);
		options.back().with_complement = false;
	}

	inline int containsName(string name) {
		int index = 0;
		for (vector<OptionDescription>::iterator it = options.begin(); it
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

#endif /* COMMANDLINEHELP_H_ */
