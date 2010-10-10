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
 * \file SparseMatrix.h
 *
 * \date Sep 20, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef SPARSEMAT_H_
#define SPARSEMAT_H_

/* openCV includes */
#include <opencv/cv.h>
#include <opencv/cxcore.hpp>

// ROCS
#include "rocs/core/types.h"

namespace rocs {
namespace math {

class SparseMatrix: public cv::SparseMat {
public:
	SparseMatrix(int rows, int cols, int type);
	virtual ~SparseMatrix();

	/* data access */
	/*! \return the type of data stored inside the matrix */
	inline int getDataType() {
		return data_type;
	}

private:
	/*! the data_type of data inside the matrix */
	int data_type;

};

} // end namespace math
} // end namespace rocs

#endif /* SPARSEMAT_H_ */
