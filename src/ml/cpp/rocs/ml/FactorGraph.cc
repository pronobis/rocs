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
 * \file FactorGraph.cc
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */

#include "rocs/ml/FactorGraph.h"

using namespace std;

namespace rocs {
namespace ml {


// ---------------------------------------------
Factor &FactorGraph::addFactor(int id, std::string name, const std::vector<Variable> &vars,
		const FactorClass &factorClass)
{
	rocsDebug3("Adding FactorGraph factor id:%d name:'%s'.", id, name.c_str());

	Factor *factor=verifyFactorIdAndName(id, name);
	if (factor)
		return *factor;

	// Check if the variables exist
	for (size_t i=0; i<vars.size(); ++i)
		if (!variableExists(vars[i].id()))
			rocsError("Variable id:%d does not exist in the graph.", vars[i].id());

	// Create a new class
	data()->factors.push_back(Factor(id, name, vars, factorClass));
	Factor &f = factorLast();
	data()->mapFactorId[id] = &f;
	if (!name.empty())
		data()->mapFactorName[name] = &f;
	if (id > data()->maxFactorId)
		data()->maxFactorId = id;
	return f;
}


// ---------------------------------------------
Factor &FactorGraph::addFactor(int id, std::string name, const std::vector<Variable> &vars,
		const cv::Mat &potentials)
{
	rocsDebug3("Adding FactorGraph factor id:%d name:'%s'.", id, name.c_str());

	Factor * factor = verifyFactorIdAndName(id, name);
	if (factor)
		return *factor;

	// Check if the variables exist
	for (size_t i=0; i<vars.size(); ++i)
		if (!variableExists(vars[i].id()))
			rocsError("Variable id:%d does not exist in the graph.", vars[i].id());

	// Create a new class
	data()->factors.push_back(Factor(id, name, vars, potentials));
	Factor &f = factorLast();
	data()->mapFactorId[id] = &f;
	if (!name.empty())
		data()->mapFactorName[name] = &f;
	if (id > data()->maxFactorId)
		data()->maxFactorId = id;
	return f;
}



// ---------------------------------------------
Factor &FactorGraph::addFactor(int id, std::string name, const Variable &var,
		const FactorClass &factorClass)
{
	rocsDebug3("Adding FactorGraph factor id:%d name:'%s'.", id, name.c_str());

	Factor * factor = verifyFactorIdAndName(id, name);
	if (factor)
		return *factor;

	// Check if the variables exist
	if (!variableExists(var.id()))
		rocsError("Variable id:%d does not exist in the graph.", var.id());

	// Create a new class
	data()->factors.push_back(Factor(id, name, var, factorClass));
	Factor &f = factorLast();
	data()->mapFactorId[id] = &f;
	if (!name.empty())
		data()->mapFactorName[name] = &f;
	if (id > data()->maxFactorId)
		data()->maxFactorId = id;
	return f;
}


// ---------------------------------------------
Factor &FactorGraph::addFactor(int id, std::string name, const Variable &var,
		const cv::Mat &potentials)
{
	rocsDebug3("Adding FactorGraph factor id:%d name:'%s'.", id, name.c_str());

	Factor * factor = verifyFactorIdAndName(id, name);
	if (factor)
		return *factor;

	// Check if the variables exist
	if (!variableExists(var.id()))
		rocsError("Variable id:%d does not exist in the graph.", var.id());

	// Create a new class
	data()->factors.push_back(Factor(id, name, var, potentials));
	Factor &f = factorLast();
	data()->mapFactorId[id] = &f;
	if (!name.empty())
		data()->mapFactorName[name] = &f;
	if (id > data()->maxFactorId)
		data()->maxFactorId = id;
	return f;
}



// ---------------------------------------------
Factor &FactorGraph::addFactor(int id, std::string name, const Variable &var1, const Variable &var2,
		const FactorClass &factorClass)
{
	rocsDebug3("Adding FactorGraph factor id:%d name:'%s'.", id, name.c_str());

	Factor * factor = verifyFactorIdAndName(id, name);
	if (factor)
		return *factor;

	// Check if the variables exist
	if (!variableExists(var1.id()))
		rocsError("Variable id:%d does not exist in the graph.", var1.id());
	if (!variableExists(var2.id()))
		rocsError("Variable id:%d does not exist in the graph.", var2.id());

	// Create a new class
	data()->factors.push_back(Factor(id, name, var1, var2, factorClass));
	Factor &f = factorLast();
	data()->mapFactorId[id] = &f;
	if (!name.empty())
		data()->mapFactorName[name] = &f;
	if (id > data()->maxFactorId)
		data()->maxFactorId = id;
	return f;
}


// ---------------------------------------------
Factor &FactorGraph::addFactor(int id, std::string name, const Variable &var1, const Variable &var2,
		const cv::Mat &potentials)
{
	rocsDebug3("Adding FactorGraph factor id:%d name:'%s'.", id, name.c_str());

	Factor * factor = verifyFactorIdAndName(id, name);
	if (factor)
		return *factor;

	// Check if the variables exist
	if (!variableExists(var1.id()))
		rocsError("Variable id:%d does not exist in the graph.", var1.id());
	if (!variableExists(var2.id()))
		rocsError("Variable id:%d does not exist in the graph.", var2.id());

	// Create a new class
	data()->factors.push_back(Factor(id, name, var1, var2, potentials));
	Factor &f = factorLast();
	data()->mapFactorId[id] = &f;
	if (!name.empty())
		data()->mapFactorName[name] = &f;
	if (id > data()->maxFactorId)
		data()->maxFactorId = id;
	return f;
}


// ---------------------------------------------
Variable &FactorGraph::addVariable(int id, std::string name, const VariableClass &varClass)
{
	rocsDebug3("Adding FactorGraph variable id:%d name:'%s'.", id, name.c_str());

	// Was name provided?
	if (name.empty())
	{
		// Id exists?
		map<int, Variable *>::iterator it = data()->mapVarId.find(id);
		if (it != data()->mapVarId.end())
			return *(it->second); // Yes, return
	}
	else
	{ // Name provided
		map<int, Variable *>::iterator it1 = data()->mapVarId.find(id);

		if (it1 != data()->mapVarId.end())
		{ // Id found
			// Name matches?
			if (it1->second->name() == name)
				return *(it1->second); // Yes, return
			else
				rocsUniquenessException("Variable with ID '%d' already exists in this pool.", id); // No, exception
		}
		else
		{ // Id not found
			// Name exists?
			map<string, Variable *>::iterator it2 = data()->mapVarName.find(name);
			if (it2 != data()->mapVarName.end())
				rocsUniquenessException("Variable with name '%s' already exists in this set.", name.c_str()); // Yes, exception
		}
	}

	// Create a new class
	data()->vars.push_back(Variable(id, name, varClass));
	Variable &f = variableLast();
	data()->mapVarId[id] = &f;
	if (!name.empty())
		data()->mapVarName[name] = &f;
	if (id > data()->maxVariableId)
		data()->maxVariableId = id;
	return f;
}


// ---------------------------------------------
Factor *FactorGraph::verifyFactorIdAndName(int id, std::string name)
{
	// Was name provided?
	if (name.empty())
	{
		// Id exists?
		map<int, Factor *>::iterator it = data()->mapFactorId.find(id);
		if (it != data()->mapFactorId.end())
			return (it->second); // Yes, return
	}
	else
	{ // Name provided
		map<int, Factor *>::iterator it1 = data()->mapFactorId.find(id);

		if (it1 != data()->mapFactorId.end())
		{ // Id found
			// Name matches?
			if (it1->second->name() == name)
				return (it1->second); // Yes, return
			else
				rocsUniquenessException("Factor with ID '%d' already exists in this pool.", id); // No, exception
		}
		else
		{ // Id not found
			// Name exists?
			map<string, Factor *>::iterator it2 = data()->mapFactorName.find(name);
			if (it2 != data()->mapFactorName.end())
				rocsUniquenessException("Factor with name '%s' already exists in this set.", name.c_str()); // Yes, exception
		}
	}

	return 0;
}



std::ostream& operator<<(std::ostream &out, const FactorGraph &fg)
{
	out << "Factor Graph" << std::endl;
	out << "------------------------" << std::endl;
	for (FactorGraph::ConstVariableIterator it = fg.variableBegin(); it!=fg.variableEnd(); ++it)
		out << *it;
	for (FactorGraph::ConstFactorIterator it = fg.factorBegin(); it!=fg.factorEnd(); ++it)
		out << *it;


	out << std::endl;
    return out;
}



}
}
