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

#include "rocs/ml/Factor.h"
#include "rocs/ml/Variable.h"
#include "rocs/core/ShallowCopyable.h"
#include <list>

namespace rocs {
namespace ml {


/*! Internal data of the @ref FactorGraph class. */
struct FactorGraphData
{
	FactorGraphData(): maxVariableId(0), maxFactorId(0)
	{}

	/*! List of variable classes added to the graph. */
	std::list<Variable> vars;

	/*! List of factor classes added to the graph. */
	std::list<Factor> factors;

	std::map<int, Variable*> mapVarId;
	std::map<std::string, Variable*> mapVarName;

	std::map<int, Factor*> mapFactorId;
	std::map<std::string, Factor*> mapFactorName;

	/*! The largest variable Id added so far. */
	int maxVariableId;

	/*! The largest factor Id added so far. */
	int maxFactorId;
};


/*!
 * Class defining a factor graph.
 * It requires a solver class to perform all the inferences on the graph.
 */
class FactorGraph : public core::ShallowCopyable<FactorGraphData>
{
public:

	/*! Iterator used to iterate over factors. */
	typedef std::list<Factor>::iterator FactorIterator;

	/*! Iterator used to iterate over variables. */
	typedef std::list<Variable>::iterator VariableIterator;

	/*! Iterator used to iterate over factors. */
	typedef std::list<Factor>::const_iterator ConstFactorIterator;

	/*! Iterator used to iterate over variables. */
	typedef std::list<Variable>::const_iterator ConstVariableIterator;


public:

	/*! Default constructor. Creates an empty factor graph. */
	FactorGraph(): SC(new FactorGraphData())
	{}


public: // Factors

	// Accepting vector of variables & factor class
	Factor &addFactor(int id, std::string name, const std::vector<Variable> &vars,
			const FactorClass &factorClass);

	Factor &addFactor(int id, const std::vector<Variable> &vars,
			const FactorClass &factorClass)
		{ return addFactor(id, std::string(), vars, factorClass); }

	Factor &addFactor(std::string name, const std::vector<Variable> &vars,
			const FactorClass &factorClass)
		{ return addFactor(getUniqueFactorId(), name, vars, factorClass); }

	Factor &addFactor(const std::vector<Variable> &vars, const FactorClass &factorClass)
		{ return addFactor(getUniqueFactorId(), std::string(), vars, factorClass); }


	// Accepting vector of variables & potentials
	Factor &addFactor(int id, std::string name,	const std::vector<Variable> &vars,
			const cv::Mat &potentials);

	Factor &addFactor(int id, const std::vector<Variable> &vars,
			const cv::Mat &potentials)
		{ return addFactor(id, std::string(), vars, potentials); }

	Factor &addFactor(std::string name, const std::vector<Variable> &vars,
			const cv::Mat &potentials)
		{ return addFactor(getUniqueFactorId(), name, vars, potentials); }

	Factor &addFactor(const std::vector<Variable> &vars,
			const cv::Mat &potentials)
		{ return addFactor(getUniqueFactorId(), std::string(), vars, potentials); }


	// Accepting single variable & factor class
	Factor &addFactor(int id, std::string name, const Variable &var,
			const FactorClass &factorClass);

	Factor &addFactor(int id, const Variable &var,
			const FactorClass &factorClass)
	{ return addFactor(id, std::string(), var, factorClass); }

	Factor &addFactor(std::string name, const Variable &var,
			const FactorClass &factorClass)
	{ return addFactor(getUniqueFactorId(), name, var, factorClass); }

	Factor &addFactor(const Variable &var, const FactorClass &factorClass)
	{ return addFactor(getUniqueFactorId(), std::string(), var, factorClass); }


	// Accepting single variable & potentials
	Factor &addFactor(int id, std::string name, const Variable &var,
			const cv::Mat &potentials);

	Factor &addFactor(int id, const Variable &var,
			const cv::Mat &potentials)
	{ return addFactor(id, std::string(), var, potentials); }

	Factor &addFactor(std::string name, const Variable &var,
			const cv::Mat &potentials)
	{ return addFactor(getUniqueFactorId(), name, var, potentials); }

	Factor &addFactor(const Variable &var, const cv::Mat &potentials)
	{ return addFactor(getUniqueFactorId(), std::string(), var, potentials); }


	// Accepting two variables & factor class
	Factor &addFactor(int id, std::string name, const Variable &var1, const Variable &var2,
			const FactorClass &factorClass);

	Factor &addFactor(int id, const Variable &var1, const Variable &var2,
			const FactorClass &factorClass)
	{ return addFactor(id, std::string(), var1, var2, factorClass); }

	Factor &addFactor(std::string name, const Variable &var1, const Variable &var2,
			const FactorClass &factorClass)
	{ return addFactor(getUniqueFactorId(), name, var1, var2, factorClass); }

	Factor &addFactor(const Variable &var1, const Variable &var2,
			const FactorClass &factorClass)
	{ return addFactor(getUniqueFactorId(), std::string(), var1, var2, factorClass); }


	// Accepting two variables & potentials
	Factor &addFactor(int id, std::string name, const Variable &var1, const Variable &var2,
			const cv::Mat &potentials);

	Factor &addFactor(int id, const Variable &var1, const Variable &var2,
			const cv::Mat &potentials)
	{ return addFactor(id, std::string(), var1, var2, potentials); }

	Factor &addFactor(std::string name, const Variable &var1, const Variable &var2,
			const cv::Mat &potentials)
	{ return addFactor(getUniqueFactorId(), name, var1, var2, potentials); }

	Factor &addFactor(const Variable &var1, const Variable &var2, const cv::Mat &potentials)
	{ return addFactor(getUniqueFactorId(), std::string(), var1, var2, potentials); }


public: // Variables

	Variable &addVariable(int id, std::string name, const VariableClass &varClass);

	Variable &addVariable(int id, const VariableClass &varClass)
	{ return addVariable(id, std::string(), varClass); }

	Variable &addVariable(std::string name, const VariableClass &varClass)
	{ return addVariable(getUniqueVariableId(), name, varClass); }

	Variable &addVariable(const VariableClass &varClass)
	{ return addVariable(getUniqueVariableId(), std::string(), varClass); }



	size_t variableCount() const
	{ return data()->vars.size(); }

	size_t factorCount() const
	{ return data()->factors.size(); }

	FactorIterator factorBegin()
	{ return data()->factors.begin(); }

	FactorIterator factorEnd()
	{ return data()->factors.end(); }

	ConstFactorIterator factorBegin() const
	{ return data()->factors.begin(); }

	ConstFactorIterator factorEnd() const
	{ return data()->factors.end(); }

	Factor &factorFirst()
	{ return data()->factors.front(); }

	Factor &factorLast()
	{ return data()->factors.back(); }

	VariableIterator variableBegin()
	{ return data()->vars.begin(); }

	VariableIterator variableEnd()
	{ return data()->vars.end(); }

	ConstVariableIterator variableBegin() const
	{ return data()->vars.begin(); }

	ConstVariableIterator variableEnd() const
	{ return data()->vars.end(); }

	Variable &variableFirst()
	{ return data()->vars.front(); }

	Variable &variableLast()
	{ return data()->vars.back(); }

	bool variableExists(int id) const
	{ return data()->mapVarId.find(id)!=data()->mapVarId.end(); }


private:

	int getUniqueVariableId()
	{
		return data()->maxVariableId+1;
	}

	int getUniqueFactorId()
	{
		return data()->maxFactorId+1;
	}

	Factor *verifyFactorIdAndName(int it, std::string name);

};


std::ostream& operator<<(std::ostream &out, const FactorGraph &fg);


}
}

#endif /* _ROCS_ML_FACTORGRAPH_H_ */
