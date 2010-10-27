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
#include "rocs/cv/FeatureList.h"
#include "rocs/cv/ImageIO.h"
//#include "rocs/cv/Crfh/Crfh.h"
#include "rocs/cv/Crfh/CrfhInterface.h"
// stl
#include <iostream>
using namespace std;

#define ROCSDIR "../../"
#define IMGDIR ROCSDIR "data/images/"

/*!
 * a test case for a simple image
 */
BOOST_AUTO_TEST_CASE( caseFeatureList )
{
	rocs::cv::FeatureList<int, double> testFeatureList;
	testFeatureList.increase_if_found(1);
	testFeatureList.increase_if_found(1);
	testFeatureList.increase_if_found(2);
	testFeatureList.increase_if_found(4);
	testFeatureList.insert_(3, 10);
	// there should be 4 elements : 1->2, 2->1, 3->10, 4->1
	testFeatureList.serialize(cout, true);
	BOOST_CHECK( testFeatureList.size() == 4);

	testFeatureList.filter(0.2);
	// there should be 2 elements : 1->2, 3->10
	testFeatureList.serialize(cout, true);
	BOOST_CHECK( testFeatureList.size() == 2);
	BOOST_CHECK( testFeatureList.at(1) == 2);
	BOOST_CHECK( testFeatureList.at(3) == 10);
}

/*!
 * a test case for a given image
 * @param filenamePpm the input image
 * @param filenameCrfh the correct result file
 */
void testCrfh(const char* filenamePpm, const char* filenameCrfh)
{
	using namespace rocs::cv;
	CrfhInterface crfhInterface;
	crfhInterface.defineSystem("Lxx(8,28)");
	crfhInterface.start();

	/*
	 * method 1 : load the Img separately and pass it
	 * method 2 : directly give the filename to the feature extractor
	 */
	for (int imgLoadMethod = 1; imgLoadMethod <= 2; ++imgLoadMethod)
	{
		Crfh* featureList;
		string result;
		if (imgLoadMethod == 1) // load separately
		{
			Img* img = ImageIO::load(filenamePpm);
			featureList = crfhInterface.processImage(img);

			/*
			 * compute sum manually in the feature list to check it is conform
			 */
			double sum = 0;
			for (Crfh::iterator it = featureList->begin(); it
					!= featureList->end(); ++it)
				sum += it->second;
			//BOOST_CHECK(sum == featureList->_sum);

			ostringstream resultStream;
			featureList->serialize(resultStream, true);
			result = resultStream.str();

			delete img;
		}
		else // load the image indirectly
		{
			string fileIn = filenamePpm;
			string fileOut = "out.txt";
			crfhInterface.process(fileIn, fileOut);
			result = rocs::core::readFile(fileOut.c_str());
		}

		/*
		 * check that the result string is the same as expected
		 */
		string correctResult = rocs::core::readFile(filenameCrfh);
		rocsDebug3("result:\n'%s'\n, correctResult:\n'%s'", result.c_str(), correctResult.c_str());
		BOOST_CHECK(result == correctResult);
	} // end loop method

	/*
	 * clean
	 */
	crfhInterface.end();
}

BOOST_AUTO_TEST_CASE( caseCrfh )
{
	testCrfh(IMGDIR "Coffee_nb.ppm", IMGDIR "Coffee_nb_Lxx(8,28).crfh");
	testCrfh(IMGDIR "box.ppm", IMGDIR "box_Lxx(8,28).crfh");
}

