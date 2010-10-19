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

template<typename keyType, typename valueType>
class FeatureList : std::map<keyType, valueType>
{
public:
	FeatureList();
	virtual ~FeatureList();
};

#endif /* FEATURELIST_H_ */
