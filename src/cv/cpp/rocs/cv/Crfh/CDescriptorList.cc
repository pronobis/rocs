/*
 * CDescriptorList.cc
 *
 *  Created on: Sep 28, 2010
 *      Author: arnaud
 */

#include "rocs/math/Matrix_.h"
#include "rocs/cv/Crfh/CDescriptorList.h"

namespace rocs {
namespace cv {

/**
 * \file CDescriptorList.cpp
 * \author Andrzej Pronobis
 *
 * Contains implementation of the CDescriptorList class.
 */


// -----------------------------------------
CDescriptorList::~CDescriptorList() {
	for (unsigned int i = 0; i < size(); ++i)
		delete at(i);
}

// -----------------------------------------
void CDescriptorList::addDescriptor(DescriptorType descriptorType,
		double scale, int bins) {
	push_back(CDescriptor::createDescriptor(descriptorType, scale, bins));
}

// -----------------------------------------
void CDescriptorList::addDescriptor(string name, double scale, int bins) {
	push_back(CDescriptor::createDescriptor(name, scale, bins));
}

// -----------------------------------------
void CDescriptorList::createAllRequiredFilters(CFilterCache &filterCache) const {
	for (unsigned int i = 0; i < size(); ++i)
		at(i)->createRequiredFilters(filterCache);
}

// -----------------------------------------
void CDescriptorList::createAllRequiredScales(CScaleSpaceCache &scaleSpaceCache) const {
	for (unsigned int i = 0; i < size(); ++i)
		at(i)->createRequiredScales(scaleSpaceCache);
}

// -----------------------------------------
void CDescriptorList::createAllRequiredChannels(CChannelCache &channelCache) const {
	for (unsigned int i = 0; i < size(); ++i)
		at(i)->createRequiredChannels(channelCache);
}

// -----------------------------------------
vector<Matrix_<double> *> CDescriptorList::applyAll(const CChannelCache &channelCache,
		const CScaleSpaceCache &scaleSpaceCache,
		const CFilterCache &filterCache) const {
	vector<Matrix_<double> *> list;

	for (unsigned int i = 0; i < size(); ++i)
		list.push_back(at(i)->apply(channelCache, scaleSpaceCache, filterCache));

	return list;
}

} // end namespace cv
} // end namespace rocs
