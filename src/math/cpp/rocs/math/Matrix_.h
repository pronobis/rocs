#ifndef MATRIX__H_
#define MATRIX__H_

#include "rocs/math/Matrix.h"
#include "rocs/core/types.h"

/*!
 *
 * a template declaration, inherit from Mat_
 * cf http://opencv.willowgarage.com/documentation/cpp/basic_structures.html?highlight=mat#id4
 *
 */
namespace rocs {
namespace math {

template<class _T>
class Matrix_: public Matrix {
public:
	/*!
		 * equivalent to Mat(_rows, _cols, Type<_T>::type_())
		 * \param rows
		 * \param cols
		 */
	Matrix_(int rows, int cols) :
		Matrix(rows, cols, core::Type<_T>::type_()) {
	}
	/*! empty constructor */
	Matrix_() :
		Matrix(0, 0, core::Type<_T>::type_()) {
	}
	/*! dtor */
	virtual ~Matrix_() {
	}

	/*!
	 * get a value from the matrix
	 * \param row
	 * \param col
	 * \return
	 */
	inline _T get(const int row, const int col) const {
		return ((Matrix*) this)->get<_T> (row, col);
	}

	/*! set */
	inline void set(int row, int col, _T value) {
		((Matrix*) this)->set<_T> (row, col, value);
	}

	/*! fill */
	inline void fill(_T value) {
		//(static_cast<Matrix*> ((Matrix_*) this))->fill<_T> (value);
		((Matrix*) this)->fill<_T> (value);
	}

	/*! fill */
	inline void fillWithZeros() {
		//(static_cast<Matrix*> ((Matrix_*) this))->fill<_T> (value);
		((Matrix*) this)->fillWithZeros<_T> ();
	}

	//	/*! + operator */
	//	Matrix_* operator +(const Matrix_<_T> &m) const {
	//		Matrix* this_Matrix = (static_cast<Matrix*> ((Matrix_*) this));
	//		Matrix m_Matrix = (static_cast<Matrix> ((Matrix_) m));
	//		Matrix* sum = *this_Matrix + m_Matrix;
	//		return (static_cast<Matrix_*> (sum));
	//	}

	/*! /= operator */
	void operator /=(const double fact) {
		for (int col = 0; col < nbCols(); ++col) {
			for (int row = 0; row < nbRows(); ++row) {
				set(row, col, get(row, col) / fact);
			}
		}
	}

	void convolveWith(const Matrix_<_T> &m) {
		((Matrix*) this)->convolveWith<_T>(m);
	}

	static Matrix_<_T> *convolve(const Matrix_<_T> &mA, const Matrix_<_T> &mB,
			Matrix_<_T> *mC = 0) {
		//		Matrix* ans = Matrix::convolve<_T>(mA, mB, mC);
		//		return (static_cast<Matrix_<_T>*> (ans));
		if (!mC)
			mC = new Matrix_<_T>(mA.nbRows(), mA.nbCols());
		Matrix::convolve<_T>(mA, mB, mC);
		return mC;
	}

};

} // end namespace math
} // end namespace rocs

#endif /* MATRIX__H_ */
