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
 * \file ChannelCache.h
 *
 * \date Sep 27, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 *
 * Contains declaration of the ChannelCache class.
 */

#ifndef CCHANNELCACHE_H_
#define CCHANNELCACHE_H_

#include <vector>

namespace rocs {
namespace math {
template<typename _T> class Matrix_;
}

namespace cv {

//using rocs::math::Matrix_;
//template<class _T> class Matrix_;
class Img;

enum ChannelType {
	CT_UNKNOWN = 0, CT_L, CT_C1, CT_C2
};

/*!
 * Class storing a cache of channels.
 */
class ChannelCache {

public:

	/*! Default constructor. */
	inline ChannelCache(const Img &image) :
		_image(&image) {
	}
	;

	/*! Destructor. Deletes all the channels. */
	~ChannelCache();

public:

	/*! Creates a new channel on the basis of the input image.
	 If an identical channel already exists a new one will
	 not be created. */
	void createChannel(ChannelType channelType);

	/*! Returns a pointer to a matrix containing pixels of the channel. */
	const math::Matrix_<double> *getChannel(ChannelType channelType) const;

private:

	/*! Pointer to the input image. */
	const Img* _image;

	/*! List storing pointers to channels. */
	std::vector<math::Matrix_<double> *> _channelList;

	/*! List of types of channels in the _channelList. */
	std::vector<ChannelType> _channelTypeList;
};

} // end namespace cv
} // end namespace rocs

#endif /* CCHANNELCACHE_H_ */
