/*
 * FeatureExtractor.h
 */

#ifndef FEATUREEXTRACTOR_H_
#define FEATUREEXTRACTOR_H_

// STD includes
#include <string>
using std::string;


/*!
 * a pure virtual class
 */
namespace rocs {
namespace cv {

class Img;

class FeatureExtractor {
public:
	FeatureExtractor() {}
	virtual ~FeatureExtractor() {}

	virtual void start() = 0;
	virtual void end() = 0;
	virtual void process(Img* frame) = 0;
	virtual void process(string filename) = 0;
};

} // end namespace cv
} // end namespace rocs

#endif /* FEATUREEXTRACTOR_H_ */
