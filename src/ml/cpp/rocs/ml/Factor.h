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

	FactorData(int id_, std::string name_, const FactorClass &factorClass_,
			const cv::Mat &potentials_):
		id(id_), name(name_), factorClass(factorClass_),
		potentials(potentials_)
	{}

	FactorData(int id_, std::string name_, const FactorClass &factorClass_,
			const std::vector<Variable> &vars_):
		id(id_), name(name_), factorClass(factorClass_), vars(vars_)
	{}

	FactorData(int id_, std::string name_, const FactorClass &factorClass_,
			const std::vector<Variable> &vars_, const cv::Mat &potentials_):
		id(id_), name(name_), factorClass(factorClass_),
		vars(vars_), potentials(potentials_)
	{}


	int id;
	std::string name;
	FactorClass factorClass;
	std::vector<Variable> vars;
	cv::Mat potentials;
};


class Factor: public core::ShallowCopyable<FactorData>
{
public:

	Factor(int id, std::string name, const FactorClass &factorClass,
		   const std::vector<Variable> &vars):
		SC(new FactorData(id, name, factorClass, vars))
	{}

	Factor(int id, const FactorClass &factorClass,
		   const std::vector<Variable> &vars):
		SC(new FactorData(id, std::string(), factorClass, vars))
	{}

	Factor(int id, std::string name, const FactorClass &factorClass,
		   const std::vector<Variable> &vars, const cv::Mat &potentials):
		SC(new FactorData(id, name, factorClass, vars, potentials))
	{}

	Factor(int id, const FactorClass &factorClass,
		   const std::vector<Variable> &vars, const cv::Mat &potentials):
		SC(new FactorData(id, std::string(), factorClass, vars, potentials))
	{}


	Factor(int id, std::string name, const FactorClass &factorClass,
		   const Variable &var):
		SC(new FactorData(id, name, factorClass))
	{
		data()->vars.push_back(var);
	}

	Factor(int id, const FactorClass &factorClass,
		   const Variable &var):
		SC(new FactorData(id, std::string(), factorClass))
	{
		data()->vars.push_back(var);
	}

	Factor(int id, std::string name, const FactorClass &factorClass,
		   const Variable &var, const cv::Mat &potentials):
		SC(new FactorData(id, name, factorClass, potentials))
	{
		data()->vars.push_back(var);
	}

	Factor(int id, const FactorClass &factorClass,
		   const Variable &var, const cv::Mat &potentials):
		SC(new FactorData(id, std::string(), factorClass, potentials))
	{
		data()->vars.push_back(var);
	}


	Factor(int id, std::string name, const FactorClass &factorClass,
		   const Variable &var1, const Variable &var2):
		SC(new FactorData(id, name, factorClass))
	{
		data()->vars.push_back(var1);
		data()->vars.push_back(var2);
	}

	Factor(int id, const FactorClass &factorClass,
		   const Variable &var1, const Variable &var2):
		SC(new FactorData(id, std::string(), factorClass))
	{
		data()->vars.push_back(var1);
		data()->vars.push_back(var2);
	}

	Factor(int id, std::string name, const FactorClass &factorClass,
		   const Variable &var1, const Variable &var2, const cv::Mat &potentials):
		SC(new FactorData(id, name, factorClass, potentials))
	{
		data()->vars.push_back(var1);
		data()->vars.push_back(var2);
	}

	Factor(int id, const FactorClass &factorClass,
		   const Variable &var1, const Variable &var2, const cv::Mat &potentials):
		SC(new FactorData(id, std::string(), factorClass, potentials))
	{
		data()->vars.push_back(var1);
		data()->vars.push_back(var2);
	}


	std::string name() const
	{ return data()->name; }

	int id() const
	{ return data()->id; }

	const FactorClass &factorClass()
	{ return data()->factorClass; }

	const cv::Mat &potentials()
	{ return data()->potentials; }

};



}
}


#endif /* _ROCS_ML_FACTOR_H_ */
