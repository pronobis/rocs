// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2010  Arnaud Ramey, Andrzej Pronobis
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
 * \file FeatureExtractor.h
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef FEATUREEXTRACTOR_H_
#define FEATUREEXTRACTOR_H_

// STD includes
#include <string>
using std::string;


/*!
 * a pure virtual class
 */
namespace rocs {
namespace cv {

class Img;

class FeatureExtractor {
public:
	FeatureExtractor() {}
	virtual ~FeatureExtractor() {}

	virtual void start() = 0;
	virtual void end() = 0;
	virtual void process(Img* frame) = 0;
	virtual void process(string filename) = 0;
};

} // end namespace cv
} // end namespace rocs

#endif /* FEATUREEXTRACTOR_H_ */
