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
 * \file Crfh.h
 *
 * Contains declaration of the Crfh class.
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef CCRFH_H_
#define CCRFH_H_

// STD includes
#include <vector>
using std::vector;
#include <sstream>
using std::ostream;
#include <map>
using std::map;

// type declaration
typedef std::map<int, double> MapType;

namespace rocs {

namespace math {
template<typename _T> class Matrix_;
}

namespace cv {

class DescriptorList;

/*!
 * Node of a libsvm sparse vector.
 */
//struct CSvmNode {
//	int index;
//	double value;
//};
typedef std::pair<int, double> CSvmNode;

/*!
 * the representation of a Crfh feature
 */
class Crfh: public MapType {

public:

	/*! Constructor. Creates a histogram from a set of
	 outputs of descriptors. */
	Crfh(vector<math::Matrix_<double> *> outputs, const DescriptorList &descrList,
			int skipBorderPixels);

	/*! Zeroes small values in the histogram. The function removes those
	 values that divided by maximum value are smaller than min_val. */
	void filter(double min_val);

	/*! Normalizes the histogram - divides each bin by the sum of all. */
	void normalize();

	/*! Serializes the histogram to a file in the libSVM format. */
	void serialize(ostream &stream);

	/*! Returns a libSVM compatible sparse vector containing the histogram. */
	CSvmNode *getLibSvmVector();

private:

	/*! Sum of all values before normalization. */
	double _sum;

	/*! Maximal value before normalization. */
	double _max;

};

} // end namespace cv
} // end namespace rocs

#endif /* CCRFH_H_ */
