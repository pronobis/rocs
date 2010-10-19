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
 * \file FeatureList.h
 *
 * TODO description
 *
 * \date Oct 19, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef FEATURELIST_H_
#define FEATURELIST_H_

// rocs includes
#include <rocs/cv/Feature.h>
#include <rocs/core/debug.h>
// std includes
#include <sstream>

template<typename keyType, typename valueType>
class FeatureList: public std::map<keyType, valueType>
{
public:

	typedef typename std::map<keyType, valueType> Type;
	typedef typename std::map<keyType, valueType>::iterator Feature;

	FeatureList() :
		Type()
	{
	}
	virtual ~FeatureList()
	{
	}

	/*!
	 * Zeroes small values in the histogram.
	 * The function removes those values that divided by maximum value
	 * are smaller than min_val.
	 */
	void filter(double min_val)
	{
		rocsDebug3("filter(%f)", min_val);
		double tmp = min_val * _sum;

		typename Type::iterator i = this->begin();
		while (i != this->end())
		{
			rocsDebug3("i->second:%f", i->second);
			//if (i.value() < tmp) {
			if (i->second < tmp)
			{
				//_sum -= i.value(); // Decreses the classification performance. We should not do it.
				//i = erase(i);
				erase(i);
				--i; // TODO check pointer arithmetic
			}
			else
				++i;
		}
	}

	/*!
	 * Normalizes the histogram - divides each bin by the sum of all.
	 */
	void normalize()
	{
		rocsDebug3("normalize() - sum:%f", _sum);
		for (typename Type::iterator i = this->begin(); i != this->end(); ++i)
		{
			//i.value() /= _sum; TODO check this
			//debugPrintf_lvl3("Elem:%f", i->second);
			i->second /= _sum;
		}
	}

	/*!
	 * Serializes the histogram to a file in the libSVM format.
	 * \param stream
	 */
	void serialize(std::ostream &stream)
	{
		rocsDebug3("serialize()");

		for (typename Type::const_iterator i = this->begin(); i != this->end(); ++i)
		{
			stream << i->first << ":" << i->second << " ";// << endl;
		}
	}

	/*!
	 * \return a libSVM compatible sparse vector containing the histogram.
	 */
	Feature *getLibSvmVector()
	{
		rocsDebug3("getLibSvmVector()");

		//Feature *vector = aMalloc<Feature> (size() + 1);
		Feature *vector = new Feature[this->size() + 1];

		int nr = 0;
		for (typename Type::const_iterator i = this->begin(); i != this->end(); ++i, ++nr)
		{
			vector[nr].first = i->first;//key();
			vector[nr].second = i->second;//.value();
		}

		vector[this->size()].first = -1;
		vector[this->size()].second = 0.0;

		return vector;
	}

private:

	/*! Sum of all values before normalization. */
	valueType _sum;

	/*! Maximal value before normalization. */
	valueType _max;
};
/////

#endif /* FEATURELIST_H_ */
