/*
 * Img.h
 *
 *  Created on: Jul 3, 2010
 *      Author: arnaud
 */

#ifndef IMG_H_
#define IMG_H_

#include "rocs/math/Matrix_.h"

namespace rocs {
namespace cv {

/*!
 * the representation of an image
 */
class Img: public math::Matrix {
public:
	Img(int rows, int cols, int type);
	virtual ~Img();

	//	template<typename _T>
	//	inline _T get(const int row, const int col) const {
	//		return ((Matrix*) this)->get<_T> (row, col);
	//	}
	//
	//	template<typename _T>
	//	inline void set(int row, int col, _T value) {
	//		((Matrix*) this)->set<_T> (row, col, value);
	//	}

	//	opencv::Mat* asOpenCvMat() {
	//		math::Matrix* thisMatrix = this;
	//		return thisMatrix->asOpenCvMat();
	//	}
	//
	//	const opencv::Mat asConstOpenCvMat() {
	//		return ((math::Matrix*) this)->asConstOpenCvMat();
	//	}

	/*! Returns the intensity channel L as a matrix of doubles. */
	math::Matrix_<double> *getL(math::Matrix_<double> *L = 0) const;

};

} // end namespace cv
} // end namespace rocs

#endif /* IMG_H_ */
