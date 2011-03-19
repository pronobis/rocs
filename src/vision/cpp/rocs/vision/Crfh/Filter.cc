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
 * \file Filter.cc
 *
 * Contains implementation of the Filter class.
 *
 * \date Sep 27, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#define PI 3.141592653589793
#include <math.h>

#include "rocs/cv/Crfh/Filter.h"
//#include "global.h"
#include "rocs/math/ElemMath.h"
//#include "Matrix_.h"

namespace rocs {
namespace cv {

Filter *Filter::createFilter(const FilterInfo &fi) {
	switch (fi.getFilterType()) {
	case FT_GAUSSIAN:
		return new CGaussianFilter(
				reinterpret_cast<const CGaussianFilterInfo &> (fi).getSigma2());
	case FT_CARTESIAN:
		return new CCartesianFilter(
				reinterpret_cast<const CCartesianFilterInfo &> (fi).getDx(),
				reinterpret_cast<const CCartesianFilterInfo &> (fi).getDy());
	default:
		return 0;
	}
}

// -----------------------------------------
void CGaussianFilter::createGaussHorizontalKernel(double sigma2) {
	rocsDebug3("createGaussHorizontalKernel(%f)", sigma2);

	double sigma = sqrt(sigma2);
	int gaussSize = rocs::math::aMax<int>(static_cast<int> (ceil(sigma
			* GAUSSIAN_SIGMAS)), 1);
	int kernelSize = 2 * gaussSize + 1;

	// Allocate memory for the kernel
	rocsDebug3("_horizontalKernel:%s, is_empty:%i", _horizontalKernel.infoString().c_str(), _horizontalKernel.isEmpty());
	_horizontalKernel.resize(1, kernelSize);

	// Be robust to sigma = 0
	if (sigma2 == 0) {
		_horizontalKernel.set(0, 0, 0);
		_horizontalKernel.set(0, 1, 1);
		_horizontalKernel.set(0, 2, 0);
		return;
	}

	// Fill in the values
	double sum = 0;
	for (int i = 0; i < kernelSize; ++i) {
		int tmp = i - gaussSize;
		double value = exp(-(tmp * tmp) / (2 * sigma2));
		_horizontalKernel.set(0, i, value);
		sum += value;
	}

	// Normalize
	_horizontalKernel /= sum;
}

// -----------------------------------------
void CGaussianFilter::createGaussVerticalKernel(double sigma2) {
	rocsDebug3("createGaussVerticalKernel(%f)", sigma2);

	double sigma = sqrt(sigma2);
	int gaussSize = rocs::math::aMax<int>(static_cast<int> (ceil(sigma
			* GAUSSIAN_SIGMAS)), 1);
	int kernelSize = 2 * gaussSize + 1;

	// Allocate memory for the kernel
	_verticalKernel.resize(kernelSize, 1);

	// Be robust to sigma = 0
	if (sigma2 == 0) {
		_verticalKernel.set(0, 0, 0);
		_verticalKernel.set(1, 0, 1);
		_verticalKernel.set(2, 0, 0);
		return;
	}

	// Fill in the values
	rocsDebug3("_verticalKernel:%s", _verticalKernel.infoString().c_str());
	double sum = 0;
	for (int i = 0; i < kernelSize; ++i) {
		//		debugPrintf_lvl3("foo %i", i);
		//		sleep(1);
		int tmp = i - gaussSize;
		double value = exp(-(tmp * tmp) / (2 * sigma2));
		_verticalKernel.set(i, 0, value);
		sum += value;
	}

	// Normalize
	_verticalKernel /= sum;
}

// -----------------------------------------
Matrix_<double> *CGaussianFilter::apply(const Matrix_<double> &input, Matrix_<
		double> *result) const {
	rocsDebug3("CGaussianFilter::apply('%s', result non null:%i", input.infoString().c_str(), (result ? 1 : 0));
	rocsDebug3("step1: _verticalKernel('%s')", _verticalKernel.infoString().c_str());
	result = Matrix_<double>::convolve(input, _verticalKernel, result);
	rocsDebug3("step2: _horizontalKernel('%s')", _horizontalKernel.infoString().c_str());
	result->convolveWith(_horizontalKernel);
	return result;
}

// -----------------------------------------
void CCartesianFilter::createXKernel(int dx) {
	rocsDebug3("createXKernel(%i)", dx);

	if (dx == 1) {
		// Allocate memory for the kernel
		_xKernel.resize(1, 3);

		// Fill in the kernel matrix
		_xKernel.set(0, 0, -0.5);
		_xKernel.set(0, 1, 0);
		_xKernel.set(0, 2, 0.5);
	} else if (dx == 2) {
		// Allocate memory for the kernel
		_xKernel.resize(1, 3);

		// Fill in the kernel matrix
		_xKernel.set(0, 0, 1);
		_xKernel.set(0, 1, -2);
		_xKernel.set(0, 2, 1);
	}
}

// -----------------------------------------
void CCartesianFilter::createYKernel(int dy) {
	rocsDebug3("createYKernel(%i)", dy);

	if (dy == 1) {
		// Allocate memory for the kernel
		_yKernel.resize(3, 1);

		// Fill in the kernel matrix
		_yKernel.set(0, 0, -0.5);
		_yKernel.set(1, 0, 0);
		_yKernel.set(2, 0, 0.5);
	} else if (dy == 2) {
		// Allocate memory for the kernel
		_yKernel.resize(3, 1);

		// Fill in the kernel matrix
		_yKernel.set(0, 0, 1);
		_yKernel.set(1, 0, -2);
		_yKernel.set(2, 0, 1);
	}
}

// -----------------------------------------
Matrix_<double> *CCartesianFilter::apply(const Matrix_<double> &input, Matrix_<
		double> *result) const {
	rocsDebug3("CCartesianFilter::apply('%s', result non null:%i", input.infoString().c_str(), (result ? 1 : 0));

	if (_xKernel.nbCols()) {
		result = Matrix_<double>::convolve(input, _xKernel, result);
		if (_yKernel.nbRows()) {
			result->convolveWith(_yKernel);
		}
	} else if (_yKernel.nbRows()) {
		result = Matrix_<double>::convolve(input, _yKernel, result);
	}

	return result;
}

} // end namespace cv
} // end namespace rocs
