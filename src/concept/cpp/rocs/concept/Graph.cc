// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2011  André Susano Pinto
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
#include "rocs/concept/Graph.h"
#include "rocs/core/Configuration.h"
#include "rocs/core/debug.h"

using rocs::core::Configuration;
using boost::property_tree::ptree;
using namespace std;

namespace rocs {
namespace concept {

namespace {

bool LoadVariableType(const Configuration &config,
		const string &prefix, VariableType &type)
{
	vector<string> values;
	config.getValueList(prefix, "name", values);
	sort(values.begin(), values.end());

	type.values = values;
	return true;
}

bool LoadFactorData(const Configuration &config,
		const string &prefix, FactorData &factor)
{
	// Load variables for the factor
	{
		vector<string> varnames, vartypes;
		config.getValueList(prefix, "var", varnames);
		config.getValueList(prefix, "type", vartypes);

		if (varnames.size() == 0
		|| varnames.size() != vartypes.size())
			return false;

		factor.variables.resize(varnames.size());
		for (size_t i = 0; i < varnames.size(); ++i)
			factor.variables[i] = make_pair(varnames[i], vartypes[i]);
	}

	// Load potentials for the factor
	{
		vector<double> potential;
		config.getValueList(prefix, "potential", potential);

		vector< vector<string> > var_index(factor.variables.size());
		for (size_t i = 0; i < factor.variables.size(); ++i)
		{
			config.getValueList(prefix, factor.variables[i].first, var_index[i]);
			if (var_index[0].size() != var_index[i].size())
				return false;
		}
		for (size_t i = 0; i < potential.size(); ++i) {
			vector<string> index(factor.variables.size());
			for (size_t v = 0; v < index.size(); ++v)
				index[v] = var_index[v][i];
			factor.potential[index] = potential[i];
		}
	}
	return true;
}

// Unfortunaly is_sorted is a SGI extension.
// Therefore we need to define it.
template<typename T>
bool is_sorted(T begin, T end)
{
	if (begin == end)
		return true;

	T next = begin;
	for (++next; next != end; begin = next, ++next)
		if(*next < *begin)
			return false;
	return true;
}

// Builds a vector with the variable types of the given FactorData.
// Returns false in case not all variables types are defined.
bool GetVariableTypes(const FactorData &data,
                      const map<string, VariableType> &known_types,
                      vector<const VariableType*> *vartypes)
{
	typedef pair<string, string> PSS;
	BOOST_FOREACH(const PSS &v, data.variables)
	{
		map<string, VariableType>::const_iterator it = known_types.find(v.second);
		if (it == known_types.end())
		{
			rocsDebug2("Invalid FactorData: Unknown variable type '%s'",
					v.second.c_str());
			return false;
		}
		vartypes->push_back(&it->second);
	}
	return true;
}
}  // end namespace anonymous

void GraphInformation::LoadConfig(const string &configFileName)
{
	core::Configuration config;
	config.addConfigFile(configFileName);
	LoadConfig(config);
}

void GraphInformation::LoadConfig(const core::Configuration &config)
{
	// Load variable types
	{
		vector<string> childs;
		config.getChildren("variable_type", &childs);
		BOOST_FOREACH(const string &child_path, childs)
		{
			const string name = child_path.substr(child_path.find_last_of(".")+1);
			rocsDebug3("Loading variable: %s", name.c_str());

			VariableType type;
			if (LoadVariableType(config, child_path, type))
				Add(name, type);
		}
	}

	// Load factors
	{
		vector<string> childs;
		config.getChildren("factor", &childs);
		BOOST_FOREACH(const string &child_path, childs)
		{
			const string name = child_path.substr(child_path.find_last_of(".")+1);
			rocsDebug3("Loading factor: %s", name.c_str());

			FactorData factor;
			if (LoadFactorData(config, child_path, factor))
				Add(name, factor);
		}
	}
}

void GraphInformation::Add(const string &name, const FactorData &factor)
{
	rocsDebug2("Add factor type: %s'", name.c_str());
	if (factors.insert(make_pair(name, factor)).second == false)
		rocsDebug1("Dropped factor: there is already a factor with that name '%s'",
				name.c_str());
}

void GraphInformation::Add(const string &name, const VariableType &type)
{
	rocsDebug2("Add variable type: %s'", name.c_str());
	if (types.insert(make_pair(name, type)).second == false)
		rocsDebug1("Dropped type: there is already a type with that name '%s'",
				name.c_str());
}

bool GraphInformation::CheckVarTypeConsistency(const string &name,
                                               const VariableType &type) const
{
	bool consistent = true;
	if (type.values.size() == 0)
	{
		rocsDebug2("VariableType '%s' has no defined possible values.", name.c_str());
		consistent = false;
	}

	if (!is_sorted(type.values.begin(), type.values.end()))
	{
		rocsDebug2("VariableType '%s' values are not sorted.", name.c_str());
		consistent = false;
	}
	return consistent;
}

bool GraphInformation::CheckFactorConsistency(const string &name,
                                              const FactorData &factor) const
{
	if (factor.variables.size() == 0)
	{
		rocsDebug2("FactorData '%s' does not has any variable.", name.c_str());
		return false;
	}

	vector<const VariableType*> vartypes;
	if (!GetVariableTypes(factor, types, &vartypes))
	{
		rocsDebug2("FactorData '%s' has undefined variable types.", name.c_str());
		return false;
	}

	// Variables types are correct, check potentials consistency
	bool consistent = true;

	typedef pair<vector<string>, double> PotentialIt;
	BOOST_FOREACH(const PotentialIt &p, factor.potential)
	{
		// Non-negative potentials only.
		if (p.second < 0)
		{
			rocsDebug2("FactorData '%s': found negative potential.", name.c_str());
			consistent = false;
		}

		// Check potential index.
		if (p.first.size() != vartypes.size())
		{
			rocsDebug2("FactorData '%s': found potential that does not agrees in"
			           " number of variables", name.c_str());
			consistent = false;
			continue;
		}

		for (size_t i = 0; i != vartypes.size(); ++i)
		{
			// Considering we have the indexes sorted and the variables sorted this
			// is inefficient. Though it does not matters since this code is mainly
			// for helping debugging.
			if (find(vartypes[i]->values.begin(), vartypes[i]->values.end(),
					p.first[i]) == vartypes[i]->values.end())
			{
				rocsDebug2("FactorData '%s': potential with incorrect value"
						"'%s' for variable %s.", name.c_str(),
						p.first[i].c_str(), factor.variables[i].first.c_str());
				consistent = false;
			}
		}
	}
	
	// Check if all potentials were defined.
	size_t total_size = 1;
	BOOST_FOREACH(const VariableType *type, vartypes)
		total_size *= type->values.size();

	if (total_size != factor.potential.size())
	{
		rocsDebug2("FactorData '%s': not all potentials are defined.", name.c_str());
		consistent = false;
	}

	return consistent;
}

bool GraphInformation::CheckConsistency() const
{
	bool consistent = true;

	// Check VariableType consistency
	typedef pair<string, VariableType> VarTypeIt;
	BOOST_FOREACH(const VarTypeIt &vartype, types)
		consistent |= CheckVarTypeConsistency(vartype.first, vartype.second);

	// Check FactorData consistency
	typedef pair<string, FactorData> FactorDataIt;
	BOOST_FOREACH(const FactorDataIt &factor, factors)
		consistent |= CheckFactorConsistency(factor.first, factor.second);

	return consistent;
}

class Variable {
 public:
	explicit Variable(const VariableType *type):type_(type) {}

	const VariableType *type_;
};

class Factor {
 public:
	Factor(const FactorData *data, const vector<const Variable*> &variables)
			:data_(data), variables_(variables) {}

	const FactorData *data_;
	vector<const Variable*> variables_;
};

const Variable* Graph::createVariable(const VariableType *type)
{
	Variable *variable = new Variable(type);
	variables_.push_back(variable);
	return variable;
}

const Factor* Graph::createFactor(const FactorData *data,
                           const vector<const Variable*> &variables)
{
	Factor* factor = new Factor(data, variables);
	factors_.push_back(factor);
	return factor;
}

}  // end namespace concept
}  // end namespace rocs
