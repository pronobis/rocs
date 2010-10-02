/*
 * SparseMatrix.cc
 *
 *  Created on: Sep 20, 2010
 *      Author: arnaud
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
