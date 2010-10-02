/*
 * CDescriptor.cc
 *
 *  Created on: Sep 27, 2010
 *      Author: arnaud
 */

#include "rocs/cv/Crfh/CFilter.h"
#include "rocs/cv/Crfh/CFilterCache.h"
#include "rocs/cv/Crfh/CChannelCache.h"
#include "rocs/cv/Crfh/CScaleSpaceCache.h"
#include "rocs/cv/Crfh/CDescriptor.h"


namespace rocs {
namespace cv {

// -----------------------------------------
CDescriptor *CDescriptor::createDescriptor(DescriptorType descriptorType,
		double scale, int bins) {
	switch (descriptorType) {
	case DT_L:
		return new CLDescriptor(scale, bins);
	case DT_Lx:
		return new CLxDescriptor(scale, bins);
	case DT_Lxx:
		return new CLxxDescriptor(scale, bins);
	case DT_Ly:
		return new CLyDescriptor(scale, bins);
	case DT_Lyy:
		return new CLyyDescriptor(scale, bins);
	case DT_Lxy:
		return new CLxyDescriptor(scale, bins);

	default:
		return 0;
	}
}

// -----------------------------------------
CDescriptor *CDescriptor::createDescriptor(string descriptorName,
		double scale, int bins) {
	if (descriptorName == "L")
		return new CLDescriptor(scale, bins);
	else if (descriptorName == "Lx")
		return new CLxDescriptor(scale, bins);
	else if (descriptorName == "Lxx")
		return new CLxxDescriptor(scale, bins);
	else if (descriptorName == "Ly")
		return new CLyDescriptor(scale, bins);
	else if (descriptorName == "Lyy")
		return new CLyyDescriptor(scale, bins);
	else if (descriptorName == "Lxy")
		return new CLxyDescriptor(scale, bins);
	else
		return 0;
}

// -----------------------------------------
void CLDescriptor::createRequiredFilters(CFilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	filterCache.createFilter(gfi);
}

// -----------------------------------------
void CLDescriptor::createRequiredChannels(CChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLDescriptor::createRequiredScales(CScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLDescriptor::apply(const CChannelCache &channelCache,
		const CScaleSpaceCache &scaleSpaceCache,
		const CFilterCache &filterCache, Matrix_<double> *result) {
	const Matrix_<double> *scaleSpaceSample = scaleSpaceCache.getScaleSpaceSample(CT_L,
			_scale);
	//result = scaleSpaceSample->getDeepCopy(result);
	scaleSpaceSample->copyTo(*result);
	// TODO check it works
	return result;
}

// -----------------------------------------
void CLxxDescriptor::createRequiredFilters(CFilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(2, 0);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLxxDescriptor::createRequiredChannels(CChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLxxDescriptor::createRequiredScales(CScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLxxDescriptor::apply(const CChannelCache &channelCache,
		const CScaleSpaceCache &scaleSpaceCache,
		const CFilterCache &filterCache, Matrix_<double> *result) {
	// Get scale space sample
	const Matrix_<double> *scaleSpaceSample = scaleSpaceCache.getScaleSpaceSample(CT_L,
			_scale);

	// Filter with second-derivative filter
	CCartesianFilterInfo cfi(2, 0);
	result = filterCache.applyFilter(cfi, *scaleSpaceSample, result);

	// Normalize
	double factor = _scale;
	//(*result) *= factor; // scale^(2/2)=sqrt(scale)^2 = scale
	(*(result->asOpenCvMat())) *= factor; // scale^(2/2)=sqrt(scale)^2 = scale

	// Return the result
	return result;
}

// -----------------------------------------
void CLxDescriptor::createRequiredFilters(CFilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(1, 0);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLxDescriptor::createRequiredChannels(CChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLxDescriptor::createRequiredScales(CScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLxDescriptor::apply(const CChannelCache &channelCache,
		const CScaleSpaceCache &scaleSpaceCache,
		const CFilterCache &filterCache, Matrix_<double> *result) {
	// Get scale space sample
	const Matrix_<double> *scaleSpaceSample = scaleSpaceCache.getScaleSpaceSample(CT_L,
			_scale);

	// Filter with second-derivative filter
	CCartesianFilterInfo cfi(1, 0);
	result = filterCache.applyFilter(cfi, *scaleSpaceSample, result);

	// Normalize
	double factor = sqrt(_scale);
	(*(result->asOpenCvMat())) *= factor; // scale^(1/2)=sqrt(scale)

	// Return the result
	return result;
}

// -----------------------------------------
void CLyDescriptor::createRequiredFilters(CFilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(0, 1);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLyDescriptor::createRequiredChannels(CChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLyDescriptor::createRequiredScales(CScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLyDescriptor::apply(const CChannelCache &channelCache,
		const CScaleSpaceCache &scaleSpaceCache,
		const CFilterCache &filterCache, Matrix_<double> *result) {
	// Get scale space sample
	const Matrix_<double> *scaleSpaceSample = scaleSpaceCache.getScaleSpaceSample(CT_L,
			_scale);

	// Filter with second-derivative filter
	CCartesianFilterInfo cfi(0, 1);
	result = filterCache.applyFilter(cfi, *scaleSpaceSample, result);

	// Normalize
	double factor = sqrt(_scale);
	(*(result->asOpenCvMat())) *= factor; // scale^(1/2)=sqrt(scale)

	// Return the result
	return result;
}

// -----------------------------------------
void CLyyDescriptor::createRequiredFilters(CFilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(0, 2);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLyyDescriptor::createRequiredChannels(CChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLyyDescriptor::createRequiredScales(CScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLyyDescriptor::apply(const CChannelCache &channelCache,
		const CScaleSpaceCache &scaleSpaceCache,
		const CFilterCache &filterCache, Matrix_<double> *result) {
	// Get scale space sample
	const Matrix_<double> *scaleSpaceSample = scaleSpaceCache.getScaleSpaceSample(CT_L,
			_scale);

	// Filter with second-derivative filter
	CCartesianFilterInfo cfi(0, 2);
	result = filterCache.applyFilter(cfi, *scaleSpaceSample, result);

	// Normalize
	double factor = _scale;
	(*(result->asOpenCvMat())) *= factor; // scale^(1/2)=sqrt(scale)

	// Return the result
	return result;
}

// -----------------------------------------
void CLxyDescriptor::createRequiredFilters(CFilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(1, 1);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLxyDescriptor::createRequiredChannels(CChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLxyDescriptor::createRequiredScales(CScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLxyDescriptor::apply(const CChannelCache &channelCache,
		const CScaleSpaceCache &scaleSpaceCache,
		const CFilterCache &filterCache, Matrix_<double> *result) {
	// Get scale space sample
	const Matrix_<double> *scaleSpaceSample = scaleSpaceCache.getScaleSpaceSample(CT_L,
			_scale);

	// Filter with second-derivative filter
	CCartesianFilterInfo cfi(1, 1);
	result = filterCache.applyFilter(cfi, *scaleSpaceSample, result);

	// Normalize
	double factor = _scale;
	(*(result->asOpenCvMat())) *= factor; // scale^(1/2)=sqrt(scale)

	// Return the result
	return result;
}

} // end namespace cv
} // end namespace rocs
