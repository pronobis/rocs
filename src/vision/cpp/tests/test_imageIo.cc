// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2010  Andrzej Pronobis
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
 * Example test suite.
 * For more information see:
 * http://www.boost.org/doc/libs/1_44_0/libs/test/doc/html/utf/user-guide.html
 * \author Arnaud Ramey, Andrzej Pronobis
 * \file test_imageIo.cc
 */

// Boost
#include <boost/test/unit_test.hpp>
// ROCS
#include "rocs/cv/ImageIO.h"

#define ROCSDIR "../../"
#define IMGDIR ROCSDIR "data/images/"

/*!
 * a test case for a fictive image
 */
BOOST_AUTO_TEST_CASE( caseFictiveImage)
{
	BOOST_REQUIRE_THROW(//
			rocs::cv::ImageIO::load("fictive.foo"),//
			rocs::core::IOException//
	);
}

/*!
 * a test case for a non fictive image
 */
BOOST_AUTO_TEST_CASE( caseNonFictiveImage)
{
	BOOST_REQUIRE_NO_THROW(//
			rocs::cv::ImageIO::load(IMGDIR "small.png")//
	);
}


/*!
 * a routine for displaying a variable and checking its value is as expected
 */
#define DISPLAY_AND_CHECK_VALUE(value, expectedValue, msg) \
	rocsDebug3("%s:%i (expected:%i)", msg, value, expectedValue); \
	BOOST_CHECK( value == expectedValue );

/*!
 * a test case for splitting channels
 */
BOOST_AUTO_TEST_CASE( caseSplitChannels )
{
	rocs::cv::Img* img = rocs::cv::ImageIO::load(IMGDIR "small.png");
	// with this image, (0, 1) = (255, 128, 0)

	rocs::cv::Img channel_red(img->nbRows(), img->nbCols(), MAT_8U );
	rocs::cv::Img channel_green(img->nbRows(), img->nbCols(), MAT_8U );
	rocs::cv::Img channel_blue(img->nbRows(), img->nbCols(), MAT_8U );

	/*
	 * extraction of one channel
	 */
	img->splitToOneChannel(0, &channel_green, 0, 0);
	//rocsDebug3("channel_green:%s", channel_green.toString().c_str());
	DISPLAY_AND_CHECK_VALUE( channel_green.get<uchar> (0, 1) , 128, "green");

	/*
	 * extraction of 2 channels
	 */
	img->splitToOneChannel(0, &channel_green, &channel_red, 0);
	//rocsDebug3("channel_blue:%s", channel_blue.toString().c_str());
	DISPLAY_AND_CHECK_VALUE( channel_green.get<uchar> (0, 1) , 128, "green");
	DISPLAY_AND_CHECK_VALUE( channel_red.get<uchar> (0, 1) , 255, "red");

	/*
	 * extraction of 3 channels
	 */
	img->splitToOneChannel(&channel_blue, &channel_green, &channel_red, 0);
	//	rocsDebug3("channel_red:%s", channel_red.toString().c_str());
	//	rocsDebug3("channel_blue:%s", channel_blue.toString().c_str());
	DISPLAY_AND_CHECK_VALUE( channel_green.get<uchar> (0, 1) , 128, "green");
	DISPLAY_AND_CHECK_VALUE( channel_red.get<uchar> (0, 1) , 255, "red");
	DISPLAY_AND_CHECK_VALUE( channel_blue.get<uchar> (1, 0) , 255, "blue");

}
