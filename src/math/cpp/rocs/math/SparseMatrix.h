/*
 * SparseMatrix.h
 *
 *  Created on: Sep 20, 2010
 *      Author: arnaud
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
