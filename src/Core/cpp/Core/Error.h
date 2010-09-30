/*
 * Error.h
 *
 *  Created on: Jul 14, 2010
 *      Author: arnaud
 */

#ifndef ERROR_H_
#define ERROR_H_

// we have to keep the C includes here otherwise cannot compile
#include <iostream>
#include <stdio.h>   // for sprintf()
#include <stdlib.h>  // for exit()
using namespace std;

/* ***************************************************************************
 *  Error codes taken from OpenCV
 */
#define StsAssert                 -215 /* assertion failed */

/* ***************************************************************************/

namespace rocs {
namespace core {

/**
 * the exception class
 */

class Exception: public std::exception {
public:
	Exception() {
		code = 0;
		line = 0;
	}
	Exception(int _code, const string& _err, const string& _func,
			const string& _file, int _line) :
		code(_code), err(_err), func(_func), file(_file), line(_line) {
		formatMessage();
	}

	virtual ~Exception() throw () {
	}

	string msg;

	int code;
	string err;
	string func;
	string file;
	int line;

	virtual const char *what() const throw () {
		return msg.c_str();
	}

	void formatMessage() {
		char buffer[300];
		if (func.size() > 0)
			sprintf(buffer, "%s:%d: error: (%d) '%s' in function \"%s()\"\n",
					file.c_str(), line, code, err.c_str(), func.c_str());
		else
			sprintf(buffer, "%s:%d: error: (%d) '%s'\n", file.c_str(), line,
					code, err.c_str());
		msg = string(buffer);
	}

};

/**
 * the error routine
 * \param exc the Exception to cast
 */
static inline void error(const Exception& exc) {
	std::cout << exc.msg << std::endl;
	exit(exc.code);
}

/*
 * errors and assert
 */
#ifdef __GNUC__
#define Error( code, msg ) \
	rocs::core::error( rocs::core::Exception(code, msg, __func__, __FILE__, __LINE__) )
#define Error_( code, args ) \
	rocs::core::error( rocs::core::Exception(code, format args, __func__, __FILE__, __LINE__) )
#define Assert( expr ) { if(!(expr)) \
	rocs::core::error( rocs::core::Exception(StsAssert, #expr, __func__, __FILE__, __LINE__) ); }
#else
#define Error( code, msg ) \
	rocs::core::error( rocs::core::Exception(code, msg, "", __FILE__, __LINE__) )
#define Error_( code, args ) \
	rocs::core::error( rocs::core::Exception(code, format args, "", __FILE__, __LINE__) )
#define Assert( expr ) { if(!(expr)) \
	rocs::core::error( rocs::core::Exception(StsAssert, #expr, "", __FILE__, __LINE__) ); }
#endif

/* code from OpenCV */
//#ifdef __GNUC__
//#define CV_Error( code, msg ) cv::error( cv::Exception(code, msg, __func__, __FILE__, __LINE__) )
//#define CV_Error_( code, args ) cv::error( cv::Exception(code, cv::format args, __func__, __FILE__, __LINE__) )
//#define CV_Assert( expr ) { if(!(expr)) cv::error( cv::Exception(CV_StsAssert, #expr, __func__, __FILE__, __LINE__) ); }
//#else
//#define CV_Error( code, msg ) cv::error( cv::Exception(code, msg, "", __FILE__, __LINE__) )
//#define CV_Error_( code, args ) cv::error( cv::Exception(code, cv::format args, "", __FILE__, __LINE__) )
//#define CV_Assert( expr ) { if(!(expr)) cv::error( cv::Exception(CV_StsAssert, #expr, "", __FILE__, __LINE__) ); }
//#endif

/*
 * asserts if debug mode
 */
#ifdef _DEBUG
#define DbgAssert(expr) Assert(expr)
#else
#define DbgAssert(expr)
#endif

} // namespace core
} // namespace rocs


#endif /* ERROR_H_ */
