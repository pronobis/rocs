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
 * \file VariableClass.h
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_ML_VARIABLECLASS_H_
#define _ROCS_ML_VARIABLECLASS_H_

#include "rocs/core/ShallowCopyable.h"
#include "rocs/core/error.h"
#include <string>
#include <vector>

namespace rocs {
namespace ml {


/*! Type of the variable values. */
enum VariableValueType
{
	/*! Simple variable not having specific values defined. */
	VVT_NO_VALUES = 0,
	/*! Variable with two values, true and false. */
	VVT_BOOL,
	/*! Variable with an arbitrary number of integer values. */
	VVT_INT,
	/*! Variable with an arbitrary number of string values. */
	VVT_STRING
};


/*! Internal data of the \ref VariableClass class. */
struct VariableClassData
{
	VariableClassData(int _id, std::string _name, int _stateCount) :
		type(VVT_NO_VALUES), id(_id), name(_name), stateCount(_stateCount)
	{}

	VariableValueType type;
	int id;
	std::string name;
	size_t stateCount;

protected:

	VariableClassData(VariableValueType _type, int _id, std::string _name, int _stateCount) :
		type(_type), id(_id), name(_name), stateCount(_stateCount)
	{}
};

/*! Internal data of the \ref VariableClass class. */
struct BoolVariableClassData : public VariableClassData
{
	BoolVariableClassData(int id, std::string name):
		VariableClassData(VVT_BOOL, id, name, 2)
	{
		values.resize(2);
		values[0] = false;
		values[1] = true;
	}

	std::vector<bool> values;
};

/*! Internal data of the \ref VariableClass class. */
struct StringVariableClassData : public VariableClassData
{
	StringVariableClassData(int id, std::string name, int stateCount):
		VariableClassData(VVT_STRING, id, name, stateCount)
	{
		values.resize(stateCount);
	}

	std::vector<std::string> values;
};

/*! Internal data of the \ref VariableClass class. */
struct IntVariableClassData: public VariableClassData
{
	IntVariableClassData(int id, std::string name, int stateCount):
		VariableClassData(VVT_INT, id, name, stateCount)
	{
		values.resize(stateCount);
	}

	std::vector<int> values;
};


/*!
 * Convenience class providing some nice casting for various
 * types of data of @ref VariableClass.
 */
class VariableClassShallowCopyable : public core::ShallowCopyable<VariableClassData>
{
protected:

	boost::shared_ptr<StringVariableClassData> stringData()
	{ return boost::static_pointer_cast<StringVariableClassData, VariableClassData>(data()); }

	const boost::shared_ptr<StringVariableClassData> stringData() const
	{ return boost::static_pointer_cast<StringVariableClassData, VariableClassData>(data()); }

	boost::shared_ptr<IntVariableClassData> intData()
	{ return boost::static_pointer_cast<IntVariableClassData, VariableClassData>(data()); }

	const boost::shared_ptr<IntVariableClassData> intData() const
	{ return boost::static_pointer_cast<IntVariableClassData, VariableClassData>(data()); }

	boost::shared_ptr<BoolVariableClassData> boolData()
	{ return boost::static_pointer_cast<BoolVariableClassData, VariableClassData>(data()); }

	const boost::shared_ptr<BoolVariableClassData> boolData() const
	{ return boost::static_pointer_cast<BoolVariableClassData, VariableClassData>(data()); }
};


/*!
 * Class representing a single random variable.
 * @note This class uses the shallow copy mechanism (see \ref ShallowCopyable).
 */
class VariableClass : public VariableClassShallowCopyable
{
public:


	/*!
	 * Constructor, creates and initializes a variable class.
	 * @param type Type of variable values.
	 * @param id Id of the variable.
	 * @param stateCount Number of states of the variable.
	 *                   Note that for VVT_BOOL this value is always set to 2.
	 */
	VariableClass(int id, VariableValueType type = VVT_NO_VALUES, int stateCount = 2)
	{
		switch(type)
		{
		case VVT_BOOL:
			setData(new BoolVariableClassData(id, std::string()));
			break;
		case VVT_INT:
			setData(new IntVariableClassData(id, std::string(), stateCount));
			break;
		case VVT_STRING:
			setData(new StringVariableClassData(id, std::string(), stateCount));
			break;
		default:
			setData(new VariableClassData(id, std::string(), stateCount));
			break;
		}
	}


	/*!
	 * Constructor, creates and initializes a variable class.
	 * Allows to provide a name for the variable class.
	 * @param type Type of variable values.
	 * @param id Id of the variable.
	 * @param stateCount Number of states of the variable.
	 *                   Note that for VVT_BOOL this value is always set to 2.
	 */
	VariableClass(int id, std::string name, VariableValueType type = VVT_NO_VALUES, int stateCount = 2)
	{
		switch(type)
		{
		case VVT_BOOL:
			setData(new BoolVariableClassData(id, name));
			break;
		case VVT_INT:
			setData(new IntVariableClassData(id, name, stateCount));
			break;
		case VVT_STRING:
			setData(new StringVariableClassData(id, name, stateCount));
			break;
		default:
			setData(new VariableClassData(id, name, stateCount));
			break;
		}
	}


	/*!
	 * Returns the name of the variable class.
	 * @return Name of the variable class.
	 */
	std::string name() const
	{ return data()->name; }


	/*!
	 * Returns the ID of the variable class.
	 * @return ID of the variable class.
	 */
	int id() const
	{ return data()->id; }

	/*!
	 * Returns the number of states of the variable class.
	 * @return Number of states of the variable class.
	 */
	size_t stateCount() const
	{ return data()->stateCount; }

	/*!
	 * Sets the variable value for the given state. If the variable
	 * value type does not correspond to this value type,
	 * conversion occurs. If the conversion fails, the
	 * @ref ConversionException is thrown.
	 * @param state State number
	 * @param value Variable value
	 * @throw ConversionException
	 * @throw TypeException
	 */
	void setValue(size_t state, std::string &value);

	/*!
	 * Sets the variable value for the given state. If the variable
	 * value type does not correspond to this value type,
	 * conversion occurs.
	 * @param state State number
	 * @param value Variable value
	 * @throw TypeException
	 */
	void setValue(size_t state, int value);

	/*!
	 * Returns the variable value for the given state. If the
	 * variable value type does not correspond to this value type
	 * conversion occurs. If the conversion fails, the
	 * @ref ConversionException is thrown.
	 * @param state State number
	 * @return Value corresponding to the state number
	 * @throw ConversionException
	 * @throw TypeException
	 */
	int getIntValue(size_t state) const;

	/*!
	 * Returns the variable value for the given state. If the
	 * variable value type does not correspond to this value type
	 * conversion occurs.
	 * @param state State number
	 * @return Value corresponding to the state number
	 * @throw TypeException
	 */
	std::string getStringValue(size_t state) const;

	/*!
	 * Returns the variable value for the given state. If the
	 * variable value type does not correspond to this value type
	 * conversion occurs. If the conversion fails, the
	 * @ref ConversionException is thrown.
	 * @param state State number
	 * @return Value corresponding to the state number
	 * @throw ConversionException
	 * @throw TypeException
	 */
	bool getBoolValue(size_t state) const;

	/*!
	 * Returns a vector of variable values.
	 * If the variable class value type does not correspond to this
	 * value type, @ref TypeException is thrown.
	 * @return A vector of variable values
	 * @throw TypeException
	 */
	const std::vector<int> &intValues() const
	{
		if (data()->type!=VVT_INT)
			rocsTypeException("Variable class values are not integers.");
		return intData()->values;
	}

	/*!
	 * Returns a vector of variable values.
	 * If the variable class value type does not correspond to this
	 * value type, @ref TypeException is thrown.
	 * @return A vector of variable values
	 * @throw TypeException
	 */
	const std::vector<std::string> &stringValues()
	{
		if (data()->type!=VVT_STRING)
			rocsTypeException("Variable class values are not strings.");
		return stringData()->values;
	}

	/*!
	 * Returns a vector of variable values.
	 * If the variable class value type does not correspond to this
	 * value type, @ref TypeException is thrown.
	 * @return A vector of variable values
	 * @throw TypeException
	 */
	const std::vector<bool> &boolValues()
	{
		if (data()->type!=VVT_BOOL)
			rocsTypeException("Variable class values are not booleans.");
		return boolData()->values;
	}

};


}
}

#endif /* _ROCS_ML_VARIABLECLASS_H_ */
