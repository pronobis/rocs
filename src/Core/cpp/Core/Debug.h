/*
 * Debug.h
 *
 * Here we define the macros to print some information
 * when DEBUG_LEVEL is >= 0
 *
 *  Created on: Aug 10, 2010
 *      Author: arnaud
 */

#ifndef DEBUG_H_
#define DEBUG_H_

namespace rocs {
namespace core {

// debugging macros so we can pin down message provenance at a glance
#define WHERESTR  "[%s:%d]:"
#define WHEREARG  __FILE__, __LINE__
#define DEBUGPRINTF(_fmt, ...)  fprintf(stdout, WHERESTR _fmt "\n", WHEREARG, __VA_ARGS__)
#define DEBUGPRINT(_string)     DEBUGPRINTF("%s", _string)
// the primitive functions for debugging
#define debugPrint( level, _string )    \
	if ( DEBUG_LEVEL >= level ) DEBUGPRINT(_string)
#define debugPrintf( level, _fmt, ... ) \
	if ( DEBUG_LEVEL >= level ) DEBUGPRINTF(_fmt, __VA_ARGS__)

// define debugPrint() and debugPrintf() for each level of verbosity
#define debugPrint_lvl1( _string)       debugPrint(1, _string)
#define debugPrintf_lvl1( _fmt, ...)    debugPrintf(1, _fmt, __VA_ARGS__)
#define debugPrint_lvl2( _string)       debugPrint(2, _string)
#define debugPrintf_lvl2( _fmt, ...)    debugPrintf(2, _fmt, __VA_ARGS__)
#define debugPrint_lvl3( _string)       debugPrint(3, _string)
#define debugPrintf_lvl3( _fmt, ...)    debugPrintf(3, _fmt, __VA_ARGS__)

} // namespace core
} // namespace rocs


#endif /* DEBUG_H_ */
