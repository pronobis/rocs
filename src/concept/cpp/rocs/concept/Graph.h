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

/*!
 * \author André Susano Pinto
 * \file Graph.h
 */

#ifndef _ROCS_CONCEPT_GRAPH_H_
#define _ROCS_CONCEPT_GRAPH_H_

#include <algorithm>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>
#include <string>
#include <vector>

namespace rocs {

namespace core {
	class Configuration;
}

namespace concept {

struct VariableType {
	// This vector must be sorted. This allows to use it in a simple
	// way to calculate variable indexs.
	std::vector<std::string> values;
};

struct FactorData {
	std::vector<std::pair<std::string, std::string> > variables;
	std::map<std::vector<std::string>, double> potential;
};

class GraphInformation {
 public:
	std::map<std::string, VariableType> types;
	std::map<std::string, FactorData>   factors;

	void Add(const std::string &name, const VariableType &type);
	void Add(const std::string &name, const FactorData &factor);

	void LoadConfig(const std::string &configFileName);
	void LoadConfig(const core::Configuration &config);

	// Returns true if the defined types and factors are consistent.
	// Debug information is produced in the negative case.
	bool CheckConsistency() const;

	bool CheckVarTypeConsistency(const std::string &name,
	                             const VariableType &type) const;

	bool CheckFactorConsistency(const std::string &name,
	                            const FactorData &factor) const;
};


class Variable;  // This class definition is never exposed externaly.
class Factor;    // This class definition is never exposed externaly.

class Graph {
 public:
	// Creates a new variable of the given type.
	// Returns a reference to the newly created variable.
	// VariableType must exist for the lifetime of this Graph.
	// Graph maintains ownership on the returned variable.
	const Variable* createVariable(const VariableType* type);

	// Creates a factor between the given variables.
	// FactorData must exist for the lifetime of this Graph.
	// Graph maintains ownership on the returned factor.
	const Factor* createFactor(const FactorData *factorData,
	                           const std::vector<const Variable*> &vars);

 protected:
	boost::ptr_vector<Variable> variables_;
	boost::ptr_vector<Factor> factors_;

 private:
	// DISALLOW COPY AND ASSIGN
	Graph(const Graph &);
	void operator = (const Graph &);
};
}  // end namespace concept
}  // end namespace rocs

#endif  // _ROCS_CONCEPT_GRAPH_H_

