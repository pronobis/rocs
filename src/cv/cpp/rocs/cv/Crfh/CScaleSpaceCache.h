/*
 * CScaleSpaceCache.h
 *
 *  Created on: Sep 27, 2010
 *      Author: arnaud
 */

#ifndef CSCALESPACECACHE_H_
#define CSCALESPACECACHE_H_

/**
 * \file CScaleSpaceCache.h
 * \author Andrzej Pronobis
 *
 * Contains declaration of the CScaleSpaceCache class.
 */

#include "rocs/cv/Crfh/CChannelCache.h"
#include <vector>
using std::vector;

namespace rocs {
namespace cv {

class CFilterCache;
template<typename _T> class Matrix_;

/**
 * Struct storing information about a scale-space sample.
 */
struct CScaleSpaceSampleInfo {
	ChannelType channelType;
	double scale;
	Matrix_<double> *matrix;
};

/**
 * Cache storing samples of the scale-space.
 */
class CScaleSpaceCache {

public:

	/** Default constructor. */
	inline CScaleSpaceCache(const CChannelCache &channelCache,
			const CFilterCache &filterCache) :
		_channelCache(&channelCache), _filterCache(&filterCache) {
	}
	;

	/** Destructor. Deletes all the scale-space samples. */
	~CScaleSpaceCache();

public:

	/** Creates a sample of the scale-space obtained from a given
	 channel. If an identical sample already exists a new one will
	 not be created. */
	void createScaleSpaceSample(ChannelType channelType, double scale);

	/** Returns a pointer to a matrix containing pixels of the scale-space sample. */
	const Matrix_<double>
			*getScaleSpaceSample(ChannelType channelType, double scale) const;

private:

	/** Pointer to the channel cache. */
	const CChannelCache *_channelCache;

	/** Pointer to the filter cache. */
	const CFilterCache *_filterCache;

	/** List storing information about samples. */
	vector<CScaleSpaceSampleInfo> _scaleSpaceSamplesList;

};

} // end namespace cv
} // end namespace rocs

#endif /* CSCALESPACECACHE_H_ */
