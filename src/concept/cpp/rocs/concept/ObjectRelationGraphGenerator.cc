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
using namespace std;


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
	_onRelationVariableClass = &_vcs->addVariableClass("on-relation", VVT_BOOL);
	_ontRelationVariableClass = &_vcs->addVariableClass("ont-relation", VVT_BOOL);
	_inRelationVariableClass = &_vcs->addVariableClass("in-relation", VVT_BOOL);

	// Creating factor classes
	_axiomFactorGraphGenerator = boost::shared_ptr<AxiomFactorClassGenerator>(
			new AxiomFactorClassGenerator(_onRelationVariableClass,
			_ontRelationVariableClass, _inRelationVariableClass, _fcs));
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
	// There is a relation for every pair of objects, unless an exception is added
	for (size_t i=0; i<_objects.size(); ++i)
	{
		for (size_t j=0; j<_objects.size(); ++j)
		{
			string &o1 = _objects[i];
			string &o2 = _objects[j];

			// On
			if (!onExceptionMatches(o1, o2))
			{
				Relation r;
				r.object1Id = o1;
				r.object2Id = o2;
				r.variable = &_fg->addVariable(*_onRelationVariableClass);
				_onRelations.push_back(r);
			}

			// Ont
			if (!ontExceptionMatches(o1, o2))
			{
				Relation r;
				r.object1Id = o1;
				r.object2Id = o2;
				r.variable = &_fg->addVariable(*_ontRelationVariableClass);
				_ontRelations.push_back(r);
			}

			// In
			if (!inExceptionMatches(o1, o2))
			{
				Relation r;
				r.object1Id = o1;
				r.object2Id = o2;
				r.variable = &_fg->addVariable(*_inRelationVariableClass);
				_inRelations.push_back(r);
			}

		}
	}
}


void ObjectRelationGraphGenerator::createAxiomFactors()
{
	// We go through all the relation variables and create all proper factors.

}


void ObjectRelationGraphGenerator::createObservationFactors()
{
	// There is a factor for every observation, unless an exception is added
	// On
	for(size_t i=0; i<_onRelationObservations.size(); ++i)
	{
		RelationObservation &ro = _onRelationObservations[i];

		// On
		if (!onExceptionMatches(ro))
		{
			Relation *r = findOnRelation(ro.object1Id, ro.object2Id);
			if (r)
			{
				double p[2] = {1-ro.value, ro.value};
				cv::Mat potentials(2, 0, CV_64F, p);
				_fg->addFactor(*r->variable, potentials);
			}
		}
	}

	// Ont
	for(size_t i=0; i<_ontRelationObservations.size(); ++i)
	{
		RelationObservation &ro = _ontRelationObservations[i];
		// Ont
		if (!ontExceptionMatches(ro))
		{
			Relation *r = findOntRelation(ro.object1Id, ro.object2Id);
			if (r)
			{
				double p[2] = {1-ro.value, ro.value};
				cv::Mat potentials(2, 0, CV_64F, p);
				_fg->addFactor(*r->variable, potentials);
			}
		}
	}

	for(size_t i=0; i<_inRelationObservations.size(); ++i)
	{
		RelationObservation &ro = _inRelationObservations[i];
		// In
		if (!inExceptionMatches(ro))
		{
			Relation *r = findInRelation(ro.object1Id, ro.object2Id);
			if (r)
			{
				double p[2] = {1-ro.value, ro.value};
				cv::Mat potentials(2, 0, CV_64F, p);
				_fg->addFactor(*r->variable, potentials);
			}
		}
	}
}



}
}

