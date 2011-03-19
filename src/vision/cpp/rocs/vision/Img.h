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

	/*! Returns the intensity channel L as a matrix of doubles. */
	math::Matrix_<double> *getL(math::Matrix_<double> *L = 0) const;

};

} // end namespace cv
} // end namespace rocs

#endif /* IMG_H_ */
