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
 * \file FeatureExtractor.h
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef FEATUREEXTRACTOR_H_
#define FEATUREEXTRACTOR_H_

// rocs includes
#include "rocs/cv/FeatureList.h"
#include "rocs/cv/ImageIO.h"
#include "rocs/core/Timer.h"
#include "rocs/core/debug.h"
#include "rocs/core/utils.h"
#include "rocs/core/error.h"

// STD includes
#include <vector>
#include <string>
using std::string;

/*!
 * a pure virtual class
 */
namespace rocs
{
namespace cv
{

class Img;

template<typename featureType>
class FeatureExtractor
{
public:
	/*! ctor */
	FeatureExtractor()
	{
	}
	/*! dtor */
	virtual ~FeatureExtractor()
	{
	}

	/*! set the misc parameters to their default value */
	virtual void setDefaultParams() = 0;
	/*! start the feature extractor
	 * 	don't forget to do :
	 * _totalTime = 0;
	 * _nbImagesTreated = 0;
	 * */
	virtual void start() = 0;
	/*! stop the feature extractor */
	virtual void end() = 0;
	/*!
	 * analyze a given image
	 * \param frame the image to analyze
	 * \return the feature
	 */
	virtual featureType* processImage(const Img* frame) = 0;

	/*!
	 * process a bunch of pictures
	 * \param inputFileName
	 * \param outputFileName where to save the results
	 */
	void process(const string inputFileName, const string outputFileName)
	{
		rocsDebug1("inputFileName:%s, outputFileName:%s",
				inputFileName.c_str(), outputFileName.c_str());

		/* load input files */
		vector<string> imageFileList;
		core::loadFilenameList(inputFileName, imageFileList);

		/* Open the output file */
		ofstream outputFileStream(outputFileName.c_str(), ios::out);
		if (!outputFileStream.is_open())
		{ /* ok, proceed with output */
			rocsError("ERROR: Unable to open the output file!");
		}

		/* Extract features from each file */
		rocsDebug3("\n\n* Processing files:");

		for (unsigned int i = 0; i < imageFileList.size(); ++i)
		{
			rocsDebug1("\n\n(%f percent) : %s", (((double) i + 1)
							/ ((double) imageFileList.size())) * 100.0,
					imageFileList[i].c_str());

			/* Load an image */
			Img* image = ImageIO::load(imageFileList[i]);

			/* Perform histogram extraction */
			featureType* crfh = processImage(image);
			rocsDebug3("\n\nComputing finished for this image !");

			/* Save the histogram to the output file */
			//			if (classLabelList[i] != "")
			//				outputFileStream << classLabelList[i] << " ";
			crfh->serialize(outputFileStream);
			//crfh->serialize(cout);
			if (i < imageFileList.size() - 1)
				outputFileStream << endl;

			/* Delete the histogram */
			delete crfh;
		} // end loop image

		/* Display average time */
		rocsDebug1("\n\n* Finished! Average processing time per image: %f ms",
				averageTime());

		/* Close the output file */
		outputFileStream.close();

		//return EXIT_SUCCESS;
	} // end process

	//private:
	Timer _t;
	long _totalTime;
	int _nbImagesTreated;
	double averageTime()
	{
		return _totalTime / _nbImagesTreated;
	}

};

} // end namespace cv
} // end namespace rocs

#endif /* FEATUREEXTRACTOR_H_ */
