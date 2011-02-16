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
 * \file ElemMath.h
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef _ROCS_MATH_ELEMMATH_H_
#define _ROCS_MATH_ELEMMATH_H_

namespace rocs {
namespace math {

/*! Returns minimum of two values. */
template<class T>
inline T aMin(T val1, T val2) {
	if (val1 < val2)
		return val1;
	return val2;
}

/*! Returns maximum of two values. */
template<class T>
inline T aMax(T val1, T val2) {
	if (val1 < val2)
		return val2;
	return val1;
}

/*!
 * returns true if the argument is a space or a tab or a newline
 * \param c
 *          the char to analyze
 * \return <code>true</code> if the argument is a space or a tab or a newline
 */
inline bool aIsWhiteChar(char c) {
	return (c == ' ') || (c == '\n') || (c == '\t');
}

/*!
 * returns true if the argument is a newline
 * \param c
 *          the char to analyze
 * \return <code>true</code> if the argument is a newline
 */
inline bool aIsNewLine(char c) {
	return (c == '\n');
}

/*!
 * round a double to the closest integer
 * \param x
 *          the double to round
 * \return
 *          the closest integer
 */
inline int aRound(double x) {
	return int(x > 0.0 ? x + 0.5 : x - 0.5);
}

} // end namespace math
} // end namespace rocs

#endif /* _ROCS_MATH_ELEMMATH_H_ */
