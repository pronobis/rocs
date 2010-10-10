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
 * \file Vector_.h
 *
 * \date Jun 18, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef VECTOR__H_
#define VECTOR__H_

#include "rocs/math/Vector.h"

namespace rocs {
namespace math {

/*!
 * a templated vector class
 *
 * We inherit from Vector so as not to have to make again the selection of
 * allowed functions coming from Matrix (or Matrix_<...> )
 *
 */
template<class _T>
class Vector_: public Vector {
public:
	//Vector_();
	Vector_(int rows) :
		Vector(rows, core::Type<_T>::type_()) {
	}
	virtual ~Vector_() {
	}

	inline _T get(const int row, const int col) const {
		return (static_cast<Vector*> (this))->get<_T> (row, col);
	}

	inline void set(int row, int col, _T value) {
		(static_cast<Vector*> (this))->set<_T> (row, col, value);
	}

	inline void fill(_T value) {
		(static_cast<Vector*> (this))->fill<_T> (value);
	}
};

} // end namespace math
} // end namespace rocs

#endif /* VECTOR__H_ */
