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


void AxiomFactorClassGenerator::generate()
{
	cv::Mat supportIrreflexivePotentials;
	_supportIrreflexiveFactorClass = &_fcs->addFactorClass(*_ontRelationVariableClass,
			*_ontRelationVariableClass, supportIrreflexivePotentials);
}


}
}
