/*
 * Vector.h
 *
 *  Created on: Jun 18, 2010
 *      Author: arnaud
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
