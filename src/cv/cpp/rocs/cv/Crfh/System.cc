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
 * \file System.cc
 *
 * \date Sep 28, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#include "rocs/cv/Crfh/ChannelCache.h"
#include "rocs/cv/Crfh/FilterCache.h"
#include "rocs/cv/Crfh/ScaleSpaceCache.h"
#include "rocs/cv/Crfh/Crfh.h"
#include "rocs/math/Matrix_.h"
#include "rocs/cv/Img.h"

#include "rocs/cv/Crfh/System.h"
#include "rocs/core/utils.h"

namespace rocs {
namespace cv {

//using rocs::math::Matrix_;

// -----------------------------------------
System::System(string sysDef) {
	rocsDebug3("CSystem::CSystem('%s')", sysDef.c_str());

	// Exemplar string:
	// Lxx(8,28)+Lxy(8,28)+Lyy(8,28)+Lxx(2,28)+Lxy(2,28)+Lyy(2,28)

	// Extract tokens
	//stringList tokens = sysDef.split('+');
	vector<string> tokens;
	rocs::core::splitString(sysDef, "+", tokens);

	// Create descriptors
	for (unsigned int i = 0; i < tokens.size(); ++i) {
		// Decode params
		int bracket1Pos = tokens[i].find('(');
		int comaPos = tokens[i].find(',');
		int bracket2Pos = tokens[i].find(')');
		//string name = tokens[i].left(bracket1Pos);
		string name = tokens[i].substr(0, bracket1Pos);
		double scale = atof(tokens[i].substr(bracket1Pos + 1, comaPos
				- bracket1Pos - 1).c_str());
		// scale = tokens[i].mid(bracket1Pos + 1, comaPos - bracket1Pos - 1).toDouble();
		int
				bins = atoi(tokens[i].substr(comaPos + 1, bracket2Pos - comaPos
						- 1).c_str());
		// bins = tokens[i].substr(comaPos + 1, bracket2Pos - comaPos - 1).toInt();

		rocsDebug3("Name:%s, scale:%f, bins:%i", name.c_str(), scale, bins);

		// Create descriptor
		_descriptorList.addDescriptor(name, scale, bins);
	}

	// Create filters
	_descriptorList.createAllRequiredFilters(_filterCache);

	rocsDebug3("CSystem now initialized.");
}

// -----------------------------------------
vector<math::Matrix_<double> *> System::computeDescriptorOutputs(const Img &image) const {
	// Create channel cache
	ChannelCache channelCache(image);
	_descriptorList.createAllRequiredChannels(channelCache);

	// Create scale-space cache
	ScaleSpaceCache scaleSpaceCache(channelCache, _filterCache);
	_descriptorList.createAllRequiredScales(scaleSpaceCache);

	// Apply the descriptors
	return _descriptorList.applyAll(channelCache, scaleSpaceCache, _filterCache);
}

// -----------------------------------------
Crfh *System::computeHistogram(const Img &image, int skipBorderPixels) const {
	rocsDebug3("computeHistogram('%s', %i)", image.infoString().c_str(), skipBorderPixels);
	vector<math::Matrix_<double> *> outputs = computeDescriptorOutputs(image);
	Crfh *crfh = new Crfh(outputs, _descriptorList, skipBorderPixels);
	for (unsigned int i = 0; i < outputs.size(); ++i)
		delete outputs[i];
	return crfh;
}

} // end namespace cv
} // end namespace rocs
