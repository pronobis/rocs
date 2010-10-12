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
 * \file Crfh.cc
 *
 * Contains implementation of the Crfh class.
 *
 * \date Sep 27, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#include <limits>

#include "rocs/cv/Crfh/DescriptorList.h"
#include "rocs/math/Matrix_.h"

#include "rocs/cv/Crfh/Crfh.h"

namespace rocs {
namespace cv {

using rocs::math::Matrix_;

Crfh::Crfh(vector<Matrix_<double> *> outputs,
		const DescriptorList &descrList, int skipBorderPixels) {
	// Check whether the descriptor list matches the output list
	if (outputs.size() != descrList.size()) {
		rocsError("The size of the descriptor list does not match the size of the outputs list. ");
		return;
	}

	// Read all the necessary information and store it in the vectors
	vector<math::Matrix_<double> *> dataVect;
	vector<double> minVect;
	vector<double> maxVect;
	vector<int> binsVect;

	int rows = outputs[0]->nbRows();
	int cols = outputs[0]->nbCols();
	int ndims = outputs.size();

	for (int i = 0; i < ndims; ++i) {
		dataVect.push_back(outputs[i]);
		binsVect.push_back(descrList[i]->getBins());
		minVect.push_back(descrList[i]->getMin());
		maxVect.push_back(descrList[i]->getMax());
		if ((rows != outputs[i]->nbRows()) || (cols != outputs[i]->nbCols())) {
			rocsError("The filter outputs have different dimensions. ");
			return;
		}
	}

	// Direct access to vectors' arrays
	Matrix_<double> **data = dataVect.data();
	double *min = minVect.data();
	double *max = maxVect.data();
	int *bins = binsVect.data();

	// Calculate scaling factors
	vector<double> factorsVect;
	for (int i = 0; i < ndims; ++i) {
		factorsVect.push_back(((double) bins[i]
				- std::numeric_limits<double>::epsilon()) / (max[i] - min[i]));
	}
	double *factors = factorsVect.data();

	// Create the histogram
	_max = -1;
	for (int i = rows - 1 - skipBorderPixels; i >= skipBorderPixels; --i) // Iterate through all pixels
		for (int j = cols - 1 - skipBorderPixels; j >= skipBorderPixels; --j) // without borders
		{
			// Number of bin for dimension k:
			// (int)((data[k][i]-min[k])*factors[k])

			int k = ndims - 1;
			long index = (int) ((data[k]->get(i, j) - min[k]) * factors[k]);
			for (k = ndims - 2; k >= 0; --k)
				index = index * bins[k] + (int) ((data[k]->get(i, j) - min[k])
						* factors[k]);

			/* insert the new element (index, tmp)
			 * from http://stackoverflow.com/questions/97050/stdmap-insert-or-stdmap-find
			 * */
			//			double new_value=value(index)+1;
			//			      if (new_value>_max) _max=new_value;
			//			      insert(index, new_value);
			//debugPrintf_lvl3("incrementing (%li)", index);
			MapType::iterator lb = lower_bound(index);
			if (lb != end() && !(key_comp()(index, lb->first))) {
				// key already exists -> update lb->second
				++(lb->second);
				if (_max < lb->second)
					_max = lb->second;
			} else {
				// the key does not exist in the map ->  add it to the map
				// Use lb as a hint to insert, so it can avoid another lookup
				insert(lb, MapType::value_type(index, 1));
			}

		}

	// Store sum of all bins
	_sum = (rows - 2 * skipBorderPixels) * (cols - 2 * skipBorderPixels);
}

// -----------------------------------------
void Crfh::serialize(ostream &stream) {
	rocsDebug3("serialize()");

	for (map<int, double>::const_iterator i = begin(); i != end(); ++i) {
		//stream << i.key() << ":" << i.value() << " ";
		stream << i->first << ":" << i->second << " ";// << endl;
	}
}

// -----------------------------------------
void Crfh::filter(double min_val) {
	rocsDebug3("filter(%f)", min_val);

	double tmp = min_val * _sum;

	map<int, double>::iterator i = begin();
	while (i != end()) {
		//if (i.value() < tmp) {
		if (i->first < tmp) {
			//_sum -= i.value(); // Decreses the classification performance. We should not do it.
			//i = erase(i);
			erase(i);
			--i; // TODO check pointer arithmetic
		} else
			++i;
	}
}

// -----------------------------------------
void Crfh::normalize() {
	rocsDebug3("normalize() - sum:%f", _sum);

	for (map<int, double>::iterator i = begin(); i != end(); ++i) {
		//i.value() /= _sum; TODO check this
		//debugPrintf_lvl3("Elem:%f", i->second);
		i->second /= _sum;
	}
}

// -----------------------------------------
CSvmNode *Crfh::getLibSvmVector() {
	rocsDebug3("getLibSvmVector()");

	//CSvmNode *vector = aMalloc<CSvmNode> (size() + 1);
	CSvmNode *vector = new CSvmNode[size() + 1];

	int nr = 0;
	for (map<int, double>::const_iterator i = begin(); i != end(); ++i, ++nr) {
		vector[nr].first = i->first;//key();
		vector[nr].second = i->second;//.value();
	}

	vector[size()].first = -1;
	vector[size()].second = 0.0;

	return vector;
}

} // end namespace cv
} // end namespace rocs
