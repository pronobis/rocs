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
 * \file CrfhInterface.h
 *
 * \date Oct 7, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef CRFHINTERFACE_H_
#define CRFHINTERFACE_H_

// STD includes
#include <string>
using std::string;

namespace rocs {
namespace cv {

class CrfhInterface {
public:
	CrfhInterface();
	virtual ~CrfhInterface();

	void process(string sysDescr, string inputFileName, string outputFileName,
			double minHistValue = 0);
};

} // end namespace cv
} // end namespace rocs

#endif /* CRFHINTERFACE_H_ */
