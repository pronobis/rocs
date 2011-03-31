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
 * \file ObjectRelationGraphGenerator.cc
 */

#include "rocs/concept/ObjectRelationGraphGenerator.h"


#include "rocs/ml/FactorGraph.h"
#include "rocs/ml/FactorClassSet.h"
#include "rocs/ml/VariableClassSet.h"


namespace rocs {
namespace concept {

using namespace ml;

ObjectRelationGraphGenerator::ObjectRelationGraphGenerator(ml::FactorGraph *fg,
		ml::VariableClassSet *vcs, ml::FactorClassSet *fcs): _fg(fg), _vcs(vcs), _fcs(fcs),
		_ownVcs(false), _ownFcs(false)
{
	// Creating sets
	if (!_vcs)
	{
		_vcs = new VariableClassSet();
		_ownVcs = true;
	}
	if (!_fcs)
	{
		_fcs = new FactorClassSet();
		_ownFcs = true;
	}

	// Creating relation variable classes
	_onRelationVariableClass = &_vcs->addVariableClass(VVT_BOOL);
	_ontRelationVariableClass = &_vcs->addVariableClass(VVT_BOOL);
	_inRelationVariableClass = &_vcs->addVariableClass(VVT_BOOL);

	// Creating factor classes
	_axiomFactorGraphGenerator = boost::shared_ptr<AxiomFactorClassGenerator>(
			new AxiomFactorClassGenerator(_onRelationVariableClass,
			_ontRelationVariableClass, _inRelationVariableClass, _fcs));
	_axiomFactorGraphGenerator->generate();
}


ObjectRelationGraphGenerator::~ObjectRelationGraphGenerator()
{
	if (_ownVcs)
		delete _vcs;
	if (_ownFcs)
		delete _fcs;
}


void ObjectRelationGraphGenerator::createObjectRelationVariables()
{

}


void ObjectRelationGraphGenerator::createAxiomFactors()
{

}




}
}

