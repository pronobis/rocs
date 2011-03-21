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
 * \file VariableClass.cc
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */

#include "rocs/ml/VariableClass.h"
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

namespace rocs {
namespace ml {


// ---------------------------------------------
void VariableClass::setValue(size_t state, std::string &value)
{
	switch(data()->type)
	{
	case VVT_STRING:
		stringData()->values[state] = value;
		return;
	case VVT_INT:
		try {
			intData()->values[state] = lexical_cast<int>(value);
		} catch(bad_lexical_cast &) {
			rocsConversionException("Cannot convert the string '%s' to integer.", value.c_str());
		}
		return;
	default:
		rocsTypeException("Variable class does allow to store values.");
	}
}


// ---------------------------------------------
void VariableClass::setValue(size_t state, int value)
{
	switch(data()->type)
	{
	case VVT_INT:
		intData()->values[state] = value;
		return;
	case VVT_STRING:
		stringData()->values[state] = lexical_cast<string>(value);
		return;
	default:
		rocsTypeException("Variable class does allow to store values.");
	}
}


// ---------------------------------------------
int VariableClass::getIntValue(size_t state) const
{
	switch(data()->type)
	{
	case VVT_INT:
		return intData()->values[state];
	case VVT_STRING:
		try {
			return lexical_cast<int>(stringData()->values[state]);
		} catch(bad_lexical_cast &) {
			rocsConversionException("Cannot convert the variable value '%s' to integer.", stringData()->values[state].c_str());
		}
	case VVT_BOOL:
		return boolData()->values[state]?1:0;
	default:
		rocsTypeException("Variable class does not store values.");
	}
}


// ---------------------------------------------
std::string VariableClass::getStringValue(size_t state) const
{
	switch(data()->type)
	{
	case VVT_STRING:
		return stringData()->values[state];
	case VVT_INT:
		return lexical_cast<string>(intData()->values[state]);
	case VVT_BOOL:
		return (boolData()->values[state]?"true":"false");
	default:
		rocsTypeException("Variable class does not store values.");
	}
}


// ---------------------------------------------
bool VariableClass::getBoolValue(size_t state) const
{
	switch(data()->type)
	{
	case VVT_BOOL:
		return boolData()->values[state];
	case VVT_STRING:
		if (stringData()->values[state] == "true")
			return true;
		else if (stringData()->values[state] == "false")
			return false;
		else
			rocsConversionException("Cannot convert the variable value '%s' to boolean.", stringData()->values[state].c_str());
	case VVT_INT:
		return intData()->values[state];
	default:
		rocsTypeException("Variable class does not store values.");
	}
}


}
}

