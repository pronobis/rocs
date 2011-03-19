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
 * \file DescriptorList.cc
 *
 * Contains implementation of the DescriptorList class.
 *
 * \date Sep 28, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#include "rocs/math/Matrix_.h"
#include "rocs/cv/Crfh/DescriptorList.h"

namespace rocs
{
namespace cv
{

// -----------------------------------------
DescriptorList::~DescriptorList()
{
	for (unsigned int i = 0; i < size(); ++i)
		delete at(i);
}

// -----------------------------------------
void DescriptorList::addDescriptor(DescriptorType descriptorType,
		double scale, int bins)
{
	push_back(Descriptor::createDescriptor(descriptorType, scale, bins));
}

// -----------------------------------------
void DescriptorList::addDescriptor(string name, double scale, int bins)
{
	push_back(Descriptor::createDescriptor(name, scale, bins));
}

// -----------------------------------------
void DescriptorList::createAllRequiredFilters(FilterCache &filterCache) const
{
	for (unsigned int i = 0; i < size(); ++i)
		at(i)->createRequiredFilters(filterCache);
}

// -----------------------------------------
void DescriptorList::createAllRequiredScales(ScaleSpaceCache &scaleSpaceCache) const
{
	for (unsigned int i = 0; i < size(); ++i)
		at(i)->createRequiredScales(scaleSpaceCache);
}

// -----------------------------------------
void DescriptorList::createAllRequiredChannels(ChannelCache &channelCache) const
{
	for (unsigned int i = 0; i < size(); ++i)
		at(i)->createRequiredChannels(channelCache);
}

// -----------------------------------------
vector<math::Matrix_<double> *> DescriptorList::applyAll(
		const ChannelCache &channelCache,
		const ScaleSpaceCache &scaleSpaceCache,
		const FilterCache &filterCache) const
{
	vector<math::Matrix_<double> *> list;

	for (unsigned int i = 0; i < size(); ++i)
		list.push_back(at(i)->apply(channelCache, scaleSpaceCache, filterCache));

	return list;
}

} // end namespace cv
} // end namespace rocs
