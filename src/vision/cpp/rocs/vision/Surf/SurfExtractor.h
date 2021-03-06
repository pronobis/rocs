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
 * \file SurfExtractor.h
 *
 * \date Sep 20, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef SURFEXTRACTOR_H_
#define SURFEXTRACTOR_H_

#define SURF_MATCHING_MAX_DIST_1ST   0.2
#define SURF_MATCHING_MAX_RATIO_1_2  0.7 // between 0 and 1, 0 = the most exigent
#define SURF_LOCATING_MIN_PAIRS      10

/* ROCS includes */
#include "rocs/cv/FeatureExtractor.h"

/* opencv includes */
#include "opencv/highgui.h"

namespace rocs {
namespace cv {

class SurfExtractor : public FeatureExtractor<int>{
public:
	SurfExtractor();
	virtual ~SurfExtractor();

	void start();
	void end();
	void process(Img* frame_img);

	void defineObjectImage(Img* object_frame);

	bool 						DISPLAY;			//!< display windows
	std::string						video_input;		//!< the file showed if INPUT_MODE = video
	std::string						image_input;		//!< the file showed if INPUT_MODE = image

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
			const CvSeq* imageKeypoints, const CvSeq* imageDescriptors, std::vector<int>& ptpairs);
	std::vector<int> 				ptpairs;

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
