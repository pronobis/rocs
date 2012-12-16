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

/*!
 * \author Andrzej Pronobis, Arnaud Ramey 
 * \file Config.h
 */

#ifndef _ROCS_CORE_CONFIG_H_
#define _ROCS_CORE_CONFIG_H_

// ROCS includes
#include "rocs/core/error.h"
#include "rocs/core/CommandLineHelp.h"
// BOOST includes
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/utility/value_init.hpp>
// STL includes
#include <vector>
#include <iostream>

// Definitions
#define TYPE_UNKNOWN   -1
#define TYPE_XML        1
#define TYPE_JSON       2
#define TYPE_INI        3
#define TYPE_INFO       4


namespace rocs {
namespace core {

using boost::property_tree::ptree;

/*!
 * Class providing access to configuration options for the ROCS components.
 *
 * It supports XML, INI, INFO, JSON formats.
 *
 * The include tags are allowed :
 * if, in the file "input.xml",
 * there is the instruction<br>
 * <code><xi:include href="toInsert.xml"/></code><br>
 * then during parsing this instruction will be replaced
 * with the content of the file "toInsert.xml" at the same point.
 *
 * For JSON, the include tag is :<br>
 * <code>"include": {"href" : "toInsert.json"}</code>
 *
 * For INI, the include tag is :<br>
 * <code>[include]
 * href = toInsert.ini</code>
 *
 * For INFO, the include tag is :<br>
 * <code>include { href "toInsert.info" }</code>
 */
class Config
{
public:

  /*! Default constructor. */
  Config();

  /*! Constructor, processes command line arguments. */
  Config(int argc, char const **argv)
  {
    addCommandLineArgs(argc, argv);
  }

  /*! Destructor. */
  virtual ~Config();

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
  void addConfigFile(std::string fileName) throw (core::IOException);

  /*!
   * add a bunch of config file
   * \param files the list of files to add
   */
  inline void addConfigFile(std::vector<std::string>& files)
    throw (core::IOException)
  {
    for (std::vector<std::string>::iterator it = files.begin(); it
           != files.end(); ++it)
      addConfigFile(*it);
  }

  /*!
   * get the value of a given parameter
   * \param path
   *          the path of the parameter in the configuration tree
   * \param default_value
   *          the value to return if the path was impossible to follow
   *          (non existing variable)
   * \param was_found
   *          is changed to <code>true</code>
   *          if the parameter was found in the configuration tree
   * \return the value of the parameter in the config tree if found,
   *         the default value otherwise
   */
  template<class _T>
  _T getValue(const std::string path, const _T default_value, bool& was_found) const
  {
    return getValue<_T> (&_tree, path, default_value, was_found);
  }

  /*!
   * get the value of a given parameter
   * \param path
   *          the path of the parameter in the configuration tree
   * \param default_value
   *          the value to return if the path was impossible to follow
   *          (non existing variable)
   * \return the value of the parameter in the config tree if found,
   *         the default value otherwise
   */
  template<class _T>
  _T getValue(const std::string path, const _T default_value) const
  {
    bool wasFound;
    return getValue<_T> (path, default_value, wasFound);
  }

  /*!
   * return a list of sons at a given path
   * \param path
   *          the path to follow in the config tree
   * \param answer
   *          list of the childs path
   */
  void getChildren(const std::string &path,
                   std::vector<std::string>* answer) const;

  /*!
   * Returns a list of values in the config tree.
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
   * \param path
   *          the path to follow from the root of the tree
   * \param key
   *          the tag to find
   * \param ans
   *          the vector where to store the answers
   */
  template<class _T>
  void getValueList(const std::string path, const std::string key,
                    std::vector<_T>& ans) const
  {
    getValueList<_T> (&_tree, path, key, ans);
  }

  /*!
   * Prints the the whole configuration loaded to std::cout
   */
  void printConfiguration() const
  {
    printTree(&_tree);
  }

  
private:

  /** the command line help */
  CommandLineHelp commandLineHelp;

  /** The property tree. */
  ptree _tree;

  /*! Clear all the info parsed till now */
  void clear()
  {
    _tree.clear();
  }
  
  /*!
   * guess the type of file according to the extension
   * \param     filename the config filename
   * \return    the guess type of file
   */
  static int guessType(std::string filename);


  static void determineTagsToFind(int fileType, std::string& tag1, std::string& tag2);

    
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
  static void readFileAndCheckIncludes(const std::string filename,
                                       ptree* tree, const bool include_allowed)
    throw (core::IOException);

  /*!
   * Parses a file into the tree
   * \param filename
   *          the file to parse
   * \param tree
   *          the tree to populate with the parsed file
   * \return the type of file guessed
   * (TYPE_UNKNOWN, TYPE_XML, TYPE_JSON, TYPE_INI or TYPE_INFO)
   */
  static int readFile(const std::string filename, ptree* tree)
    throw (core::IOException);

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
   * \param relative_path
   *          the path of the file that generated the tree
   * \param tree
   *          the tree that might contain some include tags
   * \param tagToFind1
   *          the first part of the tag
   * \param tagToFind2
   *          the second part of the tag
   */
  static void checkIncludes(const std::string relative_path, ptree* tree,
                            const std::string tagToFind1, const std::string tagToFind2);

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
  static void printPtreeRec(const ptree* tree, int depth);

  /*!
   * display the structure of the tree inside the config file
   */
  static void printTree(const ptree* tree);

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
  static std::string getValueAsString(const ptree* tree,
                                      const std::string path, bool& was_found);

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
  static _T getValue(const ptree* tree, const std::string path,
                     const _T default_value, bool& was_found)
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
  static void getChildren(const ptree* tree, const std::string path,
                          int& nb_found, std::vector<ptree>* answer);

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
   * \param ans
   *          the vector where to store the answers
   */
  template<class _T>
  static void getValueList(const ptree* tree, const std::string path,
                           const std::string key, std::vector<_T>& ans)
  {
    rocsDebug3("getValueList(path:'%s', key:'%s')", path.c_str(),
               key.c_str());

    ans.clear();

    // get the wanted sons
    int nb_sons;
    std::vector<ptree> sons;
    getChildren(tree, path, nb_sons, &sons);
    rocsDebug3("children obtained, nb:%i", nb_sons);
    //for (std::vector<ptree>::iterator it = sons.begin(); it < sons.end(); ++it)
    //printTree(&(*it));
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
        _T value = getValue<_T> (&sonson, keyTail, _T(), was_found);
        if (was_found)
        {
          ans.push_back(value);
        } // end was_found
      } // end loop grandsons
    } // end loop sons
    rocsDebug3("nbFound=%d", (int)(ans.size()));
  }

}; // Config
  

/* template specs */
template<> // string
std::string Config::getValue(const ptree* tree, const std::string path,
                             const std::string default_value, bool& was_found);
template<> // int
int Config::getValue(const ptree* tree, const std::string path,
                     const int default_value, bool& was_found);
template<> // double
double Config::getValue(const ptree* tree, const std::string path,
                        const double default_value, bool& was_found);
template<> // const char*
const char* Config::getValue(const ptree* tree, const std::string path,
                             const char* default_value, bool& was_found);

} // namespace core
} // namespace rocs

#endif /* _ROCS_CORE_CONFIG_H_ */
