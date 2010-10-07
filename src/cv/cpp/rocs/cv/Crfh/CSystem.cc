/*
 * CSystem.cc
 *
 *  Created on: Sep 28, 2010
 *      Author: arnaud
 */

#include "rocs/cv/Crfh/CChannelCache.h"
#include "rocs/cv/Crfh/CFilterCache.h"
#include "rocs/cv/Crfh/CScaleSpaceCache.h"
#include "rocs/cv/Crfh/CCrfh.h"
#include "rocs/math/Matrix_.h"
#include "rocs/cv/Img.h"

#include "rocs/cv/Crfh/CSystem.h"
#include "rocs/core/utils.h"

namespace rocs {
namespace cv {

using rocs::math::Matrix_;

// -----------------------------------------
CSystem::CSystem(string sysDef) {
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
vector<Matrix_<double> *> CSystem::computeDescriptorOutputs(const Img &image) const {
	// Create channel cache
	CChannelCache channelCache(image);
	_descriptorList.createAllRequiredChannels(channelCache);

	// Create scale-space cache
	CScaleSpaceCache scaleSpaceCache(channelCache, _filterCache);
	_descriptorList.createAllRequiredScales(scaleSpaceCache);

	// Apply the descriptors
	return _descriptorList.applyAll(channelCache, scaleSpaceCache, _filterCache);
}

// -----------------------------------------
CCrfh *CSystem::computeHistogram(const Img &image, int skipBorderPixels) const {
	rocsDebug3("computeHistogram('%s', %i)", image.infoString().c_str(), skipBorderPixels);
	vector<Matrix_<double> *> outputs = computeDescriptorOutputs(image);
	CCrfh *crfh = new CCrfh(outputs, _descriptorList, skipBorderPixels);
	for (unsigned int i = 0; i < outputs.size(); ++i)
		delete outputs[i];
	return crfh;
}

} // end namespace cv
} // end namespace rocs
