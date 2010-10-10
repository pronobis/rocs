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
 * \file Descriptor.cc
 *
 * \date Sep 27, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#include "rocs/cv/Crfh/Filter.h"
#include "rocs/cv/Crfh/FilterCache.h"
#include "rocs/cv/Crfh/ChannelCache.h"
#include "rocs/cv/Crfh/ScaleSpaceCache.h"
#include "rocs/cv/Crfh/Descriptor.h"


namespace rocs {
namespace cv {

// -----------------------------------------
Descriptor *Descriptor::createDescriptor(DescriptorType descriptorType,
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
Descriptor *Descriptor::createDescriptor(string descriptorName,
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
void CLDescriptor::createRequiredFilters(FilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	filterCache.createFilter(gfi);
}

// -----------------------------------------
void CLDescriptor::createRequiredChannels(ChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLDescriptor::createRequiredScales(ScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLDescriptor::apply(const ChannelCache &channelCache,
		const ScaleSpaceCache &scaleSpaceCache,
		const FilterCache &filterCache, Matrix_<double> *result) {
	const Matrix_<double> *scaleSpaceSample = scaleSpaceCache.getScaleSpaceSample(CT_L,
			_scale);
	//result = scaleSpaceSample->getDeepCopy(result);
	scaleSpaceSample->copyTo(*result);
	// TODO check it works
	return result;
}

// -----------------------------------------
void CLxxDescriptor::createRequiredFilters(FilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(2, 0);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLxxDescriptor::createRequiredChannels(ChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLxxDescriptor::createRequiredScales(ScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLxxDescriptor::apply(const ChannelCache &channelCache,
		const ScaleSpaceCache &scaleSpaceCache,
		const FilterCache &filterCache, Matrix_<double> *result) {
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
void CLxDescriptor::createRequiredFilters(FilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(1, 0);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLxDescriptor::createRequiredChannels(ChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLxDescriptor::createRequiredScales(ScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLxDescriptor::apply(const ChannelCache &channelCache,
		const ScaleSpaceCache &scaleSpaceCache,
		const FilterCache &filterCache, Matrix_<double> *result) {
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
void CLyDescriptor::createRequiredFilters(FilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(0, 1);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLyDescriptor::createRequiredChannels(ChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLyDescriptor::createRequiredScales(ScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLyDescriptor::apply(const ChannelCache &channelCache,
		const ScaleSpaceCache &scaleSpaceCache,
		const FilterCache &filterCache, Matrix_<double> *result) {
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
void CLyyDescriptor::createRequiredFilters(FilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(0, 2);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLyyDescriptor::createRequiredChannels(ChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLyyDescriptor::createRequiredScales(ScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLyyDescriptor::apply(const ChannelCache &channelCache,
		const ScaleSpaceCache &scaleSpaceCache,
		const FilterCache &filterCache, Matrix_<double> *result) {
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
void CLxyDescriptor::createRequiredFilters(FilterCache &filterCache) {
	CGaussianFilterInfo gfi(_scale);
	CCartesianFilterInfo cfi(1, 1);

	filterCache.createFilter(gfi);
	filterCache.createFilter(cfi);
}

// -----------------------------------------
void CLxyDescriptor::createRequiredChannels(ChannelCache &channelCache) {
	channelCache.createChannel(CT_L);
}

// -----------------------------------------
void CLxyDescriptor::createRequiredScales(ScaleSpaceCache &scaleSpaceCache) {
	scaleSpaceCache.createScaleSpaceSample(CT_L, _scale);
}

// -----------------------------------------
Matrix_<double> *CLxyDescriptor::apply(const ChannelCache &channelCache,
		const ScaleSpaceCache &scaleSpaceCache,
		const FilterCache &filterCache, Matrix_<double> *result) {
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
