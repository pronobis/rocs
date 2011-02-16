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

// rocs
#include "rocs/core/debug.h"

// Stl & Std
#include <iostream>
#include <stdio.h>   // for sprintf()
#include <stdlib.h>  // for exit()
#include <stdarg.h>  // for vargs
namespace rocs
{
namespace core
{

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
	{
	}

	/*! Constructor setting values of the error location and message. */
	Exception(const std::string& where, const std::string& error)
	{
		message = "[" + where + "] " + formatMessage(error);
	}

	/*! Destructor. */
	virtual ~Exception() throw ()
	{
	}

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
	AssertionException(const std::string& where, const std::string& error) :
		Exception(where, error)
	{
	}

	/*!
	 * Creates formatted error message based on the information
	 * in the exception.
	 */
	virtual std::string formatMessage(std::string error) throw ()
	{
		return "Assertion: " + error;
	}
};

/*!
 * The IO exception class.
 */
class IOException: public Exception
{
public:

	/*! Constructor setting values of the error location and message. */
	IOException(const std::string& where, const std::string& error) :
		Exception(where, error)
	{
	}

	/*!
	 * Creates formatted error message based on the information
	 * in the exception.
	 */
	virtual std::string formatMessage(std::string error) throw ()
	{
		return "IO: " + error;
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
#define __ROCS_HERE__ 	std::string(__PRETTY_FUNCTION__)+"@"+__FILE__+":"+ROCS_ERROR_TO_STRING(__LINE__)
#else
#define __ROCS_HERE__	std::string(__FILE__)+":"+ROCS_ERROR_TO_STRING(__LINE__)
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
	vsprintf(buf, fmt, args);
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
		rocs::core::exitWithError(rocs::core::Exception(__ROCS_HERE__, rocs::core::errMsg(__VA_ARGS__)) )

/*!
 * Macro defining an assertion.
 */
#define rocsAssert( expr ) { if(!(expr)) \
		rocs::core::exitWithError( rocs::core::AssertionException(__ROCS_HERE__, #expr) ); }

/*! Convenience macro throwing a general exception. */
#define rocsException( ... ) {\
		rocs::core::Exception e (__ROCS_HERE__, rocs::core::errMsg(__VA_ARGS__)); \
		rocsDebug3("Exception '%s'", e.what()); \
		throw e; \
		}
/*! Convenience macro throwing an IO exception. */
#define rocsIOException( ... ) {\
		rocs::core::IOException e (__ROCS_HERE__, rocs::core::errMsg(__VA_ARGS__)); \
		rocsDebug3("IOException '%s'", e.what()); \
		throw e; \
		}
/*!
 * Macro defining an assertion used only when debugging.
 */
#define rocsDebugAssert( expr ) { if ((ROCS_DEBUG_LEVEL > 0 ) && (!(expr))) \
		rocs::core::exitWithError( rocs::core::AssertionException(__ROCS_HERE__, #expr) ); }

} // namespace core
} // namespace rocs


#endif /* _ROCS_CORE_ERROR_H_ */
