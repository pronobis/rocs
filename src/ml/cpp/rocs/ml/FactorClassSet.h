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
 * \file FactorClassSet.h
 *
 * \date Mar 20, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_ML_FACTORCLASSSET_H_
#define _ROCS_ML_FACTORCLASSSET_H_

#include "rocs/ml/FactorClass.h"
#include "rocs/core/ShallowCopyable.h"
#include <list>
#include <map>

namespace rocs {
namespace ml {


/*! Internal data of the @ref FactorClassSet class. */
struct FactorClassSetData
{
	FactorClassSetData() : maxId(0)
	{}

	/*! List of classes added to the set. */
	std::list<FactorClass> classes;

	std::map<int, FactorClass *> mapId;
	std::map<std::string, FactorClass *> mapName;

	/*! The largest Id added so far. */
	int maxId;
};


/*!
 * Factor class set class. Stores and creates factor classes.
 * @note This class uses the shallow copy mechanism (see \ref ShallowCopyable).
 */
class FactorClassSet : public core::ShallowCopyable<FactorClassSetData>
{
public:

	typedef std::list<FactorClass>::iterator Iterator;


public:

	/*! Constructor, creates an empty set. */
	FactorClassSet() : SC(new FactorClassSetData())
	{}

	/*!
	 * Creates a factor class with the given ID and name and adds it
	 * to the set if a class with this name and ID does not exist yet.
	 * If a class with this name and ID exists already, nothing is
	 * created and a reference to the class is returned. If an ID
	 * exists but not the name, or the opposite, the function throws
	 * @ref UniquenessException. If an empty name is given, the
	 * function ignores it.
	 * @param id ID of the factor class
	 * @param name Name of the factor class
	 * @return Reference to the factor class
	 * @throw UniquenessException
	 */
	FactorClass &addFactorClass(int id, std::string name,
			const std::vector<VariableClass> &varClasses, const cv::Mat &potentials);

	FactorClass &addFactorClass(int id, std::string name,
			const VariableClass &varClass, const cv::Mat &potentials);

	FactorClass &addFactorClass(int id, std::string name,
			const VariableClass &varClass1, const VariableClass &varClass2,
			const cv::Mat &potentials);

	/*!
	 * Creates a factor class with a unique ID and the given name and adds
	 * it to the set if a class with this name does not exist yet. If a class
	 * with this name already exists, nothing is created and a reference
	 * to the class is returned. If an empty name is given, the function
	 * ignores it.
	 * @param name Name of the factor class
	 * @return Reference to the factor class
	 */
	FactorClass &addFactorClass(std::string name,
			const std::vector<VariableClass> &varClasses, const cv::Mat &potentials)
	{ return addFactorClass(getUniqueId(), name, varClasses, potentials); }

	/*!
	 * Creates a factor class with the given ID and adds it to the set if
	 * a class with this ID does not exist yet. If a class with this ID
	 * already exists, nothing is created and a reference to the class is
	 * returned. The function assigns an empty name to the class.
	 * @param id ID of the factor class
	 * @return Reference to the factor class
	 */
	FactorClass &addFactorClass(int id,
			const std::vector<VariableClass> &varClasses, const cv::Mat &potentials)
	{ return addFactorClass(id, std::string(), varClasses, potentials); }

	/*!
	 * Creates a factor class with a unique ID and adds it to the set.
	 * The function assigns an empty name to the class.
	 * @return Reference to the newly created and added factor class
	 */
	FactorClass &addFactorClass(const std::vector<VariableClass> &varClasses, const cv::Mat &potentials)
	{ return addFactorClass(getUniqueId(), std::string(), varClasses, potentials); }

	FactorClass &addFactorClass(const VariableClass &varClass, const cv::Mat &potentials)
	{ return addFactorClass(getUniqueId(), std::string(), varClass, potentials); }

	FactorClass &addFactorClass(const VariableClass &varClass1, const VariableClass &varClass2,
			const cv::Mat &potentials)
	{ return addFactorClass(getUniqueId(), std::string(), varClass1, varClass2, potentials); }


	/*!
	 * Returns the number of factor classes in the set.
	 * @return The number of factor classes in the set.
	 */
	size_t count() const
	{ return data()->classes.size(); }

	Iterator begin()
	{ return data()->classes.begin(); }

	Iterator end()
	{ return data()->classes.end(); }

	FactorClass &first()
	{ return data()->classes.front(); }

	FactorClass &last()
	{ return data()->classes.back(); }


private:

	int getUniqueId()
	{
		return data()->maxId+1;
	}

};

}
}

#endif /* _ROCS_ML_FACTORCLASSSET_H_ */
