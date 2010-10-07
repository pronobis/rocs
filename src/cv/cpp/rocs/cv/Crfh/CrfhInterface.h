/*
 * CrfhInterface.h
 *
 *  Created on: Oct 7, 2010
 *      Author: arnaud
 */

#ifndef CRFHINTERFACE_H_
#define CRFHINTERFACE_H_

namespace rocs {
namespace cv {

class CrfhInterface {
public:
	CrfhInterface();
	virtual ~CrfhInterface();

	void process(string sysDescr, string inputFileName, string outputFileName,
			double minHistValue = 0);
};

} // end namespace cv
} // end namespace rocs

#endif /* CRFHINTERFACE_H_ */
