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
 * \file VariableClassSet.cc
 *
 * \date Mar 20, 2011
 * \author Andrzej Pronobis
 */

#include "rocs/ml/VariableClassSet.h"

using namespace std;

namespace rocs {
namespace ml {

// ---------------------------------------------
VariableClass &VariableClassSet::addVariableClass(int id, std::string name,
		VariableValueType type, int stateCount)
{
	// Was name provided?
	if (name.empty())
	{
		// Id exists?
		map<int, VariableClass *>::iterator it = data()->mapId.find(id);
		if (it != data()->mapId.end())
			return *(it->second); // Yes, return
	}
	else
	{ // Name provided
		map<int, VariableClass *>::iterator it1 = data()->mapId.find(id);

		if (it1 != data()->mapId.end())
		{ // Id found
			// Name matches?
			if (it1->second->name() == name)
				return *(it1->second); // Yes, return
			else
				rocsUniquenessException("Variable class with ID '%d' already exists in this pool.", id); // No, exception
		}
		else
		{ // Id not found
			// Name exists?
			map<string, VariableClass *>::iterator it2 = data()->mapName.find(name);
			if (it2 != data()->mapName.end())
				rocsUniquenessException("Variable class with name '%s' already exists in this set.", name.c_str()); // Yes, exception
		}
	}

	// Create a new class
	data()->classes.push_back(VariableClass(id, name, type, stateCount));
	VariableClass &vc = last();
	data()->mapId[id] = &vc;
	if (!name.empty())
		data()->mapName[name] = &vc;
	if (id > data()->maxId)
		data()->maxId = id;
	return vc;
}



}
}

