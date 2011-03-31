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
 * \file Factor.cc
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */


#include "rocs/ml/Factor.h"

namespace rocs {
namespace ml {

using namespace cv;
using namespace std;

std::ostream& operator<<(std::ostream &out, const Factor &f)
{
	out << "Factor id:" << f.id()<< " name:"<< f.name()<<std::endl;
    if (f.potentials().dims<=2)
    {
    	out << f.potentials();
    }
    else
	{
    	for (size_t i=0; i<f.potentials().total(); ++i)
    		out << reinterpret_cast<double*>(f.potentials().data)[i]<<" ";
		out <<endl;
	}

    out << std::endl;
    return out;
}



}
}
