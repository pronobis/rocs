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
 * \file ChannelCache.cc
 *
 * \date Sep 27, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#include "rocs/cv/Img.h"

#include "rocs/cv/Crfh/ChannelCache.h"

namespace rocs {
namespace cv {

// -----------------------------------------
ChannelCache::~ChannelCache() {
	for (unsigned int i = 0; i < _channelList.size(); ++i)
		delete _channelList[i];
}

// -----------------------------------------
void ChannelCache::createChannel(ChannelType channelType) {
	// Check if we don't have the channel in the cache
	for (unsigned int i = 0; i < _channelTypeList.size(); ++i)
		if (_channelTypeList[i] == channelType)
			return;

	// Create a new channel
	math::Matrix_<double> *channel = _image->getL();

	if (channel) {
		_channelList.push_back(channel);
		_channelTypeList.push_back(channelType);
	}
}

// -----------------------------------------
const math::Matrix_<double> *ChannelCache::getChannel(ChannelType channelType) const {
	// Find the channel
	for (unsigned int i = 0; i < _channelTypeList.size(); ++i)
		if (_channelTypeList[i] == channelType)
			return _channelList[i];

	rocsDebug1("ERROR: No such channel!");
	return 0;
}

} // end namespace cv
} // end namespace rocs
