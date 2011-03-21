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
 * \file VariableClassSet.h
 *
 * \date Mar 20, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_ML_VARIABLETYPESET_H_
#define _ROCS_ML_VARIABLETYPESET_H_

#include "rocs/ml/VariableClass.h"
#include "rocs/core/ShallowCopyable.h"
#include <list>
#include <map>

namespace rocs {
namespace ml {

/*! Internal data of the @ref VariableClassSet class. */
struct VariableClassSetData
{
	VariableClassSetData() : maxId(0)
	{}

	/*! List of classes added to the set. */
	std::list<VariableClass> classes;

	std::map<int, VariableClass *> mapId;
	std::map<std::string, VariableClass *> mapName;

	/*! The largest Id added so far. */
	int maxId;
};


/*!
 * Variable class set class. Stores and creates variable classes.
 * @note This class uses the shallow copy mechanism (see \ref ShallowCopyable).
 */
class VariableClassSet : public core::ShallowCopyable<VariableClassSetData>
{
public:

	typedef std::list<VariableClass>::iterator Iterator;


public:

	/*! Constructor, creates an empty set. */
	VariableClassSet() : SC(new VariableClassSetData())
	{}

	/*!
	 * Creates a variable class with the given ID and name and adds it
	 * to the set if a class with this name and ID does not exist yet.
	 * If a class with this name and ID exists already, nothing is
	 * created and a reference to the class is returned. If an ID
	 * exists but not the name, or the opposite, the function throws
	 * @ref UniquenessException. If an empty name is given, the
	 * function ignores it.
	 * @param id ID of the variable class
	 * @param name name of the variable class
	 * @param type Variable class value type
	 * @param stateCount Number of states of the variable class
	 * @return Reference to the variable class
	 * @throw UniquenessException
	 */
	VariableClass &addVariableClass(int id, std::string name, VariableValueType type = VVT_NO_VALUES, int stateCount = 2);

	/*!
	 * Creates a variable class with a unique ID and the given name and adds
	 * it to the set if a class with this name does not exist yet. If a class
	 * with this name already exists, nothing is created and a reference
	 * to the class is returned. If an empty name is given, the function
	 * ignores it.
	 * @param name name of the variable class
	 * @param type Variable class value type
	 * @param stateCount Number of states of the variable class
	 * @return Reference to the variable class
	 */
	VariableClass &addVariableClass(std::string name, VariableValueType type = VVT_NO_VALUES, int stateCount = 2)
	{ return addVariableClass(getUniqueId(), name, type, stateCount); }

	/*!
	 * Creates a variable class with the given ID and adds it to the set if
	 * a class with this ID does not exist yet. If a class with this ID
	 * already exists, nothing is created and a reference to the class is
	 * returned. The function assigns an empty name to the class.
	 * @param id ID of the variable class
	 * @param type Variable class value type
	 * @param stateCount Number of states of the variable class
	 * @return Reference to the variable class
	 */
	VariableClass &addVariableClass(int id, VariableValueType type = VVT_NO_VALUES, int stateCount = 2)
	{ return addVariableClass(id, std::string(), type, stateCount); }

	/*!
	 * Creates a variable class with a unique ID and adds it to the set.
	 * The function assigns an empty name to the class.
	 * @param type Variable class value type
	 * @param stateCount Number of states of the variable class
	 * @return Reference to the newly created and added variable class
	 */
	VariableClass &addVariableClass(VariableValueType type = VVT_NO_VALUES, int stateCount = 2)
	{ return addVariableClass(getUniqueId(), std::string(), type, stateCount); }

	/*!
	 * Returns the number of variable classes in the set.
	 * @return The number of variable classes in the set.
	 */
	size_t count() const
	{ return data()->classes.size(); }

	Iterator begin()
	{ return data()->classes.begin(); }

	Iterator end()
	{ return data()->classes.end(); }

	VariableClass &first()
	{ return data()->classes.front(); }

	VariableClass &last()
	{ return data()->classes.back(); }


private:

	int getUniqueId()
	{
		return data()->maxId+1;
	}
};


}
}

#endif /* _ROCS_ML_VARIABLETYPESET_H_ */
