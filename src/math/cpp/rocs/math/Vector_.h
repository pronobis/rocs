/*
 * Vector_.h
 *
 *  Created on: Jun 18, 2010
 *      Author: arnaud
 */

#ifndef VECTOR__H_
#define VECTOR__H_

#include "Vector.h"

namespace rocs {
namespace math {

/**
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
		Vector(rows, Type<_T>::type_()) {
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
