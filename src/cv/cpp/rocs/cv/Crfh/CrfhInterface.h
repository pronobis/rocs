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
 * \file CrfhInterface.h
 *
 * \date Oct 7, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef CRFHINTERFACE_H_
#define CRFHINTERFACE_H_

// rocs includes
#include "rocs/cv/FeatureList.h"
#include "rocs/cv/ImageIO.h"
#include "rocs/cv/Crfh/System.h"
#include "rocs/cv/Crfh/Crfh.h"
#include "rocs/core/debug.h"
#include "rocs/core/error.h"
#include "rocs/core/Timer.h"
#include "rocs/core/utils.h"

// STD includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

namespace rocs
{
namespace cv
{

class CrfhInterface
{
public:
	CrfhInterface();
	virtual ~CrfhInterface();

	/*!
	 * Initializes the system (creates descriptors and filters).
	 * \param sysDef Exemple string:
	 * Lxx(8,28)+Lxy(8,28)+Lyy(8,28)+Lxx(2,28)+Lxy(2,28)+Lyy(2,28)
	 *
	 */
	void defineSystem(string sysDescr)
	{
		rocsDebug1("defineSystem(sysDescr:'%s'", sysDescr.c_str());

		/* Define a system */
		//System syst(sysDescr);
		syst.build(sysDescr);

		/* reset timer */
		totalTime = 0;
		nbImagesTreated = 0;
	}

	void process(string inputFileName, string outputFileName,
			double minHistValue = 0)
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
			Crfh* crfh = processImage(image, minHistValue);
			rocsDebug3("\n\nComputing finished for this image !");

			/* Save the histogram to the output file */
			//			if (classLabelList[i] != "")
			//				outputFileStream << classLabelList[i] << " ";
			crfh->serialize(outputFileStream);
			//crfh->serialize(cout);
			outputFileStream << endl;

			/* Delete the histogram */
			delete crfh;
		} // end loop image

		/* Display average time */
		rocsDebug1(
				"\n\n* Finished! Average processing time per image: %f ms",
				averageTime());

		/* Close the output file */
		outputFileStream.close();

		//return EXIT_SUCCESS;
	}

	Crfh* processImage(Img* image, double minHistValue = 0)
	{
		rocsDebug1("processImage(%s)", image->infoString().c_str());
		t.reset();
		// make the actual computation
		Crfh *crfh = syst.computeHistogram(*image, 15);
		if (minHistValue > 0)
			crfh->filter(minHistValue);
		crfh->normalize();
		// update timer
		totalTime += t.getTimeMilliseconds();
		nbImagesTreated++;
		return crfh;
	}

private:
	System syst;
	Timer t;
	long totalTime;
	int nbImagesTreated;
	double averageTime()
	{
		return totalTime / nbImagesTreated;
	}
};

} // end namespace cv
} // end namespace rocs

#endif /* CRFHINTERFACE_H_ */

