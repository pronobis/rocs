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

#include "rocs/concept/Query.h"

#define DAI_WITH_JTREE
#define DAI_WITH_BP
#include <dai/alldai.h>
#include <map>
#include <string>

#include "rocs/concept/Graph-internal.h"
#include "rocs/core/debug.h"

using namespace std;
using rocs::concept::Factor;
using rocs::concept::Variable;

namespace rocs {
namespace concept {

// This handles all internals of Query class.
// It should totally hide its dependency on libDAI.
class QueryInternal {
  public:
	QueryInternal()
	{
		size_t maxiter = 10000;
		dai::Real  tol = 1e-9;
		size_t verbose = 1;

		daiOptions_.set("maxiter", maxiter);  // Maximum number of iterations
		daiOptions_.set("tol", tol);          // Tolerance for convergence
		daiOptions_.set("verbose", verbose);
	}

	void AddFactor(const Factor& factor)
	{
		// Get potentials
		vector<double> potential;
		typedef pair<vector<string>, double> PotentialIt;
		BOOST_FOREACH(const PotentialIt &it, factor.data_->potential)
			potential.push_back(it.second);

		// Note: Be careful with potential order.
		// We use lexicographic order in the inputs.
		// DAI sorts variables by label and then uses reverse lexicographic
		// order (starting from end).
		// For that we use the dai::Permute class.
		vector<dai::Var> dai_vars = ConvertToDai(factor.variables_);
		dai::VarSet dai_varset(
			dai::SmallSet<dai::Var>(dai_vars.begin(), dai_vars.end(),
			                        dai_vars.size()));

		size_t nrStates = 1;
		for (size_t i = 0; i < dai_vars.size(); ++i )
			nrStates *= dai_vars[i].states();

		DAI_ASSERT(potential.size() == nrStates);

		dai::Factor dai_factor(dai_varset);
		dai::Permute permindex(dai_vars, true);
		for (size_t li = 0; li < nrStates; ++li)
			dai_factor.set(permindex.convertLinearIndex(li), potential[li]);

		factors_.push_back(dai_factor);
	}

	void RunInference(bool force = false) {
		if (bp_.get() == NULL || force == true)
		{
			if (factorGraph_.get() == NULL)
				MakeFactorGraph();

			rocsDebug3("Running Loopy Belife Propagation...");
			bp_.reset(new dai::BP(*factorGraph_,
					daiOptions_("updates", string("SEQRND"))
					           ("logdomain", false)));
			bp_->init();
			bp_->run();
			rocsDebug3("Finished Loopy Belife Propagation...");
		}
	}

	void MakeFactorGraph()
	{
		rocsDebug3("Creating DAI FactorGraph...");
		factorGraph_.reset(new dai::FactorGraph(factors_));

		// Invalidate BP
		bp_.reset(NULL);
	}

	void CalcMarginal(const vector<const Variable*> vars,
	                  vector<double> *output)
	{
		RunInference();
		vector<dai::Var> dai_vars = ConvertToDai(vars);
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

 protected:
	dai::Var ConvertToDai(const Variable *var)
	{
		// TODO(andresusanopinto):
		// Since dai::FactorGraph does not expects any special order for
		// variable labels, so we can just use the address of the variable.
		// Though we need to be careful about variable id size and pointer size.
		// TODO(andresp): remove double lookup.
		if (variables_.find(var) == variables_.end())
		{
			size_t varIndex = variables_.size();
			variables_[var] = dai::Var(varIndex, var->type_->values.size());
		}
		return variables_[var];
	}

	vector<dai::Var> ConvertToDai(const vector<const Variable*> &variables)
	{
		vector<dai::Var> dai(variables.size());
		for (size_t i = 0; i < variables.size(); ++i)
			dai[i] = ConvertToDai(variables[i]);
		return dai;
	}

	map<const Variable*, dai::Var> variables_;
	vector<dai::Factor> factors_;
	boost::scoped_ptr<dai::FactorGraph> factorGraph_;
	boost::scoped_ptr<dai::BP> bp_;
    dai::PropertySet daiOptions_;
};




Query::Query(const Graph *graph): graph_(graph)
{
}

Query::~Query() {}

void Query::BuildInternal()
{
	if (internal_.get() != NULL)
		return;

	internal_.reset(new QueryInternal());
	BOOST_FOREACH(const Factor &f, graph_->factors_)
		internal_->AddFactor(f);
}

void Query::Marginalize(const vector<const Variable*> &variables,
                        vector<double> *output)
{
	if (!internal_.get())
		BuildInternal();

	return internal_->CalcMarginal(variables, output);
}

}  // end namespace concept
}  // end namespace rocs
