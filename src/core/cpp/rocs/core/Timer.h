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
 * \file Timer.h
 *
 * \date Jul 15, 2010
 * \author Arnaud Ramey, Andrzej Pronobis
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>
#include <string>
#include <iostream>
using namespace std;


/*!
 * a timer class
 */
//!  A test class.
/*!
  A more elaborate class description.
*/

class Timer {
public:
	Timer() {
		reset();
	}
	~Timer() {
	}

	inline void reset() {
		gettimeofday(&start, NULL);
		usleep(2000);
	}

	inline long getTimeMilliseconds() {
		gettimeofday(&end, NULL);

		seconds = end.tv_sec - start.tv_sec;
		useconds = end.tv_usec - start.tv_usec;
		mtime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;
		//printf("Elapsed time: %ld milliseconds\n", mtime);
		return mtime;
	}

	inline long time() {
		return getTimeMilliseconds();
	}

	inline void printTime(string msg) {
		cout << "Time for " << msg << " : " << getTimeMilliseconds()
				<< " ms." << endl;
	}

private:
	struct timeval start, end;
	long mtime, seconds, useconds;
};

#endif /* TIMER_H_ */
