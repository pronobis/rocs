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
 * \file Descriptor.h
 *
 * \date Sep 27, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef CDESCRIPTOR_H_
#define CDESCRIPTOR_H_

#include <string>
using std::string;

//template<typename _T> class Matrix_;

namespace rocs {

namespace math
{
template<typename _T> class Matrix_;
}

namespace cv {

class FilterCache;
class ChannelCache;
class ScaleSpaceCache;

enum DescriptorType {
	DT_UNKNOWN = 0, DT_L, DT_Lx, DT_Lxx, DT_Ly, DT_Lyy, DT_Lxy
};

/*!
 * Interface for a class defining a descriptor.
 * Descriptor can be seen as a kind of combination of the
 * information what filter to apply to which channel at
 * which scale.
 */
class Descriptor {

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(FilterCache &filterCache) = 0;

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(ScaleSpaceCache &scaleSpaceCache) = 0;

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(ChannelCache &channelCache) = 0;

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual math::Matrix_<double> *apply(const ChannelCache &channelCache,
			const ScaleSpaceCache &scaleSpaceCache,
			const FilterCache &filterCache, math::Matrix_<double> *result = 0) = 0;

public:

	/*! Creates a descriptor characterized by type. */
	static Descriptor *createDescriptor(DescriptorType descriptorType,
			double scale, int bins);

	/*! Creates a descriptor characterized by name. */
	static Descriptor *createDescriptor(string descriptorName, double scale,
			int bins);

	/*! Returns min. */
	double getMin() {
		return _min;
	}

	/*! Returns max. */
	double getMax() {
		return _max;
	}

	/*! Returns bins. */
	int getBins() {
		return _bins;
	}

protected:

	/*! Constructor. */
	inline Descriptor(DescriptorType descriptorType, double min, double max,
			double scale, int bins) :
		_descriptorType(descriptorType), _min(min), _max(max), _scale(scale),
				_bins(bins) {
	}

protected:

	/*! Type of the descriptor. */
	DescriptorType _descriptorType;

	/*! Minimum value of the filter response. */
	double _min;

	/*! Maximum value of the filter response. */
	double _max;

	/*! Scale. */
	double _scale;

	/*! Number of quantization levels for this descriptor. */
	int _bins;
};

/*!
 * L descriptor.
 */
class CLDescriptor: public Descriptor {

public:

	/*! Constructor. */
	inline CLDescriptor(double scale, int bins) :
		Descriptor(DT_L, 0.0, 255.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(FilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(ScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(ChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual math::Matrix_<double> *apply(const ChannelCache &channelCache,
			const ScaleSpaceCache &scaleSpaceCache,
			const FilterCache &filterCache, math::Matrix_<double> *result = 0);

};

/*!
 * Lxx descriptor.
 */
class CLxxDescriptor: public Descriptor {

public:

	/*! Constructor. */
	inline CLxxDescriptor(double scale, int bins) :
		Descriptor(DT_Lxx, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(FilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(ScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(ChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual math::Matrix_<double> *apply(const ChannelCache &channelCache,
			const ScaleSpaceCache &scaleSpaceCache,
			const FilterCache &filterCache, math::Matrix_<double> *result = 0);
};

/*!
 * Lx descriptor.
 */
class CLxDescriptor: public Descriptor {

public:

	/*! Constructor. */
	inline CLxDescriptor(double scale, int bins) :
		Descriptor(DT_Lx, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(FilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(ScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(ChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual math::Matrix_<double> *apply(const ChannelCache &channelCache,
			const ScaleSpaceCache &scaleSpaceCache,
			const FilterCache &filterCache, math::Matrix_<double> *result = 0);
};

/*!
 * Ly descriptor.
 */
class CLyDescriptor: public Descriptor {

public:

	/*! Constructor. */
	inline CLyDescriptor(double scale, int bins) :
		Descriptor(DT_Ly, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(FilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(ScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(ChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual math::Matrix_<double> *apply(const ChannelCache &channelCache,
			const ScaleSpaceCache &scaleSpaceCache,
			const FilterCache &filterCache, math::Matrix_<double> *result = 0);
};

/*!
 * Lyy descriptor.
 */
class CLyyDescriptor: public Descriptor {

public:

	/*! Constructor. */
	inline CLyyDescriptor(double scale, int bins) :
		Descriptor(DT_Lyy, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(FilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(ScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(ChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual math::Matrix_<double> *apply(const ChannelCache &channelCache,
			const ScaleSpaceCache &scaleSpaceCache,
			const FilterCache &filterCache, math::Matrix_<double> *result = 0);
};

/*!
 * Ly descriptor.
 */
class CLxyDescriptor: public Descriptor {

public:

	/*! Constructor. */
	inline CLxyDescriptor(double scale, int bins) :
		Descriptor(DT_Lxy, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(FilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(ScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(ChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual math::Matrix_<double> *apply(const ChannelCache &channelCache,
			const ScaleSpaceCache &scaleSpaceCache,
			const FilterCache &filterCache, math::Matrix_<double> *result = 0);
};

} // end namespace cv
} // end namespace rocs

#endif /* CDESCRIPTOR_H_ */
