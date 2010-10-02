/*
 * CFilterCache.h
 *
 *  Created on: Sep 27, 2010
 *      Author: arnaud
 */

#ifndef CFILTERCACHE_H_
#define CFILTERCACHE_H_

#include <vector>

namespace rocs {
namespace cv {

/**
 * \file CFilterCache.h
 * \author Andrzej Pronobis
 *
 * Contains declaration of the CFilterCache class.
 */

#ifndef _CFILTERCACHE_H_
#define _CFILTERCACHE_H_

//#include <QtCore/QList>

class CFilter;
class CFilterInfo;
template<typename _T> class Matrix_;

/**
 * Class storing a cache of filters.
 */
class CFilterCache {

public:

	/** Default constructor. */
	inline CFilterCache() {
	}
	;

	/** Destructor. Deletes all the filters. */
	~CFilterCache();

public:

	/** Creates a new filter. If an identical filter already exists
	 a new one will not be created. */
	bool createFilter(const CFilterInfo &filterInfo);

	/** Applies a filter identified by the filterInfo to the given matrix. */
	Matrix_<double> *applyFilter(const CFilterInfo &filterInfo, const Matrix_<
			double> &input, Matrix_<double> *result = 0) const;

private:

	/** List storing pointers to filters. */
	std::vector<CFilter *> _filterList;

};

#endif

} // end namespace cv
} // end namespace rocs

#endif /* CFILTERCACHE_H_ */
