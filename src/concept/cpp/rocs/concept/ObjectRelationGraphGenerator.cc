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
			if ((o1!=o2) && (!onExceptionMatches(o1, o2)))
			{
				Relation r;
				r.object1Id = o1;
				r.object2Id = o2;
				r.variable = &_fg->addVariable(r.object1Id+"-on-"+r.object2Id,*_onRelationVariableClass);
				_onRelations.push_back(r);
			}

			// Ont
			if ((o1!=o2) && (!ontExceptionMatches(o1, o2)))
			{
				Relation r;
				r.object1Id = o1;
				r.object2Id = o2;
				r.variable = &_fg->addVariable(r.object1Id+"-ont-"+r.object2Id,*_ontRelationVariableClass);
				_ontRelations.push_back(r);
			}

			// In
			if ((o1!=o2) && (!inExceptionMatches(o1, o2)))
			{
				Relation r;
				r.object1Id = o1;
				r.object2Id = o2;
				r.variable = &_fg->addVariable(r.object1Id+"-in-"+r.object2Id,*_inRelationVariableClass);
				_inRelations.push_back(r);
			}

		}
	}
}


void ObjectRelationGraphGenerator::createAxiomFactors()
{
	// Basic axioms
	// (3)
	for (size_t i=0; i<_ontRelations.size(); ++i)
	{
		Relation &r1 = _ontRelations[i];
		for (size_t j=i+1; j<_ontRelations.size(); ++j)
		{
			Relation &r2 = _ontRelations[j];
			if ((r1.object1Id == r2.object2Id) && (r1.object2Id== r2.object1Id))
			{
				_fg->addFactor("(3) "+r1.variable->name()+" "+r2.variable->name(),
						*r1.variable, *r2.variable, _axiomFactorGraphGenerator->supportAntisymmetricalFactorClass());
			}
		}
	}
	// (4)
	for (size_t i=0; i<_inRelations.size(); ++i)
	{
		Relation &r1 = _inRelations[i];
		for (size_t j=i+1; j<_inRelations.size(); ++j)
		{
			Relation &r2 = _inRelations[j];
			if ((r1.object1Id == r2.object2Id) && (r1.object2Id== r2.object1Id))
			{
				_fg->addFactor("(4) "+r1.variable->name()+" "+r2.variable->name(),
						*r1.variable, *r2.variable, _axiomFactorGraphGenerator->containmentAntisymmetricalFactorClass());
			}
		}
	}
	// Transitivity axioms
	// (5)
	for (size_t i=0; i<_onRelations.size(); ++i)
	{
		Relation &r1 = _onRelations[i];
		for (size_t j=0; j<_ontRelations.size(); ++j)
		{
			Relation &r2 = _ontRelations[j];
			if ((r1.object1Id == r2.object1Id) && (r1.object2Id== r2.object2Id))
			{
				_fg->addFactor("(5) "+r1.variable->name()+" "+r2.variable->name(),
						*r1.variable, *r2.variable, _axiomFactorGraphGenerator->supportImpliesTransitiveSupportFactorClass());
			}
		}
	}
	// (6)
	for (size_t i=0; i<_ontRelations.size(); ++i)
	{
		Relation &r1 = _ontRelations[i];
		for (size_t j=0; j<_ontRelations.size(); ++j)
		{
			Relation &r2 = _ontRelations[j];
			if (r1.object2Id == r2.object1Id)
			{
				vector<Variable> varVect;
				varVect.push_back(*r1.variable);
				varVect.push_back(*r2.variable);
				Relation *rel=findOntRelation(r1.object1Id, r2.object2Id);
				if (rel)
				{
					varVect.push_back(*rel->variable);

					_fg->addFactor("(6) "+r1.variable->name()+" "+r2.variable->name()+" "+rel->variable->name(),
							varVect, _axiomFactorGraphGenerator->supportTransitiveFactorClass());
				}
			}
		}
	}
	// (7)
	for (size_t i=0; i<_inRelations.size(); ++i)
	{
		Relation &r1 = _inRelations[i];
		for (size_t j=0; j<_inRelations.size(); ++j)
		{
			Relation &r2 = _inRelations[j];
			if (r1.object2Id == r2.object1Id)
			{
				vector<Variable> varVect;
				varVect.push_back(*r1.variable);
				varVect.push_back(*r2.variable);
				Relation *rel=findInRelation(r1.object1Id, r2.object2Id);
				if (rel)
				{
					varVect.push_back(*rel->variable);

					_fg->addFactor("(7) "+r1.variable->name()+" "+r2.variable->name()+" "+rel->variable->name(),
							varVect, _axiomFactorGraphGenerator->containmentTransitiveFactorClass());
				}
			}
		}
	}
	//  Interchangeability axioms
	// (8)
	for (size_t i=0; i<_ontRelations.size(); ++i)
	{
		Relation &r1 = _ontRelations[i];
		for (size_t j=0; j<_inRelations.size(); ++j)
		{
			Relation &r2 = _inRelations[j];
			if (r1.object2Id == r2.object1Id)
			{
				vector<Variable> varVect;
				varVect.push_back(*r1.variable);
				varVect.push_back(*r2.variable);
				Relation *rel=findInRelation(r1.object1Id, r2.object2Id);
				if (rel)
				{
					varVect.push_back(*rel->variable);

					_fg->addFactor("(8) "+r1.variable->name()+" "+r2.variable->name()+" "+rel->variable->name(),
							varVect, _axiomFactorGraphGenerator->generousContainmentFactorClass());
				}
			}
		}
	}
	// (9)
	for (size_t i=0; i<_inRelations.size(); ++i)
	{
		Relation &r1 = _inRelations[i];
		for (size_t j=0; j<_ontRelations.size(); ++j)
		{
			Relation &r2 = _ontRelations[j];
			if (r1.object2Id == r2.object1Id)
			{
				vector<Variable> varVect;
				varVect.push_back(*r1.variable);
				varVect.push_back(*r2.variable);
				Relation *rel =findOntRelation(r1.object1Id, r2.object2Id);
				if (rel)
				{
					varVect.push_back(*rel->variable);

					_fg->addFactor("(9) "+r1.variable->name()+" "+r2.variable->name()+" "+rel->variable->name(),
							varVect, _axiomFactorGraphGenerator->containmentSupportsFactorClass());
				}
			}
		}
	}
	// (10)





/*
	for (size_t i=0; i<_ontRelations.size(); ++i)
	{
		Relation &rOnt1 = _ontRelations[i];
		Relation *rOn1 = findOnRelation(rOnt1.object1Id, rOnt1.object2Id);
		Relation *rIn1 = findInRelation(rOnt1.object1Id, rOnt1.object2Id);

		for (size_t k=0; k<)

	}






	for (size_t i=0; i<_inRelations.size(); ++i)
	{
		Relation &r1 = _inRelations[i];
		for (size_t j=0; j<_ontRelations.size(); ++j)
		{
			Relation &r2 = _ontRelations[j];
			if (r1.object2Id == r2.object1Id)
			{
				vector<Variable> varVect;
				varVect.push_back(*r1.variable);
				varVect.push_back(*r2.variable);
				varVect.push_back(*(findOntRelation(r1.object1Id, r2.object2Id)->variable));

				_fg->addFactor(varVect, _axiomFactorGraphGenerator->containmentSupportsFactorClass());
			}
		}
	}


*/









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
				cv::Mat potentials(1, 2, CV_64F);
				potentials.at<double>(0) = 1-ro.value;
				potentials.at<double>(1) = ro.value;
				_fg->addFactor(ro.object1Id+"-on-"+ro.object2Id+" observation", *r->variable, potentials);
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
				cv::Mat potentials(1, 2, CV_64F);
				potentials.at<double>(0) = 1-ro.value;
				potentials.at<double>(1) = ro.value;
				_fg->addFactor(ro.object1Id+"-ont-"+ro.object2Id+" observation", *r->variable, potentials);
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
				cv::Mat potentials(1, 2, CV_64F);
				potentials.at<double>(0) = 1-ro.value;
				potentials.at<double>(1) = ro.value;
				_fg->addFactor(ro.object1Id+"-in-"+ro.object2Id+" observation", *r->variable, potentials);
			}
		}
	}
}



}
}

