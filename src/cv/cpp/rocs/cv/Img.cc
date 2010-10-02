/*
 * Img.cpp
 *
 *  Created on: Jul 3, 2010
 *      Author: arnaud
 */

#include "rocs/cv/Img.h"
//#include "highgui.h"

namespace rocs {
namespace cv {

Img::Img(int rows, int cols, int type) :
	math::Matrix(rows, cols, type) {
}

Img::~Img() {
}

/*! Returns the intensity channel L as a matrix of doubles. */
math::Matrix_<double> *Img::getL(math::Matrix_<double> *L /*= 0*/) const {
	debugPrint_lvl3("getL()");

	/* convert to HLS */
	// void cvtColor(const Mat& src, Mat& dst, int code, int dstCn=0)
	opencv::Mat thisAsHls(nbRows(), nbCols(), CV_8U);
	opencv::cvtColor(this->asConstOpenCvMat(), thisAsHls, CV_RGB2HLS);
	//	debugPrintf_lvl3("thisAsHls after convert:depth=%i", thisAsHls.depth());
	//	opencv::imshow("image_hls", thisAsHls);
	//	opencv::waitKey();

	/* get the wanted channel as uchar */
	IplImage thisAsHlsAsIpl = thisAsHls;
	math::Matrix_<uchar> channel(nbRows(), nbCols());
	IplImage channelAsIpl = channel.asConstOpenCvMat();
	cvSplit(&thisAsHlsAsIpl, 0, &channelAsIpl, 0, 0);
	//	debugPrintf_lvl3("channel before return:%s, (1,1):%f", channel.infoCString(), (double) channel.get(1,1));
	//	debugPrintf_lvl3("channel before return:%s", channel.toString().c_str());
	//	opencv::imshow("test", channel.asConstOpenCvMat());
	//	opencv::waitKey();

	//	opencv::Mat thisAs32bits(nbRows(), nbCols(), CV_32SC3);
	//	this->asConstOpenCvMat().convertTo(thisAs32bits, CV_32S);
	//	debugPrintf_lvl3("thisAs32bits after convert:depth=%i", thisAs32bits.depth());
	//	opencv::Mat thisAsHls(nbRows(), nbCols(), CV_32SC3);
	//	opencv::cvtColor(thisAs32bits, thisAsHls, CV_RGB2HLS);
	//	debugPrintf_lvl3("thisAsHls after convert:depth=%i", thisAsHls.depth());
	//	opencv::imshow("image_hls", thisAsHls);
	//	opencv::waitKey();
	//
	//	IplImage foo = thisAsHls;
	//	math::Matrix_<uchar> test_m(nbRows(), nbCols());
	//	IplImage test = test_m.asConstOpenCvMat();
	//	cvSplit(&foo, &test, 0, 0, 0);
	//	opencv::imshow("test", test_m.asConstOpenCvMat());
	//	opencv::waitKey();

	/* create the channel */
	if (L == 0) {
		debugPrint_lvl3("Creating the L matrix.");
		L = new math::Matrix_<double>(nbRows(), nbCols());
	}

	/* convert to double */
	channel.copyTo_<uchar, double> (*L);
	//	debugPrintf_lvl3("L before return:%s, (1,1):%f", L->infoCString(), L->get(1,1));
	//	debugPrintf_lvl3("L before return:%s", L->toString().c_str());

	debugPrint_lvl3("getL() finished.");

	/* return the wanted channel */
	return L;
}

} // end namespace cv
} // end namespace rocs
