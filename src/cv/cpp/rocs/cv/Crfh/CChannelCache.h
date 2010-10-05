/*
 * CChannelCache.h
 *
 *  Created on: Sep 27, 2010
 *      Author: arnaud
 */

#ifndef CCHANNELCACHE_H_
#define CCHANNELCACHE_H_
/*!
 * \file CChannelCache.h
 * \author Andrzej Pronobis
 *
 * Contains declaration of the CChannelCache class.
 */

#include <vector>

namespace rocs {
namespace math {
template<typename _T> class Matrix_;
}

namespace cv {

using rocs::math::Matrix_;
//template<class _T> class Matrix_;
class Img;

enum ChannelType {
	CT_UNKNOWN = 0, CT_L, CT_C1, CT_C2
};

/*!
 * Class storing a cache of channels.
 */
class CChannelCache {

public:

	/*! Default constructor. */
	inline CChannelCache(const Img &image) :
		_image(&image) {
	}
	;

	/*! Destructor. Deletes all the channels. */
	~CChannelCache();

public:

	/*! Creates a new channel on the basis of the input image.
	 If an identical channel already exists a new one will
	 not be created. */
	void createChannel(ChannelType channelType);

	/*! Returns a pointer to a matrix containing pixels of the channel. */
	const Matrix_<double> *getChannel(ChannelType channelType) const;

private:

	/*! Pointer to the input image. */
	const Img* _image;

	/*! List storing pointers to channels. */
	std::vector<Matrix_<double> *> _channelList;

	/*! List of types of channels in the _channelList. */
	std::vector<ChannelType> _channelTypeList;
};

} // end namespace cv
} // end namespace rocs

#endif /* CCHANNELCACHE_H_ */
