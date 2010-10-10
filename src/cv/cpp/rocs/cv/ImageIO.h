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
 * \file ImageIO.h
 *
 * \date Jul 3, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef IMAGEIO_H_
#define IMAGEIO_H_

#include <iostream>

#include "rocs/cv/Img.h"

namespace rocs {
namespace cv {

/*!
 * some functions to load / write images
 */
class ImageIO {
public:
	static Img* load(std::string filename_in);
	static int write(Img* img, std::string filename_out);
};

} // end namespace cv
} // end namespace rocs

#endif /* IMAGEIO_H_ */
