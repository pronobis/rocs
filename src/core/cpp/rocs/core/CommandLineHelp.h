// ===============================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (c) 2010-2012, the ROCS authors. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met: 
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution. 
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ===============================================================================


#ifndef _ROCS_CORE_COMMANDLINEHELP_H_
#define _ROCS_CORE_COMMANDLINEHELP_H_

// Stl
#include <vector>
#include <string>


namespace rocs {
namespace core {
  
/*!
 * \author Arnaud Ramey, Andrzej Pronobis
 */
class CommandLineHelp
{
public:
  
  class OptionDescription
  {
  public:
    std::vector<std::string> names;
    std::string description;
    bool with_complement;
    
    std::string firstName()
    {
      return names.front();
    }
    
    bool containsName(std::string name);
  }; // OptionDescription
  
 
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

  
  void addOptionWithoutValue(std::vector<std::string>* names, std::string description)
  {
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

#endif /* _ROCS_CORE_COMMANDLINEHELP_H_ */
