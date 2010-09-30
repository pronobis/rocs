/*
 * Core.h
 *
 *  Created on: Jul 14, 2010
 *      Author: arnaud
 */

#ifndef CORE_H_
#define CORE_H_

// defining _DEBUG will enable all the debug tests
#define _DEBUG

// do we want to print debug infos ?
// define between 0 (no debug infos), 1 (important warnings),
// 2 (most of debug infos), and 3 (max verbosity)
#define DEBUG_LEVEL 3

/* STD includes */
#include <iostream>
#include <stdio.h>      // for sprintf()
#include <stdlib.h>     // for exit()
using namespace std;


#include "Debug.h"
#include "Error.h"
#include "Utils.h"

#endif /* CORE_H_ */
