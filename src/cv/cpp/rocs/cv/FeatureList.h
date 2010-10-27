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
//#include <rocs/cv/Feature.h>
#include <rocs/core/types.h>
#include <rocs/core/debug.h>
// std includes
#include <sstream>
#include <map>

namespace rocs {
namespace cv {


template<typename keyType, typename valueType>
class FeatureList: public std::map<keyType, valueType>
{
public:

	typedef typename std::map<keyType, valueType> Type;
	typedef typename std::map<keyType, valueType>::iterator Feature;

	FeatureList() :
		Type()
	{
		_sum = 0;
		_max = -1;
	}
	virtual ~FeatureList()
	{
	}

	/*!
	 * insert the new element (index, value)
	 * from http://stackoverflow.com/questions/97050/stdmap-insert-or-stdmap-find
	 * @param index the index where to insert
	 * @param value the new value
	 */
	void insert_(keyType index, valueType value)
	{
		typename Type::iterator lb = lower_bound(index);
		//if (lb != this->end() && !(typename Type::key_comp()(index, lb->first)))
		if (lb != this->end() && index == lb->first)
		{
			// key already exists -> update lb->second
			_sum -= lb->second; // update _sum
			lb->second = value;
		}
		else
		{
			// the key does not exist in the map ->  add it to the map
			// Use lb as a hint to insert, so it can avoid another lookup
			insert(lb, typename Type::value_type(index, value));
		}
		_sum += value; // update _sum
		if (_max < value)
			_max = value;
	}

	/*!
	 * increase the value of index
	 * @param index
	 */
	void increase_if_found(keyType index)
	{
		//		rocsDebug3("increase_if_found(%i)", index);
		double value;

		typename Type::iterator lb = lower_bound(index);
		//if (lb != this->end() && !(typename Type::key_comp()(index, lb->first)))
		if (lb != this->end() && index == lb->first)
		{
			// key already exists -> update lb->second
			++(lb->second);
			value = lb->second;
		}
		else
		{
			// the key does not exist in the map ->  add it to the map
			// Use lb as a hint to insert, so it can avoid another lookup
			insert(lb, typename Type::value_type(index, 1));
			value = 1;
		}
		_sum += 1; // update _sum
		if (_max < value)
			_max = value;
	}

	const char* iterToString(typename Type::iterator& i)
	{
		char formatString[20];
		char* ans = new char[100];
		sprintf(formatString, //
				"%s->%s", //
				rocs::core::Type<keyType>::format(), //
				rocs::core::Type<valueType>::format());
		sprintf(ans, formatString, i->first, i->second);
		return ans;
	}

	/*!
	 * Zeroes small values in the histogram.
	 * The function removes those values that divided by maximum value
	 * are smaller than min_val.
	 */
	void filter(double min_val)
	{
		//double thres = min_val * _sum;
		double thres = min_val * _max;
		rocsDebug3("filter(%f) - removing values < %f", min_val, thres);
		//		rocsDebug3("max:%f", _max);

		typename Type::iterator i = this->begin();
		while (i != this->end())
		{
			//rocsDebug3("i->second:%f", i->second);
			//if (i.value() < thres) {
			if (i->second < thres)
			{
				rocsDebug3("erasing the iterator: %s", iterToString(i));
				//_sum -= i.value(); // Decreses the classification performance. We should not do it.
				_sum -= i->second;
				//i = erase(i);
				erase(i);
				--i;
				++i;// TODO check pointer arithmetic
			}
			else
			{
				//				rocsDebug3("keeping the iterator");
				++i;
			}
		} // end loop i
	} // end filter

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
		_sum = 1;
	}

	/*!
	 * Serializes the histogram to a file in the libSVM format.
	 * \param stream
	 */
	void serialize(std::ostream &stream, bool addEndl = false)
	{
		rocsDebug3("serialize()");

		for (typename Type::const_iterator i = this->begin(); i != this->end(); ++i)
		{
			stream << i->first << ":" << i->second << " ";// << endl;
		}

		if (addEndl)
			stream << std::endl;
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

	//private:

	/*! Sum of all values before normalization. */
	valueType _sum;

	/*! Maximal value before normalization. */
	valueType _max;
};
/////

} // end namespace cv
} // end namespace rocs


#endif /* FEATURELIST_H_ */
