/*!
 * CFilterCache.cc
 *
 * Contains implementation of the CFilterCache class.
 *
 *  Created on: Sep 27, 2010
 *      Author: Andrzej Pronobis, arnaud
 */

//#include "global.h"
#include "rocs/cv/Crfh/CFilter.h"
#include "rocs/cv/Crfh/CFilterCache.h"

namespace rocs {
namespace cv {

// -----------------------------------------
CFilterCache::~CFilterCache() {
	for (unsigned int i = 0; i < _filterList.size(); ++i)
		delete _filterList[i];
}

// -----------------------------------------
bool CFilterCache::createFilter(const CFilterInfo &filterInfo) {
	// Check if we don't have an identical filter in the cache
	for (unsigned int i = 0; i < _filterList.size(); ++i)
		if (_filterList[i]->getFilterInfo() == filterInfo)
			return true;

	// Create a new filter
	CFilter *filter = CFilter::createFilter(filterInfo);
	if (filter) {
		_filterList.push_back(filter);
		return true;
	} else
		return false;
}

// -----------------------------------------
Matrix_<double> *CFilterCache::applyFilter(const CFilterInfo &filterInfo,
		const Matrix_<double> &input, Matrix_<double> *result /* =0 */) const {
	debug3("CFilterCache::applyFilter(%i, input:'%s')", filterInfo.getFilterType(), input.infoString().c_str());

	/* Find the filter */
	CFilter *filter = 0;
	for (unsigned int i = 0; (i < _filterList.size()) && (!filter); ++i) {
		if (_filterList[i]->getFilterInfo() == filterInfo)
			filter = _filterList[i];
	}

	/* Filter not found? */
	if (!filter) {
		debug1("ERROR: filter not found");
		return result;
	}
	else {
		debug3("Filter found:%i", filter->getFilterInfo().getFilterType());
	}

	/* Apply the filter */
	//debugPrintf_lvl3("result:%s", result->infoString().c_str());
	result = filter->apply(input, result);

	return result;
}

} // end namespace cv
} // end namespace rocs
