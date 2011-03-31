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
 * \file AxiomFactorClassGenerator.cc
 */

#include "rocs/concept/AxiomFactorClassGenerator.h"

#include "rocs/ml/FactorClassSet.h"
#include <opencv2/core/core.hpp>

namespace rocs {
namespace concept {

using namespace ml;


void AxiomFactorClassGenerator::generate(size_t inCount, size_t intCount, size_t onCount)
{/*
  {
    int sizes[] = {2, 2};
    cv::Mat supportAntisymmetricalPotentials(2, sizes, CV_64F);
    supportAntisymmetricalPotentials.setTo(1);
    int indices[] = {1,1};
    supportAntisymmetricalPotentials.at(indices) = 0;

    _supportAntisymmetricalFactorClass = &_fcs->addFactorClass(*_ontRelationVariableClass,
	*_ontRelationVariableClass, supportAntisymmetricalPotentials);
  }

  {
    int sizes[] = {2, 2};
    cv::Mat containmentAntisymmetricalPotentials(2, sizes, CV_64F);
    containmentAntisymmetricalPotentials.setTo(1);
    int indices[] = {1,1};
    containmentAntisymmetricalPotentials.at(indices) = 0;

    _containmentAntisymmetricalFactorClass = &_fcs->addFactorClass(*_ontRelationVariableClass,
	*_ontRelationVariableClass, containmentAntisymmetricalPotentials);
  }

  {
    int sizes[] = {2, 2};
    cv::Mat supportImpliesTransitiveSupportPotentials(2, sizes, CV_64F);
    supportImpliesTransitiveSupportPotentials.setTo(1);
    int indices[] = {1,0};
    supportImpliesTransitiveSupportPotentials.at(indices) = 0;

    _supportImpliesTransitiveSupportFactorClass = &_fcs->addFactorClass(*_onRelationVariableClass,
	*_ontRelationVariableClass, supportImpliesTransitiveSupportFactorClass);
  }

  {
    int sizes[] = {2, 2, 2};
    cv::Mat supportTransitivePotentials(3, sizes, CV_64F);
    supportTransitivePotentials.setTo(1);
    int indices[] = {1,1,0};//Forbid true, true, false case
    supportTransitivePotentials.at(indices) = 0;

    std::vector<ml::FactorClass *>classes;
    classes.push_back(_ontRelationVariableClass);
    classes.push_back(_ontRelationVariableClass);
    classes.push_back(_ontRelationVariableClass);

    _supportTransitiveFactorClass = &_fcs->addFactorClass(classes, supportTransitivePotentials);
  }

  {
    int sizes[] = {2, 2, 2};
    cv::Mat containmentTransitivePotentials(3, sizes, CV_64F);
    containmentTransitivePotentials.setTo(1);
    int indices[] = {1,1,0};//Forbid true, true, false case
    containmentTransitivePotentials.at(indices) = 0;

    std::vector<ml::FactorClass *>classes;
    classes.push_back(_inRelationVariableClass);
    classes.push_back(_inRelationVariableClass);
    classes.push_back(_inRelationVariableClass);

    _containmentTransitiveFactorClass = &_fcs->addFactorClass(classes, containmentTransitivePotentials);
  }

  {
    int sizes[] = {2, 2, 2};
    cv::Mat generousContainmentPotentials(3, sizes, CV_64F);
    generousContainmentPotentials.setTo(1);
    int indices[] = {1,1,0};//Forbid true, true, false case
    generousContainmentPotentials.at(indices) = 0;

    std::vector<ml::FactorClass *>classes;
    classes.push_back(_ontRelationVariableClass);
    classes.push_back(_inRelationVariableClass);
    classes.push_back(_inRelationVariableClass);

    _generousContainmentFactorClass = &_fcs->addFactorClass(classes, generousContainmentPotentials);
  } */
}


}
}
