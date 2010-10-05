/*
 * CSystem.h
 *
 *  Created on: Sep 28, 2010
 *      Author: arnaud
 */

#ifndef CSYSTEM_H_
#define CSYSTEM_H_

#include "rocs/cv/Crfh/CFilterCache.h"
#include "rocs/cv/Crfh/CDescriptorList.h"

#include <string>
#include <vector>
using std::string;

namespace rocs {

namespace math {
template<typename _T> class Matrix_;
}

namespace cv {

class Img;
class CCrfh;

/*!
 * Main class defining a system and managing the
 * histogram extraction process.
 */
class CSystem {

public:

	/*! Constructor. Initializes the system (creates descriptors
	 and filters). */
	CSystem(string sysDef);

public:

	/*! Computes outputs of all the descriptors. */
	vector<Matrix_<double>*> computeDescriptorOutputs(const Img &image) const;

	/*! Computes the histogram for a given image. */
	CCrfh *computeHistogram(const Img &image, int skipBorderPixels) const;

private:

	/*! List of descriptors to be computed. */
	CDescriptorList _descriptorList;

	/*! Filter cache. */
	CFilterCache _filterCache;
};

} // end namespace cv
} // end namespace rocs

#endif /* CSYSTEM_H_ */
