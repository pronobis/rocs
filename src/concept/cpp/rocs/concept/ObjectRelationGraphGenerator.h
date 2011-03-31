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
#include <rocs/ml/Variable.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

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
	struct RelationObservation
	{
		RelationObservation(const std::string &object1Id_, const std::string &object2Id_, double value_):
			object1Id(object1Id_), object2Id(object2Id_), value(value_)
		{}

		std::string object1Id;
		std::string object2Id;
		double value;
	};

	struct RelationException
	{
		RelationException(const std::string &object1Id_, const std::string &object2Id_):
			object1Id(object1Id_), object2Id(object2Id_)
		{}

		std::string object1Id;
		std::string object2Id;

		bool matches(const std::string &object1Id_, const std::string &object2Id_)
		{
			return ( ((object1Id.empty()) || (object1Id == object1Id_))
				    & ((object2Id.empty()) || (object2Id == object2Id_)) );
		}

		bool matches(const RelationObservation &ro)
		{
			return ( ((object1Id.empty()) || (object1Id == ro.object1Id))
				    & ((object2Id.empty()) || (object2Id == ro.object2Id)) );
		}
	};


public:

	struct Relation
	{
		std::string object1Id;
		std::string object2Id;

		ml::Variable *variable;
	};


public:
	ObjectRelationGraphGenerator(ml::FactorGraph *fg, ml::VariableClassSet *vcs = 0,
			ml::FactorClassSet *fcs = 0);
	~ObjectRelationGraphGenerator();


	void generate()
	{
		createObjectRelationVariables();
		_axiomFactorGraphGenerator->generate(_inRelations.size(), _ontRelations.size(), _onRelations.size());
		createAxiomFactors();
		createObservationFactors();
	}

	void addObject(std::string id)
	{
		_objects.push_back(id);
	}

	void addInRelationObservation(const std::string &object1Id, const std::string &object2Id, double value)
	{
		_inRelationObservations.push_back(RelationObservation(object1Id, object2Id, value));
	}

	void addOntRelationObservation(const std::string &object1Id, const std::string &object2Id, double value)
	{
		_ontRelationObservations.push_back(RelationObservation(object1Id, object2Id, value));
	}

	void addOnRelationObservation(const std::string &object1Id, const std::string &object2Id, double value)
	{
		_onRelationObservations.push_back(RelationObservation(object1Id, object2Id, value));
	}

	/*!
	 * Empty string matches every object.
	 * @param object1Id
	 * @param object2Id
	 */
	void addInRelationException(const std::string &object1Id, const std::string &object2Id)
	{
		_inRelationExceptions.push_back(RelationException(object1Id, object2Id));
	}

	/*!
	 * Empty string matches every object.
	 * @param object1Id
	 * @param object2Id
	 */
	void addOntRelationException(const std::string &object1Id, const std::string &object2Id)
	{
		_ontRelationExceptions.push_back(RelationException(object1Id, object2Id));
	}

	/*!
	 * Empty string matches every object.
	 * @param object1Id
	 * @param object2Id
	 */
	void addOnRelationException(const std::string &object1Id, const std::string &object2Id)
	{
		_onRelationExceptions.push_back(RelationException(object1Id, object2Id));
	}


private:

	void createObjectRelationVariables();
	void createAxiomFactors();
	void createObservationFactors();

	bool onExceptionMatches(const std::string &object1Id, const std::string &object2Id)
	{
		for (size_t e=0; e<_onRelationExceptions.size(); ++e)
		{
			if (_onRelationExceptions[e].matches(object1Id, object2Id))
				return true;
		}
		return false;
	}

	bool ontExceptionMatches(const std::string &object1Id, const std::string &object2Id)
	{
		for (size_t e=0; e<_ontRelationExceptions.size(); ++e)
		{
			if (_ontRelationExceptions[e].matches(object1Id, object2Id))
				return true;
		}
		return false;
	}

	bool inExceptionMatches(const std::string &object1Id, const std::string &object2Id)
	{
		for (size_t e=0; e<_inRelationExceptions.size(); ++e)
		{
			if (_inRelationExceptions[e].matches(object1Id, object2Id))
				return true;
		}
		return false;
	}



	bool onExceptionMatches(const RelationObservation &ro)
	{
		for (size_t e=0; e<_onRelationExceptions.size(); ++e)
		{
			if (_onRelationExceptions[e].matches(ro))
				return true;
		}
		return false;
	}

	bool ontExceptionMatches(const RelationObservation &ro)
	{
		for (size_t e=0; e<_ontRelationExceptions.size(); ++e)
		{
			if (_ontRelationExceptions[e].matches(ro))
				return true;
		}
		return false;
	}

	bool inExceptionMatches(const RelationObservation &ro)
	{
		for (size_t e=0; e<_inRelationExceptions.size(); ++e)
		{
			if (_inRelationExceptions[e].matches(ro))
				return true;
		}
		return false;
	}

	Relation *findOnRelation(const std::string &object1Id, const std::string &object2Id)
	{
		for (size_t i=0; i<_onRelations.size(); ++i)
		{
			if ((_onRelations[i].object1Id == object1Id) && (_onRelations[i].object2Id == object2Id))
				return &_onRelations[i];
		}
		return 0;
	}

	Relation *findInRelation(const std::string &object1Id, const std::string &object2Id)
	{
		for (size_t i=0; i<_inRelations.size(); ++i)
		{
			if ((_inRelations[i].object1Id == object1Id) && (_inRelations[i].object2Id == object2Id))
				return &_inRelations[i];
		}
		return 0;
	}

	Relation *findOntRelation(const std::string &object1Id, const std::string &object2Id)
	{
		for (size_t i=0; i<_ontRelations.size(); ++i)
		{
			if ((_ontRelations[i].object1Id == object1Id) && (_ontRelations[i].object2Id == object2Id))
				return &_ontRelations[i];
		}
		return 0;
	}


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

	std::vector<std::string> _objects;
	std::vector<RelationObservation> _inRelationObservations;
	std::vector<RelationObservation> _ontRelationObservations;
	std::vector<RelationObservation> _onRelationObservations;
	std::vector<RelationException> _inRelationExceptions;
	std::vector<RelationException> _ontRelationExceptions;
	std::vector<RelationException> _onRelationExceptions;
	std::vector<Relation> _inRelations;
	std::vector<Relation> _ontRelations;
	std::vector<Relation> _onRelations;
};


}
}

#endif /* _ROCS_CONCEPT_OBJECTRELATIONGRAPHGENERATOR_H_ */



