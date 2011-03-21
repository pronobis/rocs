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
 * \file FactorClass.h
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_ML_FACTORCLASS_H_
#define _ROCS_ML_FACTORCLASS_H_

#include "rocs/ml/VariableClass.h"
#include "rocs/core/ShallowCopyable.h"
#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

namespace rocs {
namespace ml {


/*! Internal data of the \ref FactorClass class. */
struct FactorClassData
{
	FactorClassData(int _id, const std::string &_name,
			const std::vector<VariableClass> &_varClasses, const cv::Mat &_potentials) :
		id(_id), name(_name), varClasses(_varClasses), potentials(_potentials)
	{}

	FactorClassData(int _id, const std::string &_name,
			const cv::Mat &_potentials) :
		id(_id), name(_name), potentials(_potentials)
	{}

	int id;
	std::string name;
	std::vector<VariableClass> varClasses;
	cv::Mat potentials;
};


/*!
 * @note This class uses the shallow copy mechanism (see \ref ShallowCopyable).
 */
class FactorClass : public core::ShallowCopyable<FactorClassData>
{
public:


	FactorClass(int id, std::vector<VariableClass> varClasses,
			    const cv::Mat &potentials) :
				SC(new FactorClassData(id, std::string(), varClasses, potentials))
	{}


	FactorClass(int id, std::string name, std::vector<VariableClass> varClasses,
		        const cv::Mat &potentials) :
		    	SC(new FactorClassData(id, name, varClasses, potentials))
	{}


	FactorClass(int id, std::string name, const VariableClass &varClass,
		        const cv::Mat &potentials) :
		    	SC(new FactorClassData(id, name, potentials))
	{
		data()->varClasses.push_back(varClass);
	}

	FactorClass(int id, std::string name, const VariableClass &varClass1,
			const VariableClass &varClass2, const cv::Mat &potentials) :
		    	SC(new FactorClassData(id, name, potentials))
	{
		data()->varClasses.push_back(varClass1);
		data()->varClasses.push_back(varClass2);
	}


	/*!
	 * Returns the name of the variable class.
	 * @return Name of the variable class.
	 */
	std::string name() const
	{ return data()->name; }


	/*!
	 * Returns the ID of the variable class.
	 * @return ID of the variable class.
	 */
	int id() const
	{ return data()->id; }


	const cv::Mat &potentials()
	{ return data()->potentials; }


	const std::vector<VariableClass> &variableClasses()
	{ return data()->varClasses; }

};


}
}

#endif /* _ROCS_ML_FACTORCLASS_H_ */
