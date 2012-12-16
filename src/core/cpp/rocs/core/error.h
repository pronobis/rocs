// ===============================================================================
// ROCS - Toolkit for Robots Comprehending Space
// Copyright (c) 2010-2012, the ROCS authors. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met: 
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution. 
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ===============================================================================

/*!
 * Exceptions and macros for reporting errors.
 * \file error.h
 * \author Andrzej Pronobis, Arnaud Ramey
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
 * The I/O exception class.
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
		return "I/O error: " + error;
	}
};


/*!
 * Exception thrown when the uniqueness condition is violated.
 */
class UniquenessException: public Exception
{
public:

	/*! Constructor setting values of the error location and message. */
	UniquenessException(const std::string& where, const std::string& error) :
		Exception(where, error)
	{
	}

	/*!
	 * Creates formatted error message based on the information
	 * in the exception.
	 */
	virtual std::string formatMessage(std::string error) throw ()
	{
		return "Uniqueness error: " + error;
	}
};


/*!
 * Exception thrown when value conversion cannot be performed.
 */
class ConversionException: public Exception
{
public:

	/*! Constructor setting values of the error location and message. */
	ConversionException(const std::string& where, const std::string& error) :
		Exception(where, error)
	{
	}

	/*!
	 * Creates formatted error message based on the information
	 * in the exception.
	 */
	virtual std::string formatMessage(std::string error) throw ()
	{
		return "Conversion error: " + error;
	}
};


/*!
 * Exception thrown when the type of an object does not match the operation.
 */
class TypeException: public Exception
{
public:

	/*! Constructor setting values of the error location and message. */
	TypeException(const std::string& where, const std::string& error) :
		Exception(where, error)
	{
	}

	/*!
	 * Creates formatted error message based on the information
	 * in the exception.
	 */
	virtual std::string formatMessage(std::string error) throw ()
	{
		return "Conversion error: " + error;
	}
};


/*! Convertion to string. */
#define ROCS_ERROR_STRINGIFY(x) #x
#define ROCS_ERROR_TO_STRING(x) ROCS_ERROR_STRINGIFY(x)

/*!
 * Information about this location.
 */
#ifdef __GNUC__
#define __ROCS_HERE__ 	std::string(__PRETTY_FUNCTION__)+"@"+__FILE__+":"+ROCS_ERROR_TO_STRING(__LINE__)
#else
#define __ROCS_HERE__	std::string(__FILE__)+":"+ROCS_ERROR_TO_STRING(__LINE__)
#endif

/*!
 * Allows to format an error message in the printf-like fashion.
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
/*! Convenience macro throwing a uniqueness exception. */
#define rocsUniquenessException( ... ) {\
		rocs::core::UniquenessException e (__ROCS_HERE__, rocs::core::errMsg(__VA_ARGS__)); \
		rocsDebug3("UniquenessException '%s'", e.what()); \
		throw e; \
		}
/*! Convenience macro throwing a conversion exception. */
#define rocsConversionException( ... ) {\
		rocs::core::ConversionException e (__ROCS_HERE__, rocs::core::errMsg(__VA_ARGS__)); \
		rocsDebug3("ConversionException '%s'", e.what()); \
		throw e; \
		}
/*! Convenience macro throwing a type exception. */
#define rocsTypeException( ... ) {\
		rocs::core::TypeException e (__ROCS_HERE__, rocs::core::errMsg(__VA_ARGS__)); \
		rocsDebug3("TypeException '%s'", e.what()); \
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
