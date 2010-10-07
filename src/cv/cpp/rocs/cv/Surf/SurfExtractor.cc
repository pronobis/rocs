/*
 * SurfExtractor.cc
 *
 *  Created on: Sep 20, 2010
 *      Author: arnaud
 */

#include "rocs/cv/Surf/SurfExtractor.h"

using namespace rocs::cv;

SurfExtractor::SurfExtractor() {
}

SurfExtractor::~SurfExtractor() {
}

void SurfExtractor::start() {
	rocsDebug3("start()");

	window1Name = "original image";
	window2Name = "correspondance image";

	image_input = "../images/group.jpg";
	video_input = "../images/walk.avi";

	DISPLAY = true;

	/* creating the frames */
	frame = NULL;
	frameBW = NULL;
	frameOut = NULL;
	object_BW_image = NULL;
	object_color_image = NULL;
	correspondances_image = NULL;

	/* creating the windows */
	if (DISPLAY) {
		opencv::namedWindow(window1Name, 1);
		opencv::namedWindow(window2Name, 1);
	}

	/* init the other things */
	// ...
	surf_init();
}

/*!
 * terminate the SurfExtractor mode
 */
void SurfExtractor::end() {
	rocsDebug3("end()");
	sleep(1); // wait a little bit...

	// stopping the capture
	// TODO

	// killing the windows
	if (DISPLAY)
		cvDestroyAllWindows();

	// killing the frames
	// ...useless
}

/////// main loop                  ////////

void SurfExtractor::defineObjectImage(Img* object_frame) {
	rocsDebug3("define_object_image() : img:%s", object_frame->infoString().c_str());

	/* load the object images */
	//	object_BW_image = cvLoadImage(object_filename.c_str(),
	//			CV_LOAD_IMAGE_GRAYSCALE);
	//	object_color_image = cvLoadImage(object_filename.c_str(),
	//			CV_LOAD_IMAGE_COLOR);
	if (object_BW_image != NULL) {
		rocsDebug3("Releasing the object images...");
		cvReleaseImage(&object_color_image);
		cvReleaseImage(&object_BW_image);
	}
	IplImage object_frame_as_ipl = *(object_frame->asOpenCvMat());

	//object_color_image = &object_frame_as_ipl;
	// make a copy to keep it
	object_color_image = cvCloneImage(&object_frame_as_ipl);

	object_BW_image = cvCreateImage(cvGetSize(object_color_image),
			object_color_image->depth, 1);
	cvCvtColor(object_color_image, object_BW_image, CV_RGB2GRAY);
	//cvCvtColor(object_BW_image, object_color_image, CV_GRAY2BGR);

	/* extract the SURF points from the object image */
	object_keypoints = 0;
	object_descriptors = 0;
	cvClearMemStorage(storage);
	cvExtractSURF(object_BW_image, 0, &object_keypoints, &object_descriptors,
			storage, surf_params);
	rocsDebug3("Object Descriptors:%i", object_descriptors->total);

	/* init the corners of the object */
	src_corners[0] = cvPoint(0, 0);
	src_corners[1] = cvPoint(object_BW_image->width, 0);
	src_corners[2] = cvPoint(object_BW_image->width, object_BW_image->height);
	src_corners[3] = cvPoint(0, object_BW_image->height);
}

/*!
 * main loop of the SurfExtractor mode
 */
void SurfExtractor::process(Img* frame_img) {
	rocsDebug3("process()");

	rocsAssert(frame_img != NULL);
	IplImage frame_as_ipl = *(frame_img->asOpenCvMat());
	this->frame = &frame_as_ipl;

	/* create the buffers */
	if (frameOut == NULL) {
		rocsDebug3("creating the buffers...");
		frameBW
				= cvCreateImage(cvGetSize(&frame_as_ipl), frame_as_ipl.depth, 1);
		frameOut = cvCreateImage(cvGetSize(&frame_as_ipl), frame_as_ipl.depth,
				frame_as_ipl.nChannels);
		rocsDebug3("Moving the windows...");
		//		cvMoveWindow(window1Name, 0, 0);
		//		cvMoveWindow(window2Name, frame->width, 0);
	}

	/* algorithms */
	cvCopy(frame, frameOut);
	surf_process();

	/* display in the 2 windows */
	if (DISPLAY) {
		//		cvShowImage(window1Name, frame);
		//		cvShowImage(window1Name, frameBW);
		//		cvShowImage(window2Name, frameOut);
		cvShowImage(window2Name, correspondances_image);

		/* key listener */
		cvWaitKey();
	}
}
/////// end of the main loop       ////////

/*!
 * initiate the things required for for surf method
 */
void SurfExtractor::surf_init() {
	rocsDebug3("surf_init()");

	/* init the storage */
	storage = cvCreateMemStorage(0);
	storage2 = cvCreateMemStorage(0);

	/* init the surf surf_params */
	surf_params = cvSURFParams(300, // only features with keypoint.hessian larger than that are extracted.
			// good default value is ~300-500 (can depend on the average
			// local contrast and sharpness of the image).
			// user can further filter out some features based on their hessian values
			// and other characteristics
			1 //int extended; 0 means basic descriptors (64 elements each),
			// 1 means extended descriptors (128 elements each)
			);
	//surf_params.nOctaves = 5;
}

/*!
 * a distance function between histograms
 *
 * \param   d1 the first descriptor
 * \param   d2 the second descriptor
 * \param   best the max distance
 * \param   length the length of descriptors
 * \return  the distance between d1 and d2
 */
double SurfExtractor::surf_compareSURFDescriptors(const float* d1,
		const float* d2, double best, int length) {
	double total_cost = 0;
	assert(length % 4 == 0);
	for (int i = 0; i < length; i += 4) {
		double t0 = d1[i] - d2[i];
		double t1 = d1[i + 1] - d2[i + 1];
		double t2 = d1[i + 2] - d2[i + 2];
		double t3 = d1[i + 3] - d2[i + 3];
		total_cost += t0 * t0 + t1 * t1 + t2 * t2 + t3 * t3;
		if (total_cost > best)
			break;
	}
	return total_cost;
}

/*!
 * finds the closest neighbour
 *
 * \param   vec
 * \param   laplacian
 * \param   model_keypoints
 * \param   model_descriptors
 * \return  the index of the nearest meighbour
 */
int SurfExtractor::surf_naiveNearestNeighbor(const float* vec, int laplacian,
		const CvSeq* model_keypoints, const CvSeq* model_descriptors) {
	int length = (int) (model_descriptors->elem_size / sizeof(float));
	int neighbor = -1;
	double d;
	double dist1 = 1e6; // distance with the best
	double dist2 = dist1; // distance with the second best
	CvSeqReader reader, kreader;
	cvStartReadSeq(model_keypoints, &kreader, 0);
	cvStartReadSeq(model_descriptors, &reader, 0);

	for (int i = 0; i < model_descriptors->total; i++) {
		const CvSURFPoint* kp = (const CvSURFPoint*) kreader.ptr;
		const float* mvec = (const float*) reader.ptr;
		CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
		CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
		if (laplacian != kp->laplacian)
			continue;
		d = surf_compareSURFDescriptors(vec, mvec, dist2, length);
		if (d < dist1) {
			dist2 = dist1;
			dist1 = d;
			neighbor = i;
		} else if (d < dist2)
			dist2 = d;
	}
	if (dist1 > SURF_MATCHING_MAX_DIST_1ST) // not close enough
		return -1;
	if (dist1 > SURF_MATCHING_MAX_RATIO_1_2 * dist2) // two firsts too close
		return -1;
	return neighbor;
}

/*!
 * find corresponding pairs of points
 *
 * \param   objectKeypoints
 * \param   objectDescriptors
 * \param   imageKeypoints
 * \param   imageDescriptors
 * \param   ptpairs the vector which will contain the result
 */
void SurfExtractor::surf_findPairs(const CvSeq* objectKeypoints,
		const CvSeq* objectDescriptors, const CvSeq* imageKeypoints,
		const CvSeq* imageDescriptors, std::vector<int>& ptpairs) {
	rocsDebug3("surf_findPairs()");

	CvSeqReader reader, kreader;
	cvStartReadSeq(objectKeypoints, &kreader);
	cvStartReadSeq(objectDescriptors, &reader);
	ptpairs.clear();

	for (int i = 0; i < objectDescriptors->total; i++) {
		const CvSURFPoint* kp = (const CvSURFPoint*) kreader.ptr;
		const float* descriptor = (const float*) reader.ptr;
		CV_NEXT_SEQ_ELEM( kreader.seq->elem_size, kreader );
		CV_NEXT_SEQ_ELEM( reader.seq->elem_size, reader );
		int nearest_neighbor = surf_naiveNearestNeighbor(descriptor,
				kp->laplacian, imageKeypoints, imageDescriptors);
		if (nearest_neighbor >= 0) {
			ptpairs.push_back(i);
			ptpairs.push_back(nearest_neighbor);
		}
	}
}

/*!
 * a rough implementation for object_BW_image location
 *
 * \param   objectKeypoints
 * \param   objectDescriptors
 * \param   imageKeypoints
 * \param   imageDescriptors
 * \param   src_corners
 * \param   dst_corners
 * \return  true if the object was located
 */
bool SurfExtractor::surf_locatePlanarObject(const CvSeq* objectKeypoints,
		const CvSeq* objectDescriptors, const CvSeq* imageKeypoints,
		const CvSeq* imageDescriptors, const CvPoint src_corners[4],
		CvPoint dst_corners[4]) {
	rocsDebug3( "surf_locatePlanarObject()");

	/* find pairs */
	ptpairs.clear();
	surf_findPairs(objectKeypoints, objectDescriptors, imageKeypoints,
			imageDescriptors, ptpairs);
	int n = numberCorrespondances();
	if (n < SURF_LOCATING_MIN_PAIRS)
		return 0; // not enough points

	/* copy points in CvPoint2D32f */
	std::vector<CvPoint2D32f> pt1, pt2;
	pt1.resize(n);
	pt2.resize(n);
	for (int i = 0; i < n; i++) {
		pt1[i]
				= ((CvSURFPoint*) cvGetSeqElem(objectKeypoints, ptpairs[i * 2]))->pt;
		pt2[i] = ((CvSURFPoint*) cvGetSeqElem(imageKeypoints,
				ptpairs[i * 2 + 1]))->pt;
	}

	/* copy points in matrix */
	CvMat _pt1, _pt2;
	_pt1 = cvMat(1, n, CV_32FC2, &pt1[0]);
	_pt2 = cvMat(1, n, CV_32FC2, &pt2[0]);

	/* search the homography */
	double h[9];
	CvMat _h = cvMat(3, 3, CV_64F, h);
	/* default */
	//bool homoFind = cvFindHomography( &_pt1, &_pt2, &_h);
	/* ransac */
	//bool homoFind = cvFindHomography( &_pt1, &_pt2, &_h, CV_RANSAC, 5);
	/* least med squares */
	bool homoFind = cvFindHomography(&_pt1, &_pt2, &_h, CV_LMEDS);
	if (!homoFind)
		return 0; // impossible to find the homography

	/* compute the image of the corners with it */
	for (int i = 0; i < 4; i++) {
		double x = src_corners[i].x, y = src_corners[i].y;
		double Z = 1. / (h[6] * x + h[7] * y + h[8]);
		double X = (h[0] * x + h[1] * y + h[2]) * Z;
		double Y = (h[3] * x + h[4] * y + h[5]) * Z;
		dst_corners[i] = cvPoint(cvRound(X), cvRound(Y));
	}

	return 1;
}

/*!
 * returns true if it manages to compute the homography
 */
bool SurfExtractor::surf_process() {
	rocsDebug3( "surf_process()");

	cvCvtColor(frame, frameBW, CV_BGR2GRAY); // grayscale conversion
	//	cvEqualizeHist(frameBW, frameBW);

	/* extract the SURF points of frameBW */
	image_keypoints = 0;
	image_descriptors = 0;
	cvClearMemStorage(storage2);
	cvExtractSURF(frameBW, 0, &image_keypoints, &image_descriptors, storage2,
			surf_params);

	/* locate the object_BW_image */
	planar_object_located = surf_locatePlanarObject(object_keypoints,
			object_descriptors, image_keypoints, image_descriptors,
			src_corners, dst_corners);

	rocsDebug3( "image descriptors: %i- nb pairs:%i- matching:%i",
			image_descriptors->total,
			numberCorrespondances(),
			planar_object_located );

	/* display */
	if (DISPLAY)
		surf_draw();

	return planar_object_located;
}

/*!
 * returns the number of correspondances
 */
int SurfExtractor::numberCorrespondances() {
	return ptpairs.size() / 2;
}

/*!
 * draw the results in the image correspondances_image
 */
void SurfExtractor::surf_draw() {
	rocsDebug3("surf_draw()");

	/* draw the surf points of the image frameOut and object_color_image */
	for (int i = 0; i < image_keypoints->total; i++) {
		CvSURFPoint* r = (CvSURFPoint*) cvGetSeqElem(image_keypoints, i);
		CvPoint center = cvPoint(cvRound(r->pt.x), cvRound(r->pt.y));
		int radius = cvRound(r->size / 4);
		cvCircle(frameOut, center, radius, CV_RGB(255,0,0), 1, 8, 0);
	}

	/* copy the two objects in a new image */
	int obj_width = object_BW_image->width;
	int obj_height = object_BW_image->height;
	if (!correspondances_image) {
		rocsDebug3("Creating correspondances_image...");
		correspondances_image = cvCreateImage(cvSize(frame->width + obj_width,
				frame->height), 8, 3);
	}
	cvZero(correspondances_image);
	cvResetImageROI(correspondances_image);
	cvSetImageROI(correspondances_image, cvRect(0, 0, obj_width, obj_height));
	//	debugPrintf_lvl3("object_color_image:depth:%i, size:%ix%i", object_color_image->depth, cvGetSize(object_color_image).width, cvGetSize(object_color_image).height);
	//	debugPrintf_lvl3("correspondances_image:depth:%i, size:%ix%i", correspondances_image->depth, cvGetSize(correspondances_image).width, cvGetSize(correspondances_image).height);
	cvCopy(object_color_image, correspondances_image);
	cvResetImageROI(correspondances_image);
	cvSetImageROI(correspondances_image, cvRect(obj_width, 0, frameOut->width,
			frameOut->height));
	cvCopy(frameOut, correspondances_image);
	cvResetImageROI(correspondances_image);

	/* draw correspondances */
	for (int i = 0; i < (int) ptpairs.size(); i += 2) {
		CvSURFPoint* r1 = (CvSURFPoint*) cvGetSeqElem(object_keypoints,
				ptpairs[i]);
		CvSURFPoint* r2 = (CvSURFPoint*) cvGetSeqElem(image_keypoints,
				ptpairs[i + 1]);
		int x2 = cvRound(r2->pt.x + obj_width);
		int y2 = cvRound(r2->pt.y);
		cvLine(correspondances_image, cvPointFrom32f(r1->pt), cvPoint(x2, y2),
				CV_RGB(0,0,255));
	}

	/* draw corners correspondances */
	if (planar_object_located) {
		for (int i = 0; i < 4; i++) {
			CvPoint r1 = dst_corners[i % 4];
			CvPoint r2 = dst_corners[(i + 1) % 4];
			cvLine(correspondances_image, cvPoint(r1.x + obj_width, r1.y),
					cvPoint(r2.x + obj_width, r2.y), CV_RGB(0, 255, 0), 2);
		}
	}
}
