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
 * \author Andrzej Pronobis
 * \file test_imageIo.cc
 */

// Boost
#include <boost/test/unit_test.hpp>
// ROCS
#include "rocs/cv/ImageIO.h"

#define ROCSDIR "../../"
#define IMGDIR ROCSDIR "data/images/"

/*! Define first test case. */
BOOST_AUTO_TEST_CASE( case1 )
{
	char filename[100];
	sprintf(filename, "%s%s", IMGDIR, "small.png");
	rocs::cv::Img* img = rocs::cv::ImageIO::load(filename);

	rocs::cv::Img channel1 ( img->nbRows(), img->nbCols(), img->getDataType() );
	img->splitToOneChannel(0, &channel1, 0, 0);

	std::cout << img->toString() << std::endl;
	int pixelComp = img->get<uchar>(2,2);
	// (1, 0) = (255, 128, 0)
	rocsDebug3("pixelComp:%i", pixelComp);
	BOOST_CHECK( pixelComp == 0 );

	//BOOST_REQUIRE( 0 == 0 );
}

