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
 * libdai factor graph solver.
 *
 * \author Andrzej Pronobis
 * \file DaiBpFactorGraphSolver.cc
 */


#include "rocs/ml/DaiBpFactorGraphSolver.h"
#include "rocs/ml/FactorGraph.h"
#include <vector>

using namespace std;

namespace rocs {
namespace ml {


// ---------------------------------------------
DaiBpFactorGraphSolver::DaiBpFactorGraphSolver(FactorGraph *fg) : FactorGraphSolver(fg)
{
	// Default options
	size_t maxiter = 10000;
    dai::Real   tol = 1e-9;
    size_t verb = 1;
     _daiOptions.set("maxiter",maxiter);  // Maximum number of iterations
     _daiOptions.set("tol",tol);          // Tolerance for convergence
     _daiOptions.set("verbose",verb);
}


// ---------------------------------------------
void DaiBpFactorGraphSolver::solve()
{
	prepareDaiGraph();

	// Run inference
	rocsDebug2("Performing all inferences on a DAI factor graph using BP.");
	_bp = dai::BP(_factorGraph, _daiOptions("updates",string("SEQRND"))("logdomain",false));
	_bp.init();
	_bp.run();
}


// ---------------------------------------------
void DaiBpFactorGraphSolver::addDaiFactor(const Factor& factor)
{
	rocsDebug3("Converting a factor id:%d name:'%s' to a DAI factor.", factor.id(), factor.name().c_str() )

	// Create VarSet for this factor
	dai::VarSet daiVarSet;
	const vector<Variable> &vars = factor.variables();
	vector<dai::Var> daiVars;
	for(size_t i=vars.size(); i>0; --i)
	{
		dai::Var var(vars[i-1].id(), vars[i-1].stateCount());
		daiVars.push_back(var);
		daiVarSet.insert(var);
	}

	// Create the factor
	dai::Factor daiFactor(daiVarSet);
	dai::Permute daiPermute(daiVars, true);
	size_t stateCount = factor.stateCount();
	const double * potentials = reinterpret_cast<double*>(factor.potentials().data);
	for (size_t li = 0; li < stateCount; ++li)
		daiFactor.set(daiPermute.convertLinearIndex(li), potentials[li]);

	// Add the factor to the list
	_factors.push_back(daiFactor);
}


// ---------------------------------------------
void DaiBpFactorGraphSolver::prepareDaiGraph()
{
	// Create dai factors
	_factors.clear();
	for (FactorGraph::ConstFactorIterator it = graph()->factorBegin();
			it!=graph()->factorEnd(); ++it)
		addDaiFactor(*it);

	// Create the graph
	_factorGraph = dai::FactorGraph(_factors);
}


// ---------------------------------------------
void DaiBpFactorGraphSolver::saveDaiGraph(std::string fileName)
{
	rocsDebug2("Saving DAI factor graph to '%s'.", fileName.c_str());

	prepareDaiGraph();
	_factorGraph.WriteToFile(fileName.c_str());
}




}
}


