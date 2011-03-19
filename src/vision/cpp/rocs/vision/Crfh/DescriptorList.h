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
 * \file DescriptorList.h
 *
 * \date Sep 28, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef CDESCRIPTORLIST_H_
#define CDESCRIPTORLIST_H_

#include "rocs/cv/Crfh/Descriptor.h"
#include <vector>
using std::vector;

//namespace math {
//template<typename _T> class Matrix_;
//}

namespace rocs
{

namespace math
{
template<typename _T> class Matrix_;
}

namespace cv
{

class DescriptorList: public vector<Descriptor *>
{

public:

	/*! Destructor. Deletes all the descriptors. */
	~DescriptorList();

public:

	/*! Adds a new descriptor to the list. The descriptor is characterized
	 by its type, scale, and number of bins. */
	void addDescriptor(DescriptorType descriptorType, double scale, int bins);

	/*! Adds a new descriptor to the list. The descriptors is characterized
	 by its name, scale, and number of bins. */
	void addDescriptor(string name, double scale, int bins);

public:

	/*! Creates filters requierd by all descriptors. */
	void createAllRequiredFilters(FilterCache &filterCache) const;

	/*! Creates samples of the scale-space requierd by all descriptors. */
	void createAllRequiredScales(ScaleSpaceCache &scaleSpaceCache) const;

	/*! Creates channels required by all descriptors. */
	void createAllRequiredChannels(ChannelCache &channelCache) const;

	/*! Applies all the descriptors in the list and returns a list of
	 pointers to the output matrices. */
	vector<math::Matrix_<double>*> applyAll(const ChannelCache &channelCache,
			const ScaleSpaceCache &scaleSpaceCache,
			const FilterCache &filterCache) const;

};

} // end namespace cv
} // end namespace rocs

#endif /* CDESCRIPTORLIST_H_ */
