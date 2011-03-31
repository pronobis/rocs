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
 * \file Factor.h
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_ML_FACTOR_H_
#define _ROCS_ML_FACTOR_H_

#include "rocs/ml/FactorClass.h"
#include "rocs/ml/Variable.h"
#include <opencv2/core/core.hpp>

namespace rocs {
namespace ml {


struct FactorData
{
	FactorData(int id_, std::string name_, const FactorClass &factorClass_):
		id(id_), name(name_), factorClass(factorClass_)
	{}

	FactorData(int id_, std::string name_, const std::vector<Variable> &vars_,
			const FactorClass &factorClass_):
		id(id_), name(name_), vars(vars_), factorClass(factorClass_)
	{}

	int id;
	std::string name;
	std::vector<Variable> vars;
	FactorClass factorClass;
	size_t stateCount;
	bool hasClass;
};


/*!
 *
 */
class Factor: public core::ShallowCopyable<FactorData>
{
public:

	// Accepts variable vector & factor class
	Factor(int id, const std::vector<Variable> &vars,
			const FactorClass &factorClass):
		SC(new FactorData(id, std::string(), vars, factorClass))
	{
		// Check if the variables match the factor class
		rocsAssert(vars.size() == factorClass.variableClasses().size())
		for (size_t i=0; i<vars.size(); ++i)
			rocsAssert(vars[i].stateCount() == factorClass.variableClasses()[i].stateCount());

		calculateStateCount();
	}

	Factor(int id, std::string name, const std::vector<Variable> &vars,
		   const FactorClass &factorClass):
		SC(new FactorData(id, name, vars, factorClass))
	{
		// Check if the variables match the factor class
		rocsAssert(vars.size() == factorClass.variableClasses().size())
		for (size_t i=0; i<vars.size(); ++i)
			rocsAssert(vars[i].stateCount() == factorClass.variableClasses()[i].stateCount());

		calculateStateCount();
	}

	// Accepts variable vector & potentials - creates own class
	Factor(int id, const std::vector<Variable> &vars,
			const cv::Mat &potentials):
		SC(new FactorData(id, std::string(), vars,
				FactorClass(-1, extractClasses(vars), potentials)))
	{
		// Check if the variables match the factor class
		rocsAssert(potentials.type() == CV_64F);
		size_t potentialsDims = (potentials.size[0]>1)?static_cast<size_t>(potentials.dims):1;
		rocsAssert(vars.size() == potentialsDims);
		for (size_t i=0; i<vars.size(); ++i)
			rocsAssert(vars[i].stateCount() == static_cast<size_t>(potentials.size[i]));

		calculateStateCount();
	}

	Factor(int id, std::string name, const std::vector<Variable> &vars,
			const cv::Mat &potentials):
		SC(new FactorData(id, name, vars,
				FactorClass(-1, extractClasses(vars), potentials)))
	{
		// Check if the variables match the factor class
		rocsAssert(potentials.type() == CV_64F);
		size_t potentialsDims = (potentials.size[0]>1)?static_cast<size_t>(potentials.dims):1;
		rocsAssert(vars.size() == potentialsDims);
		for (size_t i=0; i<vars.size(); ++i)
			rocsAssert(vars[i].stateCount() == static_cast<size_t>(potentials.size[i]));

		calculateStateCount();
	}


	// Accepts single variable & factor class
	Factor(int id, const Variable &var,
			const FactorClass &factorClass):
		SC(new FactorData(id, std::string(), factorClass))
	{
		// Check if the variables match the factor class
		rocsAssert(factorClass.variableClasses().size() == 1)
		rocsAssert(var.stateCount() == factorClass.variableClasses()[0].stateCount());

		data()->vars.push_back(var);
		calculateStateCount();
	}

	Factor(int id, std::string name, const Variable &var,
			const FactorClass &factorClass):
		SC(new FactorData(id, name, factorClass))
	{
		// Check if the variables match the factor class
		rocsAssert(factorClass.variableClasses().size() == 1)
		rocsAssert(var.stateCount() == factorClass.variableClasses()[0].stateCount());

		data()->vars.push_back(var);
		calculateStateCount();
	}

	// Accepts single variable & potentials - own class
	Factor(int id, const Variable &var, const cv::Mat &potentials):
		SC(new FactorData(id, std::string(), FactorClass(-1, var.variableClass(), potentials)))
	{
		// Check if the variables match the factor class
		rocsAssert(potentials.type() == CV_64F);
		size_t potentialsDims = (potentials.size[0]>1)?static_cast<size_t>(potentials.dims):1;
		rocsAssert(potentialsDims == 1);
		rocsAssert(var.stateCount() == static_cast<size_t>(potentials.size[1]));

		data()->vars.push_back(var);
		calculateStateCount();
	}

	Factor(int id, std::string name, const Variable &var,
			const cv::Mat &potentials):
		SC(new FactorData(id, name, FactorClass(-1, var.variableClass(), potentials)))
	{
		// Check if the variables match the factor class
		rocsAssert(potentials.type() == CV_64F);
		size_t potentialsDims = (potentials.size[0]>1)?static_cast<size_t>(potentials.dims):1;
		rocsAssert(potentialsDims == 1);
		rocsAssert(var.stateCount() == static_cast<size_t>(potentials.size[1]));

		data()->vars.push_back(var);
		calculateStateCount();
	}


	// Accepts two variables & factor class
	Factor(int id, const Variable &var1, const Variable &var2,
			const FactorClass &factorClass ):
		SC(new FactorData(id, std::string(), factorClass))
	{
		// Check if the variables match the factor class
		rocsAssert(factorClass.variableClasses().size() == 2)
		rocsAssert(var1.stateCount() == factorClass.variableClasses()[0].stateCount());
		rocsAssert(var2.stateCount() == factorClass.variableClasses()[1].stateCount());

		data()->vars.push_back(var1);
		data()->vars.push_back(var2);
		calculateStateCount();
	}

	Factor(int id, std::string name, const Variable &var1, const Variable &var2,
			const FactorClass &factorClass):
		SC(new FactorData(id, name, factorClass))
	{
		// Check if the variables match the factor class
		rocsAssert(factorClass.variableClasses().size() == 2)
		rocsAssert(var1.stateCount() == factorClass.variableClasses()[0].stateCount());
		rocsAssert(var2.stateCount() == factorClass.variableClasses()[1].stateCount());

		data()->vars.push_back(var1);
		data()->vars.push_back(var2);
		calculateStateCount();
	}

	// Accepts two variables & potentials - own class
	Factor(int id, const Variable &var1, const Variable &var2,
			const cv::Mat &potentials):
		SC(new FactorData(id, std::string(), FactorClass(-1, extractClasses(var1, var2), potentials)))
	{
		// Check if the variables match the factor class
		rocsAssert(potentials.type() == CV_64F);
		size_t potentialsDims = (potentials.size[0]>1)?static_cast<size_t>(potentials.dims):1;
		rocsAssert(potentialsDims == 2);
		rocsAssert(var1.stateCount() == static_cast<size_t>(potentials.size[0]));
		rocsAssert(var2.stateCount() == static_cast<size_t>(potentials.size[1]));

		data()->vars.push_back(var1);
		data()->vars.push_back(var2);
		calculateStateCount();
	}

	Factor(int id, std::string name, const Variable &var1, const Variable &var2,
			const cv::Mat &potentials):
		SC(new FactorData(id, name, FactorClass(-1, extractClasses(var1, var2), potentials)))
	{
		// Check if the variables match the factor class
		rocsAssert(potentials.type() == CV_64F);
		size_t potentialsDims = (potentials.size[0]>1)?static_cast<size_t>(potentials.dims):1;
		rocsAssert(potentialsDims == 2);
		rocsAssert(var1.stateCount() == static_cast<size_t>(potentials.size[0]));
		rocsAssert(var2.stateCount() == static_cast<size_t>(potentials.size[1]));

		data()->vars.push_back(var1);
		data()->vars.push_back(var2);
		calculateStateCount();
	}



	std::string name() const
	{ return data()->name; }

	int id() const
	{ return data()->id; }

	const FactorClass &factorClass() const
	{ return data()->factorClass; }

	const cv::Mat &potentials() const
	{ return data()->factorClass.potentials(); }

	const std::vector<Variable> &variables() const
	{ return data()->vars; }

	size_t stateCount() const
	{ return data()->stateCount; }


private:

	void calculateStateCount()
	{
		size_t stateCount = 1;
		for(size_t i=0; i<data()->vars.size(); ++i)
			stateCount*=data()->vars[i].stateCount();
		data()->stateCount = stateCount;
	}

	std::vector<VariableClass> extractClasses(const std::vector<Variable> &vars) const
	{
		std::vector<VariableClass> vcs;
		for (size_t i=0; i<vars.size(); ++i)
			vcs.push_back(vars[i].variableClass());
		return vcs;
	}

	std::vector<VariableClass> extractClasses(const Variable &var1, const Variable &var2) const
	{
		std::vector<VariableClass> vcs;
		vcs.push_back(var1.variableClass());
		vcs.push_back(var2.variableClass());
		return vcs;
	}
};


std::ostream& operator<<(std::ostream &out, const Factor &f);


}
}


#endif /* _ROCS_ML_FACTOR_H_ */
