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
 * \file Variable.h
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_ML_VARIABLE_H_
#define _ROCS_ML_VARIABLE_H_

#include "rocs/ml/VariableClass.h"

namespace rocs {
namespace ml {


class Variable
{

	Variable(int id, std::string name, const VariableClass &varClass):
		_id(id), _name(name), _varClass(varClass)
	{}

	Variable(int id, const VariableClass &varClass):
		_id(id), _varClass(varClass)
	{}


private:

	int _id;
	std::string _name;
	VariableClass _varClass;
};



}
}

#endif /* _ROCS_ML_VARIABLE_H_ */
