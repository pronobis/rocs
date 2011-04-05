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
void DaiBpFactorGraphSolver::solveMP()
{
	prepareDaiGraph();

	// Run inference
	rocsDebug2("Performing all inferences on a DAI factor graph using BP.");
	_bp = dai::BP(_factorGraph, _daiOptions("updates",string("SEQRND"))("logdomain",false)("inference",string("MAXPROD"))("damping",string("0.1")));

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
	dai::Permute daiPermute(daiVars, false);
	for (size_t i=0; i<daiPermute.sigma().size(); ++i)
		rocsDebug3("%d %d -> %d", daiVars[i].label(), i, daiPermute.sigma()[i]);
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

// ---------------------------------------------
dai::Factor DaiBpFactorGraphSolver::getMarginal(const Variable &variable)
{
	// Find DAI variables
	const dai::Var *var = 0;
	for (size_t i=0; i<_factorGraph.vars().size(); ++i)
		if (static_cast<int>(_factorGraph.var(i).label()) == variable.id())
			var = &_factorGraph.var(i);

	if (!var)
		rocsException("Unable to find the variable!");

	return _bp.belief(*var);
}


// ---------------------------------------------
vector<size_t> DaiBpFactorGraphSolver::getMAP()
{
	return _bp.findMaximum();
}


// ---------------------------------------------
double DaiBpFactorGraphSolver::getMapPosterior()
{
	rocsDebug3("Obtaining MAP posterior probability.")

	vector<size_t> map = _bp.findMaximum();

	rocsDebug3("%f", _bp.logScore(map));
	return exp(_bp.logScore(map));


/*	// Create VarSet for this factor
	dai::VarSet daiVarSet;
	vector<dai::Var> daiVars;
	for(size_t i=0; i<_factorGraph.vars().size()-7; i++)
	{
		daiVars.push_back(_factorGraph.vars()[i]);
		daiVarSet.insert(_factorGraph.vars()[i]);
		rocsDebug3("%d", _factorGraph.vars()[i].label());
	}

    dai::Factor marginal = _bp.belief(daiVarSet);
    vector<size_t> map = _bp.findMaximum();

	// Convert output to original variable order.
	size_t nrStates = 1;
	for (size_t i = 0; i < daiVars.size(); ++i )
		nrStates *= daiVars[i].states();
	rocsAssert(marginal.nrStates() == nrStates);

	// Get the index of the value
	int index = 0;
	int step = 1;
	for (int i=daiVars.size(); i>0; --i)
	{
		index+= map[i-1] * step;
		step*=daiVars[i-1].states();
	}

	dai::Permute permindex(daiVars, false);
	return marginal.get(permindex.convertLinearIndex(index)); */

}










/*
void CalcMarginal(const vector<const Variable*> vars,
                  vector<double> *output)
{
	dai::VarSet dai_varset(
		dai::SmallSet<dai::Var>(dai_vars.begin(), dai_vars.end(),
		                        dai_vars.size()));

	rocsDebug3("Asking belief on set of %ld variables.", dai_varset.size());
    dai::Factor marginal = bp_->belief(dai_varset);

	// Convert output to original variable order.
	size_t nrStates = 1;
	for (size_t i = 0; i < dai_vars.size(); ++i )
		nrStates *= dai_vars[i].states();

	DAI_ASSERT(marginal.nrStates() == nrStates);
	dai::Permute permindex(dai_vars, true);
	for (size_t li = 0; li < nrStates; ++li)
		output->push_back(marginal.get(permindex.convertLinearIndex(li)));
}
*/











}
}


