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
 * \file SparseMatrix.cc
 *
 * \date Sep 20, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#include "rocs/math/SparseMatrix.h"

using namespace rocs::math;

SparseMatrix::SparseMatrix(int rows, int cols, int type) :
	cv::SparseMat() {
	this->data_type = type;
	int size [2];
	size[0] = rows;
	size[1] = cols;
	create(2, size, type);
}

SparseMatrix::~SparseMatrix() {
}
