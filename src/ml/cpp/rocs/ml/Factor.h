// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2011  Andrzej Pronobis
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
 * \file Factor.h
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_ML_FACTOR_H_
#define _ROCS_ML_FACTOR_H_

#include "rocs/ml/FactorClass.h"

namespace rocs {
namespace ml {



class Factor
{

	Factor(int id, std::string name, const FactorClass &factorClass):
		_id(id), _name(name), _factorClass(factorClass)
	{}

	Factor(int id, const FactorClass &factorClass):
		_id(id), _factorClass(factorClass)
	{}

	Factor(int id, std::string name, const FactorClass &factorClass, const cv::Mat &potentials):
		_id(id), _name(name), _factorClass(factorClass), _potentials(potentials)
	{}

	Factor(int id, const FactorClass &factorClass, const cv::Mat &potentials):
		_id(id), _factorClass(factorClass), _potentials(potentials)
	{}


private:

	int _id;
	std::string _name;
	FactorClass _factorClass;
	cv::Mat _potentials;
};



}
}


#endif /* _ROCS_ML_FACTOR_H_ */
