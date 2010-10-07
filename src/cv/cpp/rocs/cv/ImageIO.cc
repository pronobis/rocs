/*
 * ImageIO.cpp
 *
 *  Created on: Jul 3, 2010
 *      Author: arnaud
 */

#include "rocs/cv/ImageIO.h"

// rename the opencv namespace not to collide with rocs::cv
namespace opencv = cv;
using namespace rocs::cv;

#define USE_OPEN_CV  1
#define USE_CIMG     2
#define IO_METHOD	USE_OPEN_CV

#if IO_METHOD == USE_OPEN_CV
#include "opencv/highgui.h"
#else //if IO_METHOD == USE_CIMG
#include "CImg.h"
#endif

Img* ImageIO::load(std::string filename_in) {
	rocsDebug3("load(%s)", filename_in.c_str());

#if IO_METHOD == USE_OPEN_CV
	/* load the image with OpenCV imread */
	opencv::Mat opencv_img = opencv::imread(filename_in.c_str());
	//	debugPrintf_lvl3("channels;%i, depth:%i", opencv_img.channels(), opencv_img.depth());

	/* create our Img object */
	Img* ans = new Img(opencv_img.rows, opencv_img.cols, MAT_8SC1);
	//	debugPrintf_lvl3("ans:channels;%i, depth:%i", ans->channels(), ans->depth());
	opencv_img.copyTo( *ans->asOpenCvMat());
	rocsDebug3("ans after copy:channels;%i, depth:%i", ans->channels(), ans->depth());
	return ans;

#else //if IO_METHOD == USE_CIMG
	/* load the image with CImg */
	cimg_library::CImg<unsigned char>* cimg = new cimg_library::CImg<
	unsigned char>(filename_in.c_str());
	// create our Img object
	Img* ans = new Img(cimg->width(), cimg->height(), MAT_8U);
	/* fill it with the data of the CImg */
	//Error(-1, "Function not finished...");
	for (int col = 0; col < cimg->width(); ++col)
	for (int row = 0; row < cimg->height(); ++row)
	ans->set(row, col, 0);//(*cimg)(row, col));
	delete cimg;
	return ans;
#endif
}

int ImageIO::write(Img* img, std::string filename_out) {
	// TODO using OpenCV ? CImg ?
	return -1;
}
