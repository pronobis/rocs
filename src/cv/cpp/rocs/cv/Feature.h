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
 * \file Feature.h
 *
 * a general interface for the description of a feature
 * It is just an extension of
 *
 * \date Oct 19, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef FEATURE_H_
#define FEATURE_H_

#include <map>
#include <iterator>

/*
 * this is what we would like to do
 */
//template<typename keyType, typename valueType>
//typedef std::map<keyType, valueType>::iterator Feature;

/*
 * if you specify explicitely the types, can use a typedef
 */
//typedef std::map<int, double>::iterator Feature;

/*
 * trick
 */
//template<typename keyType, typename valueType>
//struct Feature
//{
//	typedef std::map<keyType, valueType> Type;
//};

/*
 * full specification
 */
//template<typename keyType, typename valueType>
//class Feature : public std::map<keyType, valueType>::iterator
//{
//public:
//	/*! constructor */
//	Feature()
//	{
//	}
//	/*! destructor */
//	virtual ~Feature()
//	{
//	}
//};

#endif /* FEATURE_H_ */
