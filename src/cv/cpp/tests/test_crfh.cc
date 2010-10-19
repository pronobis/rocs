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
#include "rocs/cv/Crfh/CrfhInterface.h"

#define ROCSDIR "../../"
#define IMGDIR ROCSDIR "data/images/"

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
#include "rocs/cv/FeatureList.h"

#define ROCSDIR "../../"
#define IMGDIR ROCSDIR "data/images/"

/*!
 * a test case for a simple image
 */
BOOST_AUTO_TEST_CASE( caseFeatureList )
{
	FeatureList<int, double> test;
	test.insert( pair<int, double>(1, 0.1f) );
	test.insert( pair<int, double>(2, 0.2f) );
	test.insert( pair<int, double>(3, 0.3f) );
	BOOST_CHECK( test.size() == 3);

	test.filter(2);
	cout << "size:" << test.size() << endl;
	BOOST_CHECK( test.size() == 2);
}



///*!
// * a test case for a simple image
// */
//BOOST_AUTO_TEST_CASE( caseSimpleImage )
//{
//	rocs::cv::Img* img = rocs::cv::ImageIO::load(IMGDIR "small.png");
//	rocs::cv::CrfhInterface interface;
//	interface.defineSystem(
//			"Lxx(8,28)+Lxy(8,28)+Lyy(8,28)+Lxx(2,28)+Lxy(2,28)+Lyy(2,28)");
//	rocs::cv::Crfh* feature = interface.processImage(img);
//
//	delete img;
//}

