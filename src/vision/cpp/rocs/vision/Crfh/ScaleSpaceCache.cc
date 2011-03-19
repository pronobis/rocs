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
 * \file ScaleSpaceCache.cc
 *
 * \date Sep 27, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#include "rocs/cv/Crfh/Filter.h"
#include "rocs/cv/Crfh/ChannelCache.h"
#include "rocs/cv/Crfh/FilterCache.h"

#include "rocs/cv/Crfh/ScaleSpaceCache.h"

namespace rocs {
namespace cv {

// -----------------------------------------
ScaleSpaceCache::~ScaleSpaceCache() {
	for (unsigned int i = 0; i < _scaleSpaceSamplesList.size(); ++i)
		delete _scaleSpaceSamplesList[i].matrix;
}

// -----------------------------------------
void ScaleSpaceCache::createScaleSpaceSample(ChannelType channelType,
		double scale) {
	rocsDebug3("createScaleSpaceSample(%i, %f)", channelType, scale);

	// Check if we don't have the sample in the cache
	for (unsigned int i = 0; i < _scaleSpaceSamplesList.size(); ++i)
		if ((_scaleSpaceSamplesList[i].channelType == channelType)
				&& (_scaleSpaceSamplesList[i].scale == scale))
			return;

	// Create a new sample
	ScaleSpaceSampleInfo sssi;
	sssi.channelType = channelType;
	sssi.scale = scale;

	CGaussianFilterInfo gfi(scale);
	rocsDebug3("in:(%s)", (_channelCache->getChannel(
							channelType))->infoString().c_str());
	sssi.matrix = _filterCache->applyFilter(gfi, *(_channelCache->getChannel(
			channelType)));

	// Append sample to the list
	_scaleSpaceSamplesList.push_back(sssi);
}

// -----------------------------------------
const Matrix_<double> *ScaleSpaceCache::getScaleSpaceSample(
		ChannelType channelType, double scale) const {
	for (unsigned int i = 0; i < _scaleSpaceSamplesList.size(); ++i)
		if ((_scaleSpaceSamplesList[i].channelType == channelType)
				&& (_scaleSpaceSamplesList[i].scale == scale))
			return _scaleSpaceSamplesList[i].matrix;

	return 0;
}

} // end namespace cv
} // end namespace rocs
