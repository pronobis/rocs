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
 * \file FactorGraph.h
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_ML_FACTORGRAPH_H_
#define _ROCS_ML_FACTORGRAPH_H_

namespace rocs {
namespace ml {

//#include "rocs/ml/Factor.h"
//#include "rocs/ml/Variable.h"


/*
!
 * Class defining a factor graph.
 * It requires a solver class to perform all the inferences on the graph.

class FactorGraph
{
public:

	! Iterator used to iterate over factors.
	typedef std::list<Factor>::iterator FactorIterator;

	! Iterator used to iterate over variables.
	typedef std::list<Variable>::iterator VariableIterator;


public:

	! Default constructor. Creates an empty factor graph.
	FactorGraph()
	{}

	!
	 * Adds a factor to the graph.
	 * \param factor Factor to be added.
	 * \return Iterator pointing at the added factor.

	FactorIterator &addFactor(const Factor &factor);

	!
	 * Creates a new factor and adds it to the graph.
	 * The values of the factor are not set and need to be set later.
	 * See the description of Factor for more details about the parameters.
	 * @param variables Variables used to create the factor.
	 * @return Iterator pointing at the added factor.

	FactorIterator &addFactor(const std::vector<Variable> &variables);

	!
	 * Creates a new factor and adds it to the graph.
	 * See the description of Factor for more details about the parameters.
	 * @param variables Variables used to create the factor.
	 * @param values Factor values.
	 * @return Iterator pointing at the added factor.

	FactorIterator &addFactor(const std::vector<Variable> &variables, const cv::Mat &values);

	!
	 * Adds a variable to the graph.
	 * \param variable Variable to be added.
	 * \return Iterator pointing at the added variable.

	VariableIterator &addVariable(const Variable &variable);

	!
	 * Creates a new variable and adds it to the graph.
	 * See the description of Variable for more details about the parameters.
	 * \param states Number of states of the variable
	 * \return Iterator pointing at the added variable.

	VariableIterator &addVariable(unsigned int states);


public:

	! Returns the number of factors in the graph.
	unsigned int factorCount() const;

	! Returns the number of variables in the graph.
	unsigned int variableCount() const;


private:

	! Factors of the graph.
	std::list<Factor> _factors;

	! Variables of the graph.
	std::list<Variable> _variables;
};
*/


}
}

#endif /* _ROCS_ML_FACTORGRAPH_H_ */
