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
 * \file Matrix.cc
 * \author Arnaud Ramey, Andrzej Pronobis
 */


#include "rocs/math/Matrix.h"

namespace rocs {
namespace math {

Matrix::Matrix(int rows, int cols, int type) :
	cv::Mat(rows, cols, type) {
	this->data_type = type;
}

Matrix::~Matrix() {
}

void Matrix::copyTo(Matrix dst) const{
	rocsDebug3("copyTo(%s, %s)", infoString().c_str(), dst.infoString().c_str());

	// TODO what if data types are not similar ?
	assert(getDataType() == dst.getDataType());

	/* resize if needed */
	if (dst.nbCols() != nbCols() || dst.nbRows() != nbRows())
		dst.resize(nbRows(), nbCols());

	for (int i = 0; i < nbRows(); ++i) {
		for (int j = 0; j < nbCols(); ++j) {
			std::string value = "";
			switch (data_type) {
			case MAT_1U:
				dst.set<bool> (i, j, get<bool> (i, j));
				break;
			case MAT_8U:
				dst.set<uchar> (i, j, get<uchar> (i, j));
				break;
			case MAT_8S:
				dst.set<char> (i, j, get<char> (i, j));
				break;
			case MAT_16U:
				dst.set<unsigned short int> (i, j, get<unsigned short int> (i,
						j));
				break;
			case MAT_16S:
				dst.set<short int> (i, j, get<short int> (i, j));
				break;
			case MAT_32U:
				dst.set<unsigned int> (i, j, get<unsigned int> (i, j));
				break;
			case MAT_32S:
				dst.set<int> (i, j, get<int> (i, j));
				break;
			case MAT_32F:
				dst.set<float> (i, j, get<float> (i, j));
				break;
			case MAT_64F:
				dst.set<double> (i, j, get<double> (i, j));
				break;
			default:
				break;
			}
		} // end loop cols
	} // end loop rows
}

bool Matrix::operator ==(const Matrix &m) const {
	// TODO more clever implementation
	switch (data_type) {
	case MAT_1U:
		return this->equals<bool> (m);
	case MAT_8U:
		return this->equals<uchar> (m);
	case MAT_8S:
		return this->equals<char> (m);
	case MAT_16U:
		return this->equals<unsigned short int> (m);
	case MAT_16S:
		return this->equals<short int> (m);
	case MAT_32U:
		return this->equals<unsigned int> (m);
	case MAT_32S:
		return this->equals<int> (m);
	case MAT_32F:
		return this->equals<float> (m);
	case MAT_64F:
		return this->equals<double> (m);
	default:
		return false;
	}
}

bool Matrix::operator !=(const Matrix &m) const {
	return !(*this == m);
}

Matrix* Matrix::operator +(const Matrix &m) const {
	// TODO more clever implementation
	switch (data_type) {
	case MAT_1U:
		return this->plus<bool> (m);
	case MAT_8U:
		return this->plus<uchar> (m);
	case MAT_8S:
		return this->plus<char> (m);
	case MAT_16U:
		return this->plus<unsigned short int> (m);
	case MAT_16S:
		return this->plus<short int> (m);
	case MAT_32U:
		return this->plus<unsigned int> (m);
	case MAT_32S:
		return this->plus<int> (m);
	case MAT_32F:
		return this->plus<float> (m);
	case MAT_64F:
		return this->plus<double> (m);
	default:
		return false;
	}
}
Matrix* Matrix::operator -(const Matrix &m) const {
	// TODO more clever implementation
	switch (data_type) {
	case MAT_1U:
		return this->minus<bool> (m);
	case MAT_8U:
		return this->minus<uchar> (m);
	case MAT_8S:
		return this->minus<char> (m);
	case MAT_16U:
		return this->minus<unsigned short int> (m);
	case MAT_16S:
		return this->minus<short int> (m);
	case MAT_32U:
		return this->minus<unsigned int> (m);
	case MAT_32S:
		return this->minus<int> (m);
	case MAT_32F:
		return this->minus<float> (m);
	case MAT_64F:
		return this->minus<double> (m);
	default:
		return false;
	}
}
Matrix* Matrix::operator *(const Matrix &m) const {
	// TODO more clever implementation
	switch (data_type) {
	case MAT_1U:
		return this->times<bool> (m);
	case MAT_8U:
		return this->times<uchar> (m);
	case MAT_8S:
		return this->times<char> (m);
	case MAT_16U:
		return this->times<unsigned short int> (m);
	case MAT_16S:
		return this->times<short int> (m);
	case MAT_32U:
		return this->times<unsigned int> (m);
	case MAT_32S:
		return this->times<int> (m);
	case MAT_32F:
		return this->times<float> (m);
	case MAT_64F:
		return this->times<double> (m);
	default:
		return false;
	}
}

double Matrix::det() {
	return cv::determinant(*this);
}

Matrix* Matrix::transpose() const {
	Matrix* ans = new Matrix(nbCols(), nbRows(), data_type);
	// transpose the cv matrix
	cv::transpose(*this, *ans);
	return ans;
}

Matrix* Matrix::inverse(int method /*=DECOMP_LU*/) const {
	Matrix* ans = new Matrix(nbCols(), nbRows(), data_type);
	cv::invert(*this, *ans);
	return ans;
}

int Matrix::nbCols() const {
	return size().width;
}

int Matrix::nbRows() const {
	return size().height;
}

std::string Matrix::toString() {
	std::ostringstream buffer;
	// adding size
	buffer << nbCols() << "x" << nbRows() << " : " << std::endl;
	// adding line after line
	for (int i = 0; i < nbRows(); ++i) {
		for (int j = 0; j < nbCols(); ++j) {
			//string value = "";
			switch (data_type) {
			case MAT_1U:
				buffer << get<bool> (i, j);
				break;
			case MAT_8U:
				buffer << (int) get<uchar> (i, j);
				break;
			case MAT_8S:
				buffer << (int) get<char> (i, j);
				break;
			case MAT_16U:
				buffer << get<unsigned short int> (i, j);
				break;
			case MAT_16S:
				buffer << get<short int> (i, j);
				break;
			case MAT_32U:
				buffer << get<unsigned int> (i, j);
				break;
			case MAT_32S:
				buffer << get<int> (i, j);
				break;
			case MAT_32F:
				buffer << get<float> (i, j);
				break;
			case MAT_64F:
				buffer << get<double> (i, j);
				break;
			default:
				break;
			}
			buffer << "\t";
		} // end loop cols
		buffer << std::endl;
	} // end loop rows
	return buffer.str();
}

} // end namespace math
} // end namespace rocs
