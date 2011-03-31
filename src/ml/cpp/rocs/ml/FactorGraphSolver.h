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
 * Factor graph solver interface.
 *
 * \author Andrzej Pronobis
 * \file FactorGraphSolver.h
 */

#ifndef _ROCS_ML_FACTORGRAPHSOLVER_H_
#define _ROCS_ML_FACTORGRAPHSOLVER_H_

#include "rocs/ml/Factor.h"

namespace rocs {
namespace ml {

class FactorGraph;
class Variable;

/*!
 * Interface of a generic factor graph solver.
 */
class FactorGraphSolver
{
public:

	FactorGraphSolver(const FactorGraph *fg): _graph(fg)
	{}

	virtual ~FactorGraphSolver()
	{};

	void setGraph(const FactorGraph *fg)
	{ _graph = fg; }

	virtual void solve() = 0;

	const FactorGraph *graph() const
	{ return _graph; }


private:

	const FactorGraph *_graph;

};


}
}

#endif /** _ROCS_ML_FACTORGRAPHSOLVER_H_ */
