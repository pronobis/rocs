/*
 * CDescriptor.h
 *
 *  Created on: Sep 27, 2010
 *      Author: arnaud
 */

#ifndef CDESCRIPTOR_H_
#define CDESCRIPTOR_H_

#include <string>
using std::string;

template<typename _T> class Matrix_;

namespace rocs {
namespace cv {

class CFilterCache;
class CChannelCache;
class CScaleSpaceCache;

enum DescriptorType {
	DT_UNKNOWN = 0, DT_L, DT_Lx, DT_Lxx, DT_Ly, DT_Lyy, DT_Lxy
};

/*!
 * Interface for a class defining a descriptor.
 * Descriptor can be seen as a kind of combination of the
 * information what filter to apply to which channel at
 * which scale.
 */
class CDescriptor {

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(CFilterCache &filterCache) = 0;

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(CScaleSpaceCache &scaleSpaceCache) = 0;

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(CChannelCache &channelCache) = 0;

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual Matrix_<double> *apply(const CChannelCache &channelCache,
			const CScaleSpaceCache &scaleSpaceCache,
			const CFilterCache &filterCache, Matrix_<double> *result = 0) = 0;

public:

	/*! Creates a descriptor characterized by type. */
	static CDescriptor *createDescriptor(DescriptorType descriptorType,
			double scale, int bins);

	/*! Creates a descriptor characterized by name. */
	static CDescriptor *createDescriptor(string descriptorName, double scale,
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
	inline CDescriptor(DescriptorType descriptorType, double min, double max,
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
class CLDescriptor: public CDescriptor {

public:

	/*! Constructor. */
	inline CLDescriptor(double scale, int bins) :
		CDescriptor(DT_L, 0.0, 255.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(CFilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(CScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(CChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual Matrix_<double> *apply(const CChannelCache &channelCache,
			const CScaleSpaceCache &scaleSpaceCache,
			const CFilterCache &filterCache, Matrix_<double> *result = 0);

};

/*!
 * Lxx descriptor.
 */
class CLxxDescriptor: public CDescriptor {

public:

	/*! Constructor. */
	inline CLxxDescriptor(double scale, int bins) :
		CDescriptor(DT_Lxx, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(CFilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(CScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(CChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual Matrix_<double> *apply(const CChannelCache &channelCache,
			const CScaleSpaceCache &scaleSpaceCache,
			const CFilterCache &filterCache, Matrix_<double> *result = 0);
};

/*!
 * Lx descriptor.
 */
class CLxDescriptor: public CDescriptor {

public:

	/*! Constructor. */
	inline CLxDescriptor(double scale, int bins) :
		CDescriptor(DT_Lx, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(CFilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(CScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(CChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual Matrix_<double> *apply(const CChannelCache &channelCache,
			const CScaleSpaceCache &scaleSpaceCache,
			const CFilterCache &filterCache, Matrix_<double> *result = 0);
};

/*!
 * Ly descriptor.
 */
class CLyDescriptor: public CDescriptor {

public:

	/*! Constructor. */
	inline CLyDescriptor(double scale, int bins) :
		CDescriptor(DT_Ly, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(CFilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(CScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(CChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual Matrix_<double> *apply(const CChannelCache &channelCache,
			const CScaleSpaceCache &scaleSpaceCache,
			const CFilterCache &filterCache, Matrix_<double> *result = 0);
};

/*!
 * Lyy descriptor.
 */
class CLyyDescriptor: public CDescriptor {

public:

	/*! Constructor. */
	inline CLyyDescriptor(double scale, int bins) :
		CDescriptor(DT_Lyy, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(CFilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(CScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(CChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual Matrix_<double> *apply(const CChannelCache &channelCache,
			const CScaleSpaceCache &scaleSpaceCache,
			const CFilterCache &filterCache, Matrix_<double> *result = 0);
};

/*!
 * Ly descriptor.
 */
class CLxyDescriptor: public CDescriptor {

public:

	/*! Constructor. */
	inline CLxyDescriptor(double scale, int bins) :
		CDescriptor(DT_Lxy, -128.0, 128.0, scale, bins) {
	}

public:

	/*! Creates all the required filters in the filter cache. */
	virtual void createRequiredFilters(CFilterCache &filterCache);

	/*! Creates all the samples of the scale-space in the scale-space cache. */
	virtual void createRequiredScales(CScaleSpaceCache &scaleSpaceCache);

	/*! Creates all the required channels in the channel cache. */
	virtual void createRequiredChannels(CChannelCache &channelCache);

	/*! Applies the descriptor to the proper channel using proper filters. */
	virtual Matrix_<double> *apply(const CChannelCache &channelCache,
			const CScaleSpaceCache &scaleSpaceCache,
			const CFilterCache &filterCache, Matrix_<double> *result = 0);
};

} // end namespace cv
} // end namespace rocs

#endif /* CDESCRIPTOR_H_ */
