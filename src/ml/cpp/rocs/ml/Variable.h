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



struct VariableData
{
	VariableData(int id_, std::string name_, const VariableClass &varClass_):
		id(id_), name(name_), varClass(varClass_)
	{}

	int id;
	std::string name;
	VariableClass varClass;
};


class Variable: public core::ShallowCopyable<VariableData>
{
public:

	Variable(int id, std::string name, const VariableClass &varClass):
		SC(new VariableData(id, name, varClass))
	{}

	Variable(int id, const VariableClass &varClass):
		SC(new VariableData(id, std::string(), varClass))
	{}


	std::string name() const
	{ return data()->name; }

	int id() const
	{ return data()->id; }

	const VariableClass &variableClass()
	{ return data()->varClass; }

};



}
}

#endif /* _ROCS_ML_VARIABLE_H_ */
