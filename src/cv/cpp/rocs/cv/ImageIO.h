/*
 * ImageIO.h
 *
 *  Created on: Jul 3, 2010
 *      Author: arnaud
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
