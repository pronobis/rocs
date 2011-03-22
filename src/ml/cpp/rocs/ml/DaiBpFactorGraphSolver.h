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
 * \file DaiBpFactorGraphSolver.h
 */

#ifndef _ROCS_ML_DAIBPFACTORGRAPHSOLVER_H_
#define _ROCS_ML_DAIBPFACTORGRAPHSOLVER_H_

#include "rocs/ml/FactorGraphSolver.h"

#define DAI_WITH_BP
#include <dai/alldai.h>

namespace rocs {
namespace ml {

class Factor;


class DaiBpFactorGraphSolver : public FactorGraphSolver
{
public:

	DaiBpFactorGraphSolver(FactorGraph *fg);

	virtual ~DaiBpFactorGraphSolver()
	{}

	/*! Performs all inferences on the graph. */
	virtual void solve();

	/*! Saves the graph in the DAI format to a file. */
	void saveDaiGraph(std::string fileName);


	dai::PropertySet &daiOptions()
	{ return _daiOptions; }


private:

	/*! Creates a single DAI factor and adds it to a list. */
	void addDaiFactor(const Factor& factor);

	/*! Creates the DAI graph. */
	void prepareDaiGraph();


private:

	std::vector<dai::Factor> _factors;
	dai::FactorGraph _factorGraph;
	dai::BP _bp;
    dai::PropertySet _daiOptions;

};


}
}

#endif /** _ROCS_ML_DAIFACTORGRAPHSOLVER_H_ */

