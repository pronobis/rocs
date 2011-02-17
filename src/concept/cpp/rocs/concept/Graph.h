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
#include <map>
#include <string>
#include <vector>

namespace rocs {

namespace core {
	class Configuration;
}

namespace concept {

struct VariableType {
	std::vector<std::string> values;
};

struct Factor {
	std::vector<std::pair<std::string, std::string> > variables;
	std::map< std::vector<std::string>, double> potential;
};

class GraphInformation {
 public:
	std::map<std::string, VariableType> types;
	std::map<std::string, Factor> factors;

	void Add(const std::string &name, const VariableType &type);
	void Add(const std::string &name, const Factor &factor);

	void LoadConfig(const std::string &configFileName);
	void LoadConfig(const core::Configuration &config);
};
}  // end namespace concept
}  // end namespace rocs

#endif  // _ROCS_CONCEPT_GRAPH_H_
