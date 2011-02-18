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

}  // end namespace concept
}  // end namespace rocs
