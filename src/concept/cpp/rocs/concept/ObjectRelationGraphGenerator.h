// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2011  Andrzej Pronobis, Kristoffer Sjöo
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
 *
 *
 * \author Andrzej Pronobis, Kristoffer Sjöo
 * \file ObjectRelationGraphGenerator.h
 */

#ifndef _ROCS_CONCEPT_OBJECTRELATIONGRAPHGENERATOR_H_
#define _ROCS_CONCEPT_OBJECTRELATIONGRAPHGENERATOR_H_

#include <rocs/concept/AxiomFactorClassGenerator.h>
#include <boost/shared_ptr.hpp>


namespace rocs {

namespace ml{
	class FactorGraph;
	class VariableClassSet;
	class FactorClassSet;
	class VariableClass;
	class FactorClass;
}

namespace concept {


/*!
 *
 */
class ObjectRelationGraphGenerator
{

public:
	ObjectRelationGraphGenerator(ml::FactorGraph *fg, ml::VariableClassSet *vcs = 0,
			ml::FactorClassSet *fcs = 0);
	~ObjectRelationGraphGenerator();


	void generate()
	{
		createObjectRelationVariables();
		createAxiomFactors();
	}


private:

	void createObjectRelationVariables();
	void createAxiomFactors();


private:

	ml::FactorGraph *_fg;
	ml::VariableClassSet *_vcs;
	ml::FactorClassSet *_fcs;
	bool _ownVcs;
	bool _ownFcs;

	ml::VariableClass *_onRelationVariableClass;
	ml::VariableClass *_ontRelationVariableClass;
	ml::VariableClass *_inRelationVariableClass;

	boost::shared_ptr<AxiomFactorClassGenerator> _axiomFactorGraphGenerator;
};


}
}

#endif /* _ROCS_CONCEPT_OBJECTRELATIONGRAPHGENERATOR_H_ */



