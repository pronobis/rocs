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
 * \file AxiomFactorClassGenerator.h
 */

#ifndef _ROCS_CONCEPT_AXIOMFACTORCLASSGENERATOR_H_
#define _ROCS_CONCEPT_AXIOMFACTORCLASSGENERATOR_H_

#include <stddef.h>

namespace rocs {

namespace ml{
	class FactorClassSet;
	class FactorClass;
	class VariableClass;
}

namespace concept {

/*!
 *
 */
class AxiomFactorClassGenerator
{

public:
	AxiomFactorClassGenerator(ml::VariableClass *onRelationVariableClass,
			ml::VariableClass *ontRelationVariableClass,
			ml::VariableClass *inRelationVariableClass,
			ml::FactorClassSet *fcs):
			_onRelationVariableClass(onRelationVariableClass),
			_ontRelationVariableClass(ontRelationVariableClass),
			_inRelationVariableClass(inRelationVariableClass),
			_fcs(fcs)
	{}

	~AxiomFactorClassGenerator()
	{}

	void generate(size_t inCount, size_t intCount, size_t onCount);


public:

	ml::FactorClass &supportAntisymmetricalFactorClass()
	{
		return *_supportAntisymmetricalFactorClass;
	}


private:

	ml::VariableClass *_onRelationVariableClass;
	ml::VariableClass *_ontRelationVariableClass;
	ml::VariableClass *_inRelationVariableClass;

	ml::FactorClassSet *_fcs;

	ml::FactorClass *_supportAntisymmetricalFactorClass;
	ml::FactorClass *_containmentAntisymmetricalFactorClass;
	ml::FactorClass *_supportImpliesTransitiveSupportFactorClass;
	ml::FactorClass *_supportTransitiveFactorClass;
	ml::FactorClass *_containmentTransitiveFactorClass;
	ml::FactorClass *_generousContainmentFactorClass;
	ml::FactorClass *_containmentSupportsFactorClass;
	ml::FactorClass *_directSupportRequiredFactorClass;;

};


}
}

#endif /* _ROCS_CONCEPT_AXIOMFACTORCLASSGENERATOR_H_ */



