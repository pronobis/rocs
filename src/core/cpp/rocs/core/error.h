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
 * Exceptions and macros for reporting errors.
 * \file error.h
 * \author Arnaud Ramey, Andrzej Pronobis
 */


#ifndef _ROCS_CORE_ERROR_H_
#define _ROCS_CORE_ERROR_H_

// Stl & Std
#include <iostream>
#include <stdio.h>   // for sprintf()
#include <stdlib.h>  // for exit()
#include <stdarg.h>  // for vargs


namespace rocs {
namespace core {

// Debug level
#ifndef ROCS_DEBUG_LEVEL
	#define ROCS_DEBUG_LEVEL 0
#endif


/*!
 * The generic exception class.
 */
class Exception: public std::exception
{
public:

	/*! Default constructor. */
	Exception()
	{}

	/*! Constructor setting values of the error location and message. */
	Exception(const std::string& where, const std::string& error)
	{
		message = "[" + where +"] " + formatMessage(error);
	}

	/*! Destructor. */
	virtual ~Exception() throw ()
	{}

	/*! The final formatted message that should be displayed. */
	std::string message;

	/*! Returns the output error message. */
	virtual const char *what() const throw ()
	{
		return message.c_str();
	}

	/*!
	 * Creates formatted error message based on the information
	 * in the exception.
	 */
	virtual std::string formatMessage(std::string error) throw ()
	{
		return "Error: " + error;
	}
};


/*!
 * The assertion exception class.
 */
class AssertionException: public Exception
{
public:

	/*! Constructor setting values of the error location and message. */
	AssertionException(const std::string& where, const std::string& error):
		Exception(where, error)
	{}

	/*!
	 * Creates formatted error message based on the information
	 * in the exception.
	 */
	virtual std::string formatMessage(std::string error) throw ()
	{
		return "Assertion: " + error;
	}
};


/*! Convertion to string. */
#define ROCS_ERROR_STRINGIFY(x) #x
#define ROCS_ERROR_TO_STRING(x) ROCS_ERROR_STRINGIFY(x)


/*!
 * The primitive macro for debugging
 * Accepts message in the printf like fashion.
 */
#ifdef __GNUC__
	#define __HERE__ 	std::string(__PRETTY_FUNCTION__)+"@"+__FILE__+":"+ROCS_ERROR_TO_STRING(__LINE__)
#else
	#define __HERE__	std::string(__FILE__)+":"+ROCS_ERROR_TO_STRING(__LINE__)
#endif


/*!
 * Allows to format an error message in the printf-like fashion.
 * From OpenCV.
 */
static inline std::string errMsg(const char* fmt, ...)
{
	char buf[1 << 16];
	va_list args;
	va_start( args, fmt );
	vsprintf( buf, fmt, args );
	return std::string(buf);
}


/*!
 * Routine used for fatal errors.
 * Displays messages and kills the process.
 * \param exc the Exception to cast
 */
static inline void exitWithError(const Exception& exc)
{
	std::cout << exc.message << std::endl;
	exit(-1);
}


/*!
 * Macro reporting a fatal error.
 */
#define rocsError( ... ) \
		rocs::core::exitWithError(rocs::core::Exception(__HERE__, rocs::core::errMsg(__VA_ARGS__)) )

/*!
 * Macro defining an assertion.
 */
#define rocsAssert( expr ) { if(!(expr)) \
		rocs::core::exitWithError( rocs::core::AssertionException(__HERE__, #expr) ); }

/*!
 * Convenience macro throwing a general exception.
 */
#define rocsException( ... ) \
		throw rocs::core::Exception(__HERE__, rocs::core::errMsg(__VA_ARGS__))

/*!
 * Macro defining an assertion used only when debugging.
 */
#define rocsDebugAssert( expr ) { if ((ROCS_DEBUG_LEVEL > 0 ) && (!(expr))) \
		rocs::core::exitWithError( rocs::core::AssertionException(__HERE__, #expr) ); }


} // namespace core
} // namespace rocs


#endif /* ROCS_CORE_ERROR_H_ */
