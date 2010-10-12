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
 * \file ScaleSpaceCache.h
 *
 * \date Sep 27, 2010
 * \author Andrzej Pronobis
 *
 * Contains declaration of the ScaleSpaceCache class.
 */

#ifndef CSCALESPACECACHE_H_
#define CSCALESPACECACHE_H_

#include "rocs/cv/Crfh/ChannelCache.h"
#include <vector>
using std::vector;

namespace rocs {
namespace cv {

class FilterCache;
template<typename _T> class Matrix_;

/*!
 * Struct storing information about a scale-space sample.
 */
struct ScaleSpaceSampleInfo {
	ChannelType channelType;
	double scale;
	Matrix_<double> *matrix;
};

/*!
 * Cache storing samples of the scale-space.
 */
class ScaleSpaceCache {

public:

	/*! Default constructor. */
	inline ScaleSpaceCache(const ChannelCache &channelCache,
			const FilterCache &filterCache) :
		_channelCache(&channelCache), _filterCache(&filterCache) {
	}
	;

	/*! Destructor. Deletes all the scale-space samples. */
	~ScaleSpaceCache();

public:

	/*! Creates a sample of the scale-space obtained from a given
	 channel. If an identical sample already exists a new one will
	 not be created. */
	void createScaleSpaceSample(ChannelType channelType, double scale);

	/*! Returns a pointer to a matrix containing pixels of the scale-space sample. */
	const Matrix_<double>
			*getScaleSpaceSample(ChannelType channelType, double scale) const;

private:

	/*! Pointer to the channel cache. */
	const ChannelCache *_channelCache;

	/*! Pointer to the filter cache. */
	const FilterCache *_filterCache;

	/*! List storing information about samples. */
	vector<ScaleSpaceSampleInfo> _scaleSpaceSamplesList;

};

} // end namespace cv
} // end namespace rocs

#endif /* CSCALESPACECACHE_H_ */
