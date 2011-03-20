// ==================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (C) 2011  Andrzej Pronobis
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
 * \file ShalowCopyable.h
 *
 * \date Mar 20, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_CORE_SHALLOWCOPYABLE_H_
#define _ROCS_CORE_SHALLOWCOPYABLE_H_

#include <boost/smart_ptr.hpp>

namespace rocs {
namespace core {


/*!
 * This class easily implements the shallow copy mechanism
 * in another class that derives from it.
 */
template <class Data>
class ShallowCopyable
{

protected:

	/*! Constructor, stores the pointer to data. */
	ShallowCopyable(Data *d = 0) : _d(d)
	{}

	/*! Returns true if the pointer to data is null. */
	bool isNull()
	{ return !_d; }


protected:

	/*! Pointer to shared data. */
	boost::shared_ptr<Data> _d;

};


}
}

#endif /* _ROCS_CORE_SHALLOWCOPYABLE_H_ */
