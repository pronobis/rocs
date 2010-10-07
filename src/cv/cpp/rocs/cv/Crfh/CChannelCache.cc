/*
 * CChannelCache.cc
 *
 *  Created on: Sep 27, 2010
 *      Author: arnaud
 */

#include "rocs/math/Matrix_.h"
#include "rocs/cv/Img.h"

#include "rocs/cv/Crfh/CChannelCache.h"

namespace rocs {
namespace cv {

// -----------------------------------------
CChannelCache::~CChannelCache() {
	for (unsigned int i = 0; i < _channelList.size(); ++i)
		delete _channelList[i];
}

// -----------------------------------------
void CChannelCache::createChannel(ChannelType channelType) {
	// Check if we don't have the channel in the cache
	for (unsigned int i = 0; i < _channelTypeList.size(); ++i)
		if (_channelTypeList[i] == channelType)
			return;

	// Create a new channel
	Matrix_<double> *channel = _image->getL();

	if (channel) {
		_channelList.push_back(channel);
		_channelTypeList.push_back(channelType);
	}
}

// -----------------------------------------
const Matrix_<double> *CChannelCache::getChannel(ChannelType channelType) const {
	// Find the channel
	for (unsigned int i = 0; i < _channelTypeList.size(); ++i)
		if (_channelTypeList[i] == channelType)
			return _channelList[i];

	rocsDebug1("ERROR: No such channel!");
	return 0;
}

} // end namespace cv
} // end namespace rocs
