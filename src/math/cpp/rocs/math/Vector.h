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
 * \file Vector.h
 *
 * \date Jun 18, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "rocs/math/Matrix.h"

namespace rocs {
namespace math {

/*!
 * It is an extension of Matrix.
 * Most of its functions will redirect to the Matrix corresponding function,
 * with, for those who need it, a number of columns equal to 1
 */
class Vector: private Matrix {
public:
	//Vector();
	/*!
	 * the constructor
	 *
	 * \param rows number of rows
	 * \param type the data_type of data : MAT_8U -> MAT_64F
	 * \return
	 */
	Vector(int rows, int type) :
		Matrix(rows, 1, type) {
	}
	virtual ~Vector();

	/*! getters and setters */
	template<typename _T> inline _T get(const int row) const {
		return get<_T> (row, 1);
	}
	template<typename _T> inline void set(int row, _T value) {
		(static_cast<Matrix*> (this))->set<_T> (row, 1, value);
	}
	template<typename _T> inline void fill(_T value) {
		return (static_cast<Matrix*> (this))->fill<_T> (value);
	}

	inline void copyTo(Vector m) {
		(static_cast<Matrix*> (this))->copyTo(m);
	}

	// size
	inline int nbRows() {
		return (static_cast<Matrix*> (this))->nbRows();
	}

	inline int size() {
		return nbRows();
	}

	inline std::string toString() {
		return (static_cast<Matrix*> (this))->toString();
	}
};

} // end namespace math
} // end namespace rocs

#endif /* VECTOR_H_ */
