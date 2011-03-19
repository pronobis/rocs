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
//#include <opencv/highgui.h>

namespace rocs
{
namespace math
{

Matrix::Matrix(int rows, int cols, int type) :
	cv::Mat(rows, cols, type)
{
	this->data_type = type;
}

Matrix::~Matrix()
{
}

void Matrix::copyTo(Matrix dst) const
{
	rocsDebug3("copyTo(%s, %s)", infoString().c_str(), dst.infoString().c_str());

	// TODO what if data types are not similar ?
	assert(getDataType() == dst.getDataType());

	/* resize if needed */
	if (dst.nbCols() != nbCols() || dst.nbRows() != nbRows())
		dst.resize(nbRows(), nbCols());

	for (int i = 0; i < nbRows(); ++i)
	{
		for (int j = 0; j < nbCols(); ++j)
		{
			std::string value = "";
			switch (data_type)
			{
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

bool Matrix::operator ==(const Matrix &m) const
{
	// TODO more clever implementation
	switch (data_type)
	{
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

bool Matrix::operator !=(const Matrix &m) const
{
	return !(*this == m);
}

Matrix* Matrix::operator +(const Matrix &m) const
{
	// TODO more clever implementation
	switch (data_type)
	{
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
Matrix* Matrix::operator -(const Matrix &m) const
{
	// TODO more clever implementation
	switch (data_type)
	{
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
Matrix* Matrix::operator *(const Matrix &m) const
{
	// TODO more clever implementation
	switch (data_type)
	{
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

double Matrix::det()
{
	return cv::determinant(*this);
}

Matrix* Matrix::transpose() const
{
	Matrix* ans = new Matrix(nbCols(), nbRows(), data_type);
	// transpose the cv matrix
	cv::transpose(*this, *ans);
	return ans;
}

Matrix* Matrix::inverse(int method /*=DECOMP_LU*/) const
{
	Matrix* ans = new Matrix(nbCols(), nbRows(), data_type);
	cv::invert(*this, *ans);
	return ans;
}

int Matrix::nbCols() const
{
	return size().width;
}

int Matrix::nbRows() const
{
	return size().height;
}

void Matrix::splitToOneChannel(Matrix* channel0, Matrix* channel1,
		Matrix* channel2, Matrix* channel3)
{
	rocsDebug3("splitToOneChannel(c0:%i, c1:%i, c2:%i, c3:%i)", channel0 != NULL, channel1 != NULL, channel2 != NULL, channel3 != NULL);
	Matrix* channels[] =
	{ channel0, channel1, channel2, channel3 };
	splitToOneChannel(channels, 4);
}

void Matrix::splitToOneChannel(Matrix* channels[], int channelsSize)
{
	rocsDebug3("src:%s", infoString().c_str());
	/* get the wanted channel as uchar */
	IplImage thisAsIpl = *this->asOpenCvMat();

	/*
	 * create the from_to for the wanted channels
	 */
	std::vector<opencv::Mat> dstVector;
	std::vector<int> fromToVector;
	for (int channelCounter = 0; channelCounter < channelsSize; ++channelCounter)
	{
		if (channels[channelCounter] == NULL)
			continue;
		/*
		 * from  now we are sure the current channel is not empty
		 */
		dstVector.push_back(channels[channelCounter]->asConstOpenCvMat());
		fromToVector.push_back(channelCounter); // source
		fromToVector.push_back(dstVector.size() - 1); // destination
	}

	/*
	 * convert to arrays
	 */
	unsigned int npairs = fromToVector.size() / 2;
	//	Matrix dst[dstVector.size()];
	//	for (unsigned int dstIndex = 0; dstIndex < ndsts; ++dstIndex)
	//		dst[dstIndex] = *dstVector[dstIndex];
	int fromTo[fromToVector.size()];
	for (unsigned int i = 0; i < fromToVector.size(); ++i)
		fromTo[i] = fromToVector[i];
	for (unsigned int pairIndex = 0; pairIndex < npairs; ++pairIndex)
		rocsDebug3("Pair: (%i,%i)", fromTo[2*pairIndex], fromTo[2*pairIndex+1]);

	/*
	 * do the real conversion
	 */
	std::vector<opencv::Mat> srcv;
	srcv.push_back(asConstOpenCvMat());
	rocsDebug3("ndsts:%i, nPairs:%i", (int) dstVector.size(), npairs);
	mixChannels(srcv, dstVector, fromTo, npairs);

	//	using namespace opencv;
	//	Mat rgba(100, 100, CV_8UC4, Scalar(1, 2, 3, 4));
	//	Mat bgr(rgba.rows, rgba.cols, CV_8UC3 );
	//	Mat alpha(rgba.rows, rgba.cols, CV_8UC1 );
	//	// this code splits a 4-channel RGBA image into a 3-channel BGR (i.e. with R and B channels swapped) and separate alpha channel image:
	//	// forming array of matrices is quite efficient operations,
	//	// because the matrix data is not copied, only the headers
	//	Mat out2[] =
	//	{ bgr, alpha };
	//	// rgba[0] -> bgr[2], rgba[1] -> bgr[1],
	//	// rgba[2] -> bgr[0], rgba[3] -> alpha[0]
	//	int from_to[] =
	//	{ 0, 2, 1, 1, 2, 0, 3, 3 };
	//	mixChannels(&rgba, 1, out2, 2, from_to, 4);

	//IplImage* c0ptr = NULL, *c1ptr = NULL, *c2ptr = NULL, *c3ptr = NULL;
	//	if (channel0)
	//	{
	//		rocsDebug3("c0:%s", channel0->infoString().c_str());
	//		IplImage c0 = (IplImage) channel0 ->asConstOpenCvMat();
	//		c0ptr = &c0;
	//	}
	//	if (channel1)
	//	{
	//		rocsDebug3("c1:%s", channel1->infoString().c_str());
	//		IplImage c1 = (IplImage) channel1 ->asConstOpenCvMat();
	//		c1ptr = &c1;
	//	}
	//	if (channel2)
	//	{
	//		rocsDebug3("c2:%s", channel2->infoString().c_str());
	//		IplImage c2 = (IplImage) channel2 ->asConstOpenCvMat();
	//		c2ptr = &c2;
	//	}
	//	if (channel3)
	//	{
	//		rocsDebug3("c3:%s", channel3->infoString().c_str());
	//		IplImage c3 = (IplImage) channel3 ->asConstOpenCvMat();
	//		c3ptr = &c3;
	//	}
	//	cvSplit(&thisAsIpl, c0ptr, c1ptr, c2ptr, c3ptr);
	//	cvShowImage("test", &thisAsIpl);
	//	cvWaitKey(0);
	//	cvShowImage("test", c0ptr);
	//	cvWaitKey(0);
	//	cvShowImage("test", c1ptr);
	//	cvWaitKey(0);
	//	cvShowImage("test", c2ptr);
	//	cvWaitKey(0);
	//	cvShowImage("test", c3ptr);
	//	cvWaitKey(0);
	//	rocsDebug3("channel1:%s", channel1->toString().c_str());
}

std::string Matrix::toString()
{
	std::ostringstream buffer;
	// adding size
	buffer << infoString() << " : " << std::endl;
	// adding line after line
	for (int i = 0; i < nbRows(); ++i)
	{
		for (int j = 0; j < nbCols(); ++j)
		{
			//string value = "";
			switch (data_type)
			{
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
