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
#include "rocs/cv/FeatureExtractor.h"
#include "rocs/cv/Crfh/System.h"
#include "rocs/cv/Crfh/Crfh.h"

// STD includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

namespace rocs
{
namespace cv
{

class CrfhInterface: public rocs::cv::FeatureExtractor<Crfh>
{
public:
	/*! ctor */
	CrfhInterface()
	{
		rocsDebug3("CrfhInterface()");
		setDefaultParams();
	}
	/*! dtor */
	virtual ~CrfhInterface()
	{
	}

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
		//System _syst(sysDescr);
		_syst.build(sysDescr);
	}

	/*!
	 * set the minimal value for the histogram
	 * \param minHistValue
	 */
	void setMinHistValue(double minHistValue)
	{
		rocsDebug3("setMinHistValue(%f)", minHistValue);
		_minHistValue = minHistValue;
	}

	/*!
	 * set the width of the border that is not analyzed in the image
	 * \param skipBorderPixels
	 */
	void setSkipBorderPixels(int skipBorderPixels)
	{
		_skipBorderPixels = skipBorderPixels;
	}

	void setDefaultParams()
	{
		rocsDebug3("setDefaultParams()");
		/* default params */
		_minHistValue = 0;
		_skipBorderPixels = 15;
	}

	void start()
	{
		rocsDebug3("start()");
		/* reset timer */
		_totalTime = 0;
		_nbImagesTreated = 0;
	}

	void end()
	{
		rocsDebug3("end()");
		// nothing to do
	}

	Crfh* processImage(const Img* image)
	{
		rocsDebug1("processImage(%s)", image->infoString().c_str());
		_t.reset();

		// make the actual computation
		Crfh *crfh = _syst.computeHistogram(*image, _skipBorderPixels);
		if (_minHistValue > 0)
			crfh->filter(_minHistValue);
		crfh->normalize();
		// update timer
		_totalTime += _t.getTimeMilliseconds();
		_nbImagesTreated++;
		return crfh;
	}

private:
	System _syst;
	double _minHistValue;
	int _skipBorderPixels;
};

} // end namespace cv
} // end namespace rocs

#endif /* CRFHINTERFACE_H_ */

