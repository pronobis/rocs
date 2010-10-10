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
 * \file FilterCache.h
 *
 * \date Sep 27, 2010
 * \author Andrzej Pronobis
 *
 * Contains declaration of the FilterCache class.
 */

#ifndef CFILTERCACHE_H_
#define CFILTERCACHE_H_

#include <vector>

namespace rocs {
namespace cv {

//#include <QtCore/QList>

class Filter;
class FilterInfo;
template<typename _T> class Matrix_;

/*!
 * Class storing a cache of filters.
 */
class FilterCache {

public:

	/*! Default constructor. */
	inline FilterCache() {
	}
	;

	/*! Destructor. Deletes all the filters. */
	~FilterCache();

public:

	/*! Creates a new filter. If an identical filter already exists
	 a new one will not be created. */
	bool createFilter(const FilterInfo &filterInfo);

	/*! Applies a filter identified by the filterInfo to the given matrix. */
	Matrix_<double> *applyFilter(const FilterInfo &filterInfo, const Matrix_<
			double> &input, Matrix_<double> *result = 0) const;

private:

	/*! List storing pointers to filters. */
	std::vector<Filter *> _filterList;

};

} // end namespace cv
} // end namespace rocs

#endif /* CFILTERCACHE_H_ */
