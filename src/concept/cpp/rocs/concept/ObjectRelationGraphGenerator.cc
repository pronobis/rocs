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
#include <set>
#include <boost/scoped_ptr.hpp>

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

//Given: list of zs
//Given: map from z to ONt(zn,y) ID
//Given: map from z to ON(x,zn) ID
//Given: map from z to IN(x,zn) ID

void recurseSupportRequirement_In(cv::Mat &potentials, 
    bool dontcare,
    map<string, int> &Ont_zmap, 
    map<string, int> &On_zmap, 
    map<string, int> &In_zmap,
    int *indices,
    set<string> &zVals,
    set<string>::iterator zIt);
void recurseSupportRequirement_On(cv::Mat &potentials, 
    bool dontcare,
    map<string, int> &Ont_zmap, 
    map<string, int> &On_zmap, 
    map<string, int> &In_zmap,
    int *indices,
    set<string> &zVals,
    set<string>::iterator zIt);
void recurseSupportRequirement_Ont(cv::Mat &potentials, 
    map<string, int> &Ont_zmap, 
    map<string, int> &On_zmap, 
    map<string, int> &In_zmap,
    int *indices,
    set<string> &zVals,
    set<string>::iterator zIt)
{
  if (zIt == zVals.end()) {
    potentials.at<double>(indices) = 0;
  }
  else if (Ont_zmap.count(*zIt) > 0) {
    // If there is an ONt(z,y) relation
    int index = Ont_zmap[*zIt];
    indices[index] = 0; //Set it to false
    // Go on to vary ON(x,zn), with don't-care
    recurseSupportRequirement_On(potentials, true,
	Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);

    // Now set it ONt(z,y) to true,
    indices[index] = 1;
    // Go on to vary ON(x,zn), without don't-care
    recurseSupportRequirement_On(potentials, false,
	Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
  }
  else {
    // No ONt(z,y) relation exists
    // Don't set any index, but recurse as if it had been 0
    // Go on to vary ON(x,zn), with don't-care
    recurseSupportRequirement_On(potentials, true,
	Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
  }
}

void recurseSupportRequirement_On(cv::Mat &potentials, 
    bool dontcare,
    map<string, int> &Ont_zmap, 
    map<string, int> &On_zmap, 
    map<string, int> &In_zmap,
    int *indices,
    set<string> &zVals,
    set<string>::iterator zIt)
{
  if (On_zmap.count(*zIt) > 0) {
    // If there is an ON(x,z) relation
    int index = On_zmap[*zIt];

    if (dontcare) {
      // Doesn't matter what the value is; recurse for both 0 and 1
      indices[index] = 0;
      recurseSupportRequirement_In(potentials, true,
	  Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
      indices[index] = 1;
      recurseSupportRequirement_In(potentials, true,
	  Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
    }
    else {
      // We care about the value of ON(x,z) and IN(x,z). They must both be 0
      // or this state is not forbidden.
      indices[index] = 0; //Set it to false
      // Go on to vary ON(x,zn), without don't-care
      recurseSupportRequirement_In(potentials, true,
	  Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
    }
  }
  else {
    // No relation exists; recurse but set no index
    recurseSupportRequirement_In(potentials, dontcare,
	Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
  }
}

void recurseSupportRequirement_In(cv::Mat &potentials, 
    bool dontcare,
    map<string, int> &Ont_zmap, 
    map<string, int> &On_zmap, 
    map<string, int> &In_zmap,
    int *indices,
    set<string> &zVals,
    set<string>::iterator zIt)
{
  if (In_zmap.count(*zIt) > 0) {
    // If there is an IN(z,y) relation
    int index = In_zmap[*zIt];

    if (dontcare) {
      // Doesn't matter what the value is; recurse for both 0 and 1
      indices[index] = 0;
      // Go on to vary the next z
      zIt++;
      recurseSupportRequirement_Ont(potentials,
	  Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
      indices[index] = 1;
      recurseSupportRequirement_Ont(potentials, 
	  Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
    }
    else {
      // We care about the value of IN(x,z). It must be 0
      // or this state is not forbidden.
      indices[index] = 0; //Set it to false
      // Go on to vary the next z
      zIt++;
      recurseSupportRequirement_Ont(potentials,
	  Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
    }
  }
  else {
    // No relation exists; recurse but set no index
    zIt++;
    recurseSupportRequirement_Ont(potentials, 
	Ont_zmap, On_zmap, In_zmap, indices, zVals, zIt);
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




//void recurseSupportRequirement(cv::Mat &potentials, int *indices, int depth, int maxDepth)
//{
//  if (depth > maxDepth) {
//    potentials.at<double>(indices) = 0;
//  }
//  else {
//    // If there is a ONt(z,y) relation,
//    // 
//    
//    if (
//    //Case: ~ONt(z,y)
//    indices[depth*3] = 0;  	//~ONt(zn,y)
//    
//
//    indices[depth*3+1] = 0;    	//~ON(x,zn)
//    indices[depth*3+2] = 0;  	//~IN(x,zn)
//    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);
//    indices[depth*3+1] = 1;    	//ON(x,zn)
//    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);
//    indices[depth*3+1] = 0;    	//~ON(x,zn)
//    indices[depth*3+2] = 1;  	//IN(x,zn)
//    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);
//    indices[depth*3+1] = 1;    	//ON(x,zn)
//    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);
//
//    // ONt(z,y) and ~ON(x,z) and ~IN(x,z)) (case when ~ONt(z,y) already covered above)
//    indices[depth*3] = 1;
//    indices[depth*3+1] = 0;
//    indices[depth*3+2] = 0;
//    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);
//  }
//}

	// (10)
	// ONt(x,y)
	for (size_t i=0; i<_ontRelations.size(); ++i)
	{
	  Relation &rOnt1 = _ontRelations[i];
	  Relation *rOn1 = findOnRelation(rOnt1.object1Id, rOnt1.object2Id);
//	  Relation *rIn1 = findInRelation(rOnt1.object1Id, rOnt1.object2Id);
	  const string & x = rOnt1.object1Id;
	  const string & y = rOnt1.object2Id;

	  int inCount = _inRelations.size();
	  int onCount = _onRelations.size();
	  int ontCount = _ontRelations.size();
	  int dimensions = inCount + ontCount + onCount;
	  boost::scoped_ptr<int> sizes(new int[dimensions]);
	  boost::scoped_ptr<int> indices(new int[dimensions]);
	  for (int i = 0; i < dimensions; i++) {
	    sizes.get()[i] = 2;
	  }

	  vector<Variable> varVect;
	  varVect.push_back(*rOnt1.variable);
	  varVect.push_back(*rOn1->variable);
//	  varVect.push_back(*rIn1->variable);

	  // Maps from z object ID to the index number 
	  map<string, int> Ont_zmap;
	  map<string, int> On_zmap;
	  map<string, int> In_zmap;

	  // Look for all ONt(z,y)
	  int variableIndex = varVect.size();
	  set<string> zVals;
	  for (int i = 0; i < ontCount; i++) {
	    if (_ontRelations[i].object2Id == y &&
		_ontRelations[i].object1Id != x) {
	      string z = _ontRelations[i].object1Id;
	      zVals.insert(z);
	      Ont_zmap[z] = variableIndex;
	      varVect.push_back(*_ontRelations[i].variable);
	      variableIndex++;
	    }
	  }
	  // Look for all ON(x,z)
	  for (int i = 0; i < onCount; i++) {
	    if (_onRelations[i].object1Id == x &&
		_onRelations[i].object2Id != y) {
	      string z = _onRelations[i].object2Id;
	      zVals.insert(z);
	      On_zmap[z] = variableIndex;
	      varVect.push_back(*_onRelations[i].variable);
	      variableIndex++;
	    }
	  }
	  // Look for all IN(x,z)
	  for (int i = 0; i < inCount; i++) {
	    if (_inRelations[i].object1Id == x &&
		_inRelations[i].object2Id != y) {
	      string z = _inRelations[i].object2Id;
	      zVals.insert(z);
	      In_zmap[z] = variableIndex;
	      varVect.push_back(*_inRelations[i].variable);
	      variableIndex++;
	    }
	  }

	  cv::Mat directSupportRequiredPotentials(varVect.size(), sizes.get(), CV_64F);
	  directSupportRequiredPotentials.setTo(1);

	  indices.get()[0] = 1; //ONt(x,y)
	  indices.get()[1] = 0; //~ON(x,y)
//	  indices.get()[2] = 0; //~IN(x,y)
	  recurseSupportRequirement_Ont(directSupportRequiredPotentials,
	      Ont_zmap, On_zmap, In_zmap,
	      indices.get(), zVals, zVals.begin());
//	  indices.get()[2] = 1; //~IN(x,y)
//	  recurseSupportRequirement_Ont(directSupportRequiredPotentials,
//	      Ont_zmap, On_zmap, In_zmap,
//	      indices.get(), zVals, zVals.begin());

	  stringstream s;
	  for (size_t i=0; i<varVect.size(); ++i)
		  s<<varVect[i].name()<<" ";
	  _fg->addFactor("(10) "+s.str(),
			  varVect, directSupportRequiredPotentials);
	}

	// (11)
	for (size_t i=0; i<_objects.size(); ++i)
	{
		vector<Variable> varVect;
		vector<int> indices;

		string &xobject = _objects[i];
		for(size_t k=0; k<_ontRelations.size(); ++k)
		{
			if (_ontRelations[k].object1Id == xobject)
			{
				varVect.push_back(*_ontRelations[k].variable);
				indices.push_back(0);
			}
		}
		for(size_t k=0; k<_inRelations.size(); ++k)
		{
			if (_inRelations[k].object1Id == xobject)
			{
				varVect.push_back(*_inRelations[k].variable);
				indices.push_back(0);
			}
		}

		if (!varVect.empty())
		{
			boost::scoped_ptr<int> sizes(new int[varVect.size()]);
			boost::scoped_ptr<int> _indices(new int[varVect.size()]);
			for (size_t k=0; k<varVect.size(); ++k)
			{
				sizes.get()[k]=2;
				_indices.get()[k]=indices[k];
			}
			cv::Mat supportRequiredPotentials(varVect.size(), sizes.get(), CV_64F);
			supportRequiredPotentials.setTo(1);
			supportRequiredPotentials.at<double>(_indices.get()) = 0;

			  stringstream s;
			  for (size_t i=0; i<varVect.size(); ++i)
				  s<<varVect[i].name()<<" ";
			_fg->addFactor("(11) "+s.str(),
					varVect, supportRequiredPotentials);
		}
	}

	// (12)
	for (size_t i=0; i<_onRelations.size(); ++i)
	{
		Relation &r1 = _onRelations[i];
		for (size_t j=0; j<_onRelations.size(); ++j)
		{
			Relation &r2 = _onRelations[j];
			if ((r1.object1Id == r2.object1Id) && (r1.object2Id != r2.object2Id))
			{
				_fg->addFactor("(12) "+r1.variable->name()+" "+r2.variable->name(),
						*r1.variable, *r2.variable, _axiomFactorGraphGenerator->uniqueSupportFactorClass());
			}
		}
	}

	// (13)
	for (size_t i=0; i<_ontRelations.size(); ++i)
	{
		Relation &r1 = _ontRelations[i];
		for (size_t j=0; j<_ontRelations.size(); ++j)
		{
			Relation &r2 = _ontRelations[j];
			if ((r1.object1Id == r2.object1Id) && ((r1.object2Id != r2.object2Id) ))
			{
				vector<Variable> varVect;
				varVect.push_back(*r1.variable);
				varVect.push_back(*r2.variable);
				Relation *rel1 =findOntRelation(r1.object2Id, r2.object2Id);
				Relation *rel2 =findOntRelation(r2.object2Id, r1.object2Id);

				if (rel1&&rel2)
				{
					varVect.push_back(*rel1->variable);
					varVect.push_back(*rel2->variable);

					_fg->addFactor("(13) "+r1.variable->name()+" "+r2.variable->name()+" "+rel1->variable->name()+" "+rel2->variable->name(),
							varVect, _axiomFactorGraphGenerator->uniqueTransitiveSupportFactorClass());
				} else if (rel1 || rel2)
				{
					Variable *var = (rel1)?rel1->variable:rel2->variable;
					varVect.push_back(*var);
					int sizes[] = {2,2,2};
					cv::Mat potentials(3, sizes, CV_64F);
					potentials.setTo(1);
				    int indices[] = {1,1,0}; //Forbid true, true, false
					potentials.at<double>(indices) = 0;

					_fg->addFactor("(13) "+r1.variable->name()+" "+r2.variable->name()+" "+var->name(),
							varVect, potentials);
				}
				else
				{
					int sizes[] = {2,2};
					cv::Mat potentials(2, sizes, CV_64F);
					potentials.setTo(1);
				    int indices[] = {1,1}; //Forbid true, true
					potentials.at<double>(indices) = 0;

					_fg->addFactor("(13) "+r1.variable->name()+" "+r2.variable->name(),
							varVect, potentials);
				}
			}
		}
	}


	// (14)
	for (size_t i=0; i<_inRelations.size(); ++i)
	{
		Relation &r1 = _inRelations[i];
		for (size_t j=0; j<_inRelations.size(); ++j)
		{
			Relation &r2 = _inRelations[j];
			if ((r1.object1Id == r2.object1Id) && ((r1.object2Id != r2.object2Id) ))
			{
				vector<Variable> varVect;
				varVect.push_back(*r1.variable);
				varVect.push_back(*r2.variable);
				Relation *rel1 =findInRelation(r1.object2Id, r2.object2Id);
				Relation *rel2 =findInRelation(r2.object2Id, r1.object2Id);

				if (rel1&&rel2)
				{
					varVect.push_back(*rel1->variable);
					varVect.push_back(*rel2->variable);

					_fg->addFactor("(14) "+r1.variable->name()+" "+r2.variable->name()+" "+rel1->variable->name()+" "+rel2->variable->name(),
							varVect, _axiomFactorGraphGenerator->uniqueInnessFactorClass());
				} else if (rel1 || rel2)
				{
					Variable *var = (rel1)?rel1->variable:rel2->variable;
					varVect.push_back(*var);
					int sizes[] = {2,2,2};
					cv::Mat potentials(3, sizes, CV_64F);
					potentials.setTo(1);
				    int indices[] = {1,1,0}; //Forbid true, true, false
					potentials.at<double>(indices) = 0;

					_fg->addFactor("(14) "+r1.variable->name()+" "+r2.variable->name()+" "+var->name(),
							varVect, potentials);
				}
				else
				{
					int sizes[] = {2,2};
					cv::Mat potentials(2, sizes, CV_64F);
					potentials.setTo(1);
				    int indices[] = {1,1}; //Forbid true, true
					potentials.at<double>(indices) = 0;

					_fg->addFactor("(14) "+r1.variable->name()+" "+r2.variable->name(),
							varVect, potentials);
				}
			}
		}
	}


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

