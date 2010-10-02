/*
 * CDescriptorList.h
 *
 *  Created on: Sep 28, 2010
 *      Author: arnaud
 */

#ifndef CDESCRIPTORLIST_H_
#define CDESCRIPTORLIST_H_

#include "rocs/cv/Crfh/CDescriptor.h"
#include <vector>
using std::vector;

//namespace math {
//template<typename _T> class Matrix_;
//}

namespace rocs {

namespace math {
template<typename _T> class Matrix_;
}

namespace cv {

class CDescriptorList: public vector<CDescriptor *> {

public:

	/** Destructor. Deletes all the descriptors. */
	~CDescriptorList();

public:

	/** Adds a new descriptor to the list. The descriptor is characterized
	 by its type, scale, and number of bins. */
	void addDescriptor(DescriptorType descriptorType, double scale, int bins);

	/** Adds a new descriptor to the list. The descriptors is characterized
	 by its name, scale, and number of bins. */
	void addDescriptor(string name, double scale, int bins);

public:

	/** Creates filters requierd by all descriptors. */
	void createAllRequiredFilters(CFilterCache &filterCache) const;

	/** Creates samples of the scale-space requierd by all descriptors. */
	void createAllRequiredScales(CScaleSpaceCache &scaleSpaceCache) const;

	/** Creates channels required by all descriptors. */
	void createAllRequiredChannels(CChannelCache &channelCache) const;

	/** Applies all the descriptors in the list and returns a list of
	 pointers to the output matrices. */
	vector<Matrix_<double>*> applyAll(const CChannelCache &channelCache,
			const CScaleSpaceCache &scaleSpaceCache,
			const CFilterCache &filterCache) const;

};

} // end namespace cv
} // end namespace rocs

#endif /* CDESCRIPTORLIST_H_ */
