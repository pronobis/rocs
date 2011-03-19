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
 * \file ImageIO.cc
 *
 * \date Jul 3, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#include "rocs/cv/ImageIO.h"

#include "rocs/core/utils.h" // for fileExists()
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

Img* ImageIO::load(const std::string filename_in) throw (core::IOException)
{
	rocsDebug3("load(%s)", filename_in.c_str());

	/*
	 * check that the file exists
	 */
	if (!rocs::core::fileExists(filename_in))
		rocsIOException("The given file '%s' does not exist.", filename_in.c_str());

#if IO_METHOD == USE_OPEN_CV
	try
	{
		/* load the image with OpenCV imread */
		opencv::Mat opencv_img = opencv::imread(filename_in.c_str());
		//	debugPrintf_lvl3("channels;%i, depth:%i", opencv_img.channels(), opencv_img.depth());

		/* create our Img object - its reallocation is done if needed during the copy */
		Img* ans = new Img(0, 0, MAT_8SC1);
		opencv_img.copyTo(*ans->asOpenCvMat());
		rocsDebug3("ans after copy:%s", ans->infoString().c_str());
		return ans;
	} // end of try
	catch (opencv::Exception error)
	{
		rocsError(error.what());
		return NULL;
	}

#else //if IO_METHOD == USE_CIMG
	//Error(-1, "Function not finished...");
	/* load the image with CImg */
	cimg_library::CImg<unsigned char> cimg(filename_in.c_str());
	int nChannels = cimg.spectrum();
	rocsDebug3("nChannels:%i", nChannels);

	/* create our Img object */
	Img* ans = new Img(cimg.width(), cimg.height(), MAT_8UC(nChannels));
	rocsDebug3("ans before copy:%s", ans->infoString().c_str());

	/* fill it with the data of the CImg */
	for (int col = 0; col < cimg.width(); ++col)
	for (int row = 0; row < cimg.height(); ++row)
	{
		if (nChannels == 1)
		ans->set<unsigned char> (row, col, cimg(row, col));
		else
		{
			for (int var = 0; var < 3; ++var)
			{
				// TODO how to solve this ?
				ans->set<unsigned char> (row, col, cimg(col, row,
								2 - var));
			}
		}
	}
	return ans;
#endif
}

int ImageIO::write(const Img& img, const std::string filename_out)  throw (core::IOException)
{
#if IO_METHOD == USE_OPEN_CV
	/* load the image with OpenCV imread */
	bool success = opencv::imwrite(filename_out, img.asConstOpenCvMat());
	return success;
#else //if IO_METHOD == USE_CIMG
	// TODO write for CImg
	rocsError("ImageIO::write() not implemented with CImg");
	return -1;
#endif
}
