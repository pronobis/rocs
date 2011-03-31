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
#include <stddef.h>

namespace rocs {
namespace concept {

using namespace ml;


void recurseSupportRequirement(cv::Mat &potentials, int *indices, int depth, int maxDepth)
{
  if (depth > maxDepth) {
    potentials.at<double>(indices) = 0;
  }
  else {
    //Case: ~ONt(z,y)
    indices[depth*3] = 0;  	//~ONt(zn,y)
    indices[depth*3+1] = 0;    	//~ON(x,zn)
    indices[depth*3+2] = 0;  	//~IN(x,zn)
    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);
    indices[depth*3+1] = 1;    	//ON(x,zn)
    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);
    indices[depth*3+1] = 0;    	//~ON(x,zn)
    indices[depth*3+2] = 1;  	//IN(x,zn)
    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);
    indices[depth*3+1] = 1;    	//ON(x,zn)
    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);

    // ONt(z,y) and ~ON(x,z) and ~IN(x,z)) (case when ~ONt(z,y) already covered above)
    indices[depth*3] = 1;
    indices[depth*3+1] = 0;
    indices[depth*3+2] = 0;
    recurseSupportRequirement(potentials, indices, depth+3, maxDepth);
  }
}

void AxiomFactorClassGenerator::generate(size_t inCount, size_t ontCount, size_t onCount)
{
  {
    int sizes[] = {2, 2};
    cv::Mat supportAntisymmetricalPotentials(2, sizes, CV_64F);
    supportAntisymmetricalPotentials.setTo(1);
    int indices[] = {1,1};
    supportAntisymmetricalPotentials.at<double>(indices) = 0;

    _supportAntisymmetricalFactorClass = &_fcs->addFactorClass(*_ontRelationVariableClass,
	*_ontRelationVariableClass, supportAntisymmetricalPotentials);
  }

  {
    int sizes[] = {2, 2};
    cv::Mat containmentAntisymmetricalPotentials(2, sizes, CV_64F);
    containmentAntisymmetricalPotentials.setTo(1);
    int indices[] = {1,1};
    containmentAntisymmetricalPotentials.at<double>(indices) = 0;

    _containmentAntisymmetricalFactorClass = &_fcs->addFactorClass(*_ontRelationVariableClass,
	*_ontRelationVariableClass, containmentAntisymmetricalPotentials);
  }

  {
    int sizes[] = {2, 2};
    cv::Mat supportImpliesTransitiveSupportPotentials(2, sizes, CV_64F);
    supportImpliesTransitiveSupportPotentials.setTo(1);
    int indices[] = {1,0};
    supportImpliesTransitiveSupportPotentials.at<double>(indices) = 0;

    _supportImpliesTransitiveSupportFactorClass = &_fcs->addFactorClass(*_onRelationVariableClass,
	*_ontRelationVariableClass, supportImpliesTransitiveSupportPotentials);
  }

  {
    int sizes[] = {2, 2, 2};
    cv::Mat supportTransitivePotentials(3, sizes, CV_64F);
    supportTransitivePotentials.setTo(1);
    int indices[] = {1,1,0};//Forbid true, true, false case
    supportTransitivePotentials.at<double>(indices) = 0;

    std::vector<ml::VariableClass>classes;
    classes.push_back(*_ontRelationVariableClass);
    classes.push_back(*_ontRelationVariableClass);
    classes.push_back(*_ontRelationVariableClass);

    _supportTransitiveFactorClass = &_fcs->addFactorClass(classes, supportTransitivePotentials);
  }

  {
    int sizes[] = {2, 2, 2};
    cv::Mat containmentTransitivePotentials(3, sizes, CV_64F);
    containmentTransitivePotentials.setTo(1);
    int indices[] = {1,1,0};//Forbid true, true, false case
    containmentTransitivePotentials.at<double>(indices) = 0;

    std::vector<ml::VariableClass>classes;
    classes.push_back(*_inRelationVariableClass);
    classes.push_back(*_inRelationVariableClass);
    classes.push_back(*_inRelationVariableClass);

    _containmentTransitiveFactorClass = &_fcs->addFactorClass(classes, containmentTransitivePotentials);
  }

  {
    int sizes[] = {2, 2, 2};
    cv::Mat generousContainmentPotentials(3, sizes, CV_64F);
    generousContainmentPotentials.setTo(1);
    int indices[] = {1,1,0};//Forbid true, true, false case
    generousContainmentPotentials.at<double>(indices) = 0;

    std::vector<ml::VariableClass>classes;
    classes.push_back(*_ontRelationVariableClass);
    classes.push_back(*_inRelationVariableClass);
    classes.push_back(*_inRelationVariableClass);

    _generousContainmentFactorClass = &_fcs->addFactorClass(classes, generousContainmentPotentials);
  }

  {
    int sizes[] = {2, 2, 2};
    cv::Mat containmentSupportsPotentials(3, sizes, CV_64F);
    containmentSupportsPotentials.setTo(1);
    int indices[] = {1,1,0};//Forbid true, true, false case
    containmentSupportsPotentials.at<double>(indices) = 0;

    std::vector<ml::VariableClass>classes;
    classes.push_back(*_inRelationVariableClass);
    classes.push_back(*_ontRelationVariableClass);
    classes.push_back(*_ontRelationVariableClass);

    _containmentSupportsFactorClass = &_fcs->addFactorClass(classes, containmentSupportsPotentials);
  }

  if (0)
  {
    int dimensions = inCount + ontCount + onCount;
    int *sizes = new int[dimensions];
    for (int i = 0; i < dimensions; i++) {
      sizes[i] = 2;
    }
    cv::Mat directSupportRequiredPotentials(dimensions, sizes, CV_64F);
    directSupportRequiredPotentials.setTo(1);

    //For all (x,y)
    // If ONt(x,y) and ~ON(x,y)
    //  For all z1
    //   if (~ONt(z,y) or (~ON(x,z) and ~IN(x,z)))
    //    For all z2...
    //      ...
    //      set false

    std::vector<ml::VariableClass>classes;
    //classes filled out as follows:
    //ONt(x,y) (LHS),
    //ON(x,y) (RHS),
    //IN(x,y),
    //ONt(z1,y)		
    //ON(x,z1) 		
    //IN(x,z1) 		
    //ONt(z2,y) ...//excluding ONt(x,y)
    //ON(x,z2)     //excluding ON(x,y)
    //IN(x,z2)     //excluding IN(x,y)
    for(int i = 0; i < dimensions; i+=3) {
      classes.push_back(*_ontRelationVariableClass);
      classes.push_back(*_onRelationVariableClass);
      classes.push_back(*_inRelationVariableClass);
    }

    int *indices = new int[dimensions];
    indices[0] = 1;//ONt(x,y)
    indices[1] = 0;//~ON(x,y)
    indices[2] = 0;//~IN(x,y)
    recurseSupportRequirement(directSupportRequiredPotentials, indices, 3, dimensions);
    indices[2] = 1;//IN(x,y)
    recurseSupportRequirement(directSupportRequiredPotentials, indices, 3, dimensions);

    _directSupportRequiredFactorClass = &_fcs->addFactorClass(classes, directSupportRequiredPotentials);
  }

  if(0)
  {
    int dimensions = inCount + ontCount;
    int *sizes = new int[dimensions];
    for (int i = 0; i < dimensions; i++) {
      sizes[i] = 2;
    }
    cv::Mat supportRequiredPotentials(dimensions, sizes, CV_64F);
    supportRequiredPotentials.setTo(1);

    //classes filled out as follows:
    //ONt(x,y1),
    //IN(x,y1),
    //ONt(x,y2) ...  //excluding ONt(x,x)
    //IN(x,y2) ...   //excluding IN(x,x)

    std::vector<ml::VariableClass>classes;
    int *indices = new int[dimensions];
    for(int i = 0; i < dimensions; i+=2) {
      classes.push_back(*_ontRelationVariableClass);
      classes.push_back(*_inRelationVariableClass);
      indices[i] = 0;		//~ONt(x,y)
      indices[i+1] = 0;		//~IN(x,y)
    }

    supportRequiredPotentials.at<double>(indices) = 0;
    _supportRequiredFactorClass = &_fcs->addFactorClass(classes, supportRequiredPotentials);
  }

  {
    //Assume relations given are ON(x,y) and ON(x,z) where y!=z
    int sizes[] = {2, 2};
    cv::Mat uniqueSupportPotentials(2, sizes, CV_64F);
    uniqueSupportPotentials.setTo(1);
    int indices[] = {1,0};//Forbid true, true, false case
    uniqueSupportPotentials.at<double>(indices) = 0;

    _uniqueSupportFactorClass = &_fcs->addFactorClass(*_onRelationVariableClass,
	*_ontRelationVariableClass, uniqueSupportPotentials);
  }

  {
    //Assume relations given are ONt(x,y), ONt(x,z), ONt(y,z), ONt(z,y)
    int sizes[] = {2, 2, 2, 2};
    cv::Mat uniqueTransitiveSupportPotentials(4, sizes, CV_64F);
    uniqueTransitiveSupportPotentials.setTo(1);
    int indices[] = {1,1,0,0};//Forbid true, true, false, false case
    uniqueTransitiveSupportPotentials.at<double>(indices) = 0;

    std::vector<ml::VariableClass>classes;
    classes.push_back(*_ontRelationVariableClass);
    classes.push_back(*_ontRelationVariableClass);
    classes.push_back(*_ontRelationVariableClass);
    classes.push_back(*_ontRelationVariableClass);

    _uniqueTransitiveSupportFactorClass = &_fcs->addFactorClass(classes, uniqueTransitiveSupportPotentials);
  }

  {
    //Assume relations given are IN(x,y), IN(x,z), IN(y,z), IN(z,y)
    int sizes[] = {2, 2, 2, 2};
    cv::Mat uniqueInnessPotentials(4, sizes, CV_64F);
    uniqueInnessPotentials.setTo(1);
    int indices[] = {1,1,0,0};//Forbid true, true, false, false case
    uniqueInnessPotentials.at<double>(indices) = 0;

    std::vector<ml::VariableClass>classes;
    classes.push_back(*_inRelationVariableClass);
    classes.push_back(*_inRelationVariableClass);
    classes.push_back(*_inRelationVariableClass);
    classes.push_back(*_inRelationVariableClass);

    _uniqueInnessFactorClass = &_fcs->addFactorClass(classes, uniqueInnessPotentials);
  }
}


};
};
