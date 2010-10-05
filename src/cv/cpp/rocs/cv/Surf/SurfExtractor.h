/*
 * SurfExtractor.h
 *
 *  Created on: Sep 20, 2010
 *      Author: arnaud
 */

#ifndef SURFEXTRACTOR_H_
#define SURFEXTRACTOR_H_

#define SURF_MATCHING_MAX_DIST_1ST   0.2
#define SURF_MATCHING_MAX_RATIO_1_2  0.7 // between 0 and 1, 0 = the most exigent
#define SURF_LOCATING_MIN_PAIRS      10

/* ROCS includes */
#include "rocs/core/Core.h"
#include "rocs/cv/FeatureExtractor.h"
#include "rocs/cv/Img.h"

/* opencv includes */
#include "opencv/highgui.h"

namespace rocs {
namespace cv {

class SurfExtractor : public FeatureExtractor{
public:
	SurfExtractor();
	virtual ~SurfExtractor();

	void start();
	void end();
	void process(Img* frame_img);

	void defineObjectImage(Img* object_frame);

	bool 						DISPLAY;			//!< display windows
	string						video_input;		//!< the file showed if INPUT_MODE = video
	string						image_input;		//!< the file showed if INPUT_MODE = image

	/////
	///// general fields
	/////
	IplImage* 					frame;				//!< the acquired frame
	IplImage* 					frameBW;			//!< the BW version of the acquired frame
	IplImage* 					frameOut;			//!< the output
	const char* 				window1Name;		//!< the name of the first window
	const char* 				window2Name;		//!< the name of the second window


	//////
	////// finder
	//////
	double surf_compareSURFDescriptors
	(const float* d1, const float* d2, double best, int length);
	int surf_naiveNearestNeighbor
	(const float* vec, int laplacian,  const CvSeq* model_keypoints, const CvSeq* model_descriptors);
	void surf_findPairs
	(const CvSeq* objectKeypoints, const CvSeq* objectDescriptors,
			const CvSeq* imageKeypoints, const CvSeq* imageDescriptors, vector<int>& ptpairs);
	vector<int> 				ptpairs;

	bool surf_locatePlanarObject
	(const CvSeq* objectKeypoints,  const CvSeq* objectDescriptors, const CvSeq* imageKeypoints,
			const CvSeq* imageDescriptors, const CvPoint src_corners[4], CvPoint dst_corners[4]);
	bool 						planar_object_located;
	CvPoint 					src_corners[4];
	CvPoint 					dst_corners[4];

	void surf_init				();
	CvSURFParams 				surf_params;
	//string 						object_filename;
	IplImage* 					object_BW_image;
	CvSeq *						object_keypoints;
	CvSeq *						object_descriptors;
	CvMemStorage* 				storage;

	bool surf_process			();
	CvSeq *						image_keypoints;
	CvSeq *						image_descriptors;
	CvMemStorage* 				storage2;

	/* draw the surf points of the object_BW_image */
	void surf_draw				();
	IplImage* 					correspondances_image;
	IplImage*					object_color_image;

	// data access
	/*! returns the number of correspondances */
	int	numberCorrespondances	();

};

} // end namespace cv
} // end namespace rocs

#endif /* SURFEXTRACTOR_H_ */
