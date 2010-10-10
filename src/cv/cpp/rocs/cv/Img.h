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
 * \file Img.h
 *
 * \date Jul 3, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
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
