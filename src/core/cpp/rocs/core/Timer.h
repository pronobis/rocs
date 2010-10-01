/*
 * Timer.h
 *
 *  Created on: Jul 15, 2010
 *      Author: arnaud
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>
#include <string>
#include <iostream>
using namespace std;


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
