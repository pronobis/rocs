/*
 * CScaleSpaceCache.cc
 *
 *  Created on: Sep 27, 2010
 *      Author: arnaud
 */

#include "rocs/math/Matrix_.h"
#include "rocs/cv/Crfh/CFilter.h"
#include "rocs/cv/Crfh/CChannelCache.h"
#include "rocs/cv/Crfh/CFilterCache.h"

#include "rocs/cv/Crfh/CScaleSpaceCache.h"

namespace rocs {
namespace cv {

// -----------------------------------------
CScaleSpaceCache::~CScaleSpaceCache() {
	for (unsigned int i = 0; i < _scaleSpaceSamplesList.size(); ++i)
		delete _scaleSpaceSamplesList[i].matrix;
}

// -----------------------------------------
void CScaleSpaceCache::createScaleSpaceSample(ChannelType channelType,
		double scale) {
	debug3("createScaleSpaceSample(%i, %f)", channelType, scale);

	// Check if we don't have the sample in the cache
	for (unsigned int i = 0; i < _scaleSpaceSamplesList.size(); ++i)
		if ((_scaleSpaceSamplesList[i].channelType == channelType)
				&& (_scaleSpaceSamplesList[i].scale == scale))
			return;

	// Create a new sample
	CScaleSpaceSampleInfo sssi;
	sssi.channelType = channelType;
	sssi.scale = scale;

	CGaussianFilterInfo gfi(scale);
	debug3("in:(%s)", (_channelCache->getChannel(
							channelType))->infoString().c_str());
	sssi.matrix = _filterCache->applyFilter(gfi, *(_channelCache->getChannel(
			channelType)));

	// Append sample to the list
	_scaleSpaceSamplesList.push_back(sssi);
}

// -----------------------------------------
const Matrix_<double> *CScaleSpaceCache::getScaleSpaceSample(
		ChannelType channelType, double scale) const {
	for (unsigned int i = 0; i < _scaleSpaceSamplesList.size(); ++i)
		if ((_scaleSpaceSamplesList[i].channelType == channelType)
				&& (_scaleSpaceSamplesList[i].scale == scale))
			return _scaleSpaceSamplesList[i].matrix;

	return 0;
}

} // end namespace cv
} // end namespace rocs
