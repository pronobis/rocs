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
static inline void splitString(std::string sentence, std::string separators,
		std::vector<std::string>& sentenceWords)
{
	boost::split(sentenceWords, sentence, boost::is_any_of(separators));
}

/*!
 * Determine if a file exists
 * \param strFilename
 *          the file to search
 * \return true if the file exists
 */
static inline bool fileExists(std::string strFilename)
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

} // namespace core
} // namespace rocs


#endif /* _ROCS_CORE_UTILS_H_ */
