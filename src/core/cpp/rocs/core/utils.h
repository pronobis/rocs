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
 * General utilities.
 * \author Arnaud Ramey, Andrzej Pronobis
 * \file utils.h
 */

#ifndef _ROCS_CORE_UTILS_H_
#define _ROCS_CORE_UTILS_H_

// Boost includes
#include <boost/algorithm/string.hpp>
// STL includes
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <sys/stat.h>

namespace rocs
{
namespace core
{

/*!
 * Splits string into substrings.
 * \param sentence
 *          the sentence to split
 * \param separators
 *          the different separators, for instance " \t\n"
 * \param sentenceWords
 *          the answer to fill
 */
static inline void splitString(const std::string sentence,
		const std::string separators, std::vector<std::string>& sentenceWords)
{
	boost::split(sentenceWords, sentence, boost::is_any_of(separators));
}

/*!
 * Determine if a file exists
 * \param strFilename
 *          the file to search
 * \return true if the file exists
 */
static inline bool fileExists(const std::string strFilename)
{
	struct stat stFileInfo;
	bool blnReturn;
	int intStat;

	// Attempt to get the file attributes
	intStat = stat(strFilename.c_str(), &stFileInfo);
	if (intStat == 0)
	{
		// We were able to get the file attributes
		// so the file obviously exists.
		blnReturn = true;
	}
	else
	{
		// We were not able to get the file attributes.
		// This may mean that we don't have permission to
		// access the folder which contains this file. If you
		// need to do that level of checking, lookup the
		// return values of stat which will give you
		// more details on why stat failed.
		blnReturn = false;
	}

	return (blnReturn);
}

static inline void loadFilenameList(const std::string inputFileName, std::vector<
		std::string>& ans)
{
	using namespace std;
	bool inputIsAList = (inputFileName[0] == '@');

	/* Read list of images */
	if (inputIsAList)
	{
		string inputFileNameWithoutArobase = inputFileName.substr(inputFileName.size() - 1);
		rocsDebug1("\n\n* Reading list file: %s", inputFileName.c_str());

		/* Open file */
		ifstream listFileStream(inputFileNameWithoutArobase.c_str(), ios::in);
		if (!listFileStream.is_open())
		{ /* ok, proceed with output */
			rocsError("ERROR: Unable to open the list file '%s'!",
					inputFileNameWithoutArobase.c_str());
		}

		/* Read the lines */
		while (!listFileStream.eof())
		{
			string line;
			getline(listFileStream, line);

			//vector<string> line_split = line.split(' ');
			vector<string> line_words;
			istringstream iss(line);
			copy(istream_iterator<string> (iss), istream_iterator<string> (),
					back_inserter<vector<string> > (line_words));

			ans.push_back(line_words[0]);
			//				if (line_words.size() > 1)
			//					classLabelList.push_back(line_words[1]);
			//				else
			//					classLabelList.push_back("");
		}

		/* Close file */
		listFileStream.close();
	}
	else
	{ // input is not a list
		ans .push_back(inputFileName);
		//			classLabelList.push_back("");
	}
}

/*!
 * read a file and return the result as a string
 * @param filename
 * @return the content of the file
 */
static inline std::string readFile(const char* filename)
{
	std::ostringstream ans;
	std::string line;
	std::ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			getline(myfile, line);
			ans << line << std::endl;
		}
		myfile.close();
	}

	else
		rocsError("ERROR: Unable to open the file '%s'!", filename);

	return ans.str();
}

} // namespace core
} // namespace rocs


#endif /* _ROCS_CORE_UTILS_H_ */
