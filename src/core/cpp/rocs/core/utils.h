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

// STL & Boost includes
#include <vector>
#include <boost/algorithm/string.hpp>


namespace rocs {
namespace core {

/*! Splits string into substrings. */
static inline void splitString(std::string sentence, std::string separators,
		std::vector<std::string>& sentenceWords)
{
	boost::split(sentenceWords, sentence, boost::is_any_of(separators));
}

} // namespace core
} // namespace rocs


#endif /* _ROCS_CORE_UTILS_H_ */
