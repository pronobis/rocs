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
 * \file FilterCache.cc
 *
 * Contains implementation of the FilterCache class.
 *
 * \date Sep 27, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

//#include "global.h"
#include "rocs/cv/Crfh/Filter.h"
#include "rocs/cv/Crfh/FilterCache.h"

namespace rocs {
namespace cv {

// -----------------------------------------
FilterCache::~FilterCache() {
	for (unsigned int i = 0; i < _filterList.size(); ++i)
		delete _filterList[i];
}

// -----------------------------------------
bool FilterCache::createFilter(const FilterInfo &filterInfo) {
	// Check if we don't have an identical filter in the cache
	for (unsigned int i = 0; i < _filterList.size(); ++i)
		if (_filterList[i]->getFilterInfo() == filterInfo)
			return true;

	// Create a new filter
	Filter *filter = Filter::createFilter(filterInfo);
	if (filter) {
		_filterList.push_back(filter);
		return true;
	} else
		return false;
}

// -----------------------------------------
Matrix_<double> *FilterCache::applyFilter(const FilterInfo &filterInfo,
		const Matrix_<double> &input, Matrix_<double> *result /* =0 */) const {
	rocsDebug3("CFilterCache::applyFilter(%i, input:'%s')", filterInfo.getFilterType(), input.infoString().c_str());

	/* Find the filter */
	Filter *filter = 0;
	for (unsigned int i = 0; (i < _filterList.size()) && (!filter); ++i) {
		if (_filterList[i]->getFilterInfo() == filterInfo)
			filter = _filterList[i];
	}

	/* Filter not found? */
	if (!filter) {
		rocsDebug1("ERROR: filter not found");
		return result;
	}
	else {
		rocsDebug3("Filter found:%i", filter->getFilterInfo().getFilterType());
	}

	/* Apply the filter */
	//debugPrintf_lvl3("result:%s", result->infoString().c_str());
	result = filter->apply(input, result);

	return result;
}

} // end namespace cv
} // end namespace rocs
