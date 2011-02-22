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
 * \file Graph-internal.h
 *
 * This file contains internals of graph models. And no code should rely
 * on the definitions of this file.
 * Its used to share graph internals between Graph.cc and Query.cc.
 */
#ifndef _ROCS_CONCEPT_GRAPH_INTERNAL_H_
#define _ROCS_CONCEPT_GRAPH_INTERNAL_H_

#include <vector>
#include "rocs/concept/Graph.h"

namespace rocs {
namespace concept {

class Variable {
 public:
	explicit Variable(const VariableType *type):type_(type) {}

	const VariableType *type_;
};

class Factor {
 public:
	Factor(const FactorData *data, const std::vector<const Variable*> &variables)
			:data_(data), variables_(variables) {}

	const FactorData *data_;
	std::vector<const Variable*> variables_;
};

}  // end namespace concept
}  // end namespace rocs

#endif  // _ROCS_CONCEPT_GRAPH_INTERNAL_H_
