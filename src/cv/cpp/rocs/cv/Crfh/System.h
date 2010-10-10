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
 * \file System.h
 *
 * \date Sep 28, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef CSYSTEM_H_
#define CSYSTEM_H_

#include "rocs/cv/Crfh/FilterCache.h"
#include "rocs/cv/Crfh/DescriptorList.h"

#include <string>
#include <vector>
using std::string;

namespace rocs {

namespace math {
template<typename _T> class Matrix_;
}

namespace cv {

class Img;
class Crfh;

/*!
 * Main class defining a system and managing the
 * histogram extraction process.
 */
class System {

public:

	/*! Constructor. Initializes the system (creates descriptors
	 and filters). */
	System(string sysDef);

public:

	/*! Computes outputs of all the descriptors. */
	vector<math::Matrix_<double>*> computeDescriptorOutputs(const Img &image) const;

	/*! Computes the histogram for a given image. */
	Crfh *computeHistogram(const Img &image, int skipBorderPixels) const;

private:

	/*! List of descriptors to be computed. */
	DescriptorList _descriptorList;

	/*! Filter cache. */
	FilterCache _filterCache;
};

} // end namespace cv
} // end namespace rocs

#endif /* CSYSTEM_H_ */
