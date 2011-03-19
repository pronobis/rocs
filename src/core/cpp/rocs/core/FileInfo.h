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
 * \file FileInfo.h
 *
 * \date Mar 19, 2011
 * \author Andrzej Pronobis
 */

#ifndef _ROCS_CORE_FILEINFO_H_
#define _ROCS_CORE_FILEINFO_H_

// Stl & Boost
#define BOOST_FILESYSTEM_VERSION 2
#include <boost/filesystem.hpp>

namespace rocs {
namespace core {

/*!
 * This class provides file information.
 */
class FileInfo
{
public:

	/*! Default constructor, create and instance of
	 * FileInfo not lined to any file. */
	FileInfo();

	/*! Constructor, creates FileInfo for a specific file path. */
	FileInfo(std::string filePath) : _path(filePath)
	{}

	/*! Sets file path for this FileInfo. */
	void setFilePath(std::string filePath)
	{ _path = filePath; }

	/*! Returns true if the object points to existing entity. */
	bool exists()
	{ return boost::filesystem::exists(_path); }

	/*! Returns true if the object points to a
	 * file, but not a symlink to a file. */
	bool isFile()
	{ return boost::filesystem::is_regular_file(_path); }

	/*! Returns true if the object points to a directory
	 * or symlink to a directory. */
	bool isDir()
	{ return boost::filesystem::is_directory(_path); }

	/*! Returns true if the object points to an existing file. */
	bool fileExists()
	{ return exists()&&isFile(); }

	/*! Returns true if the object points to an existing directory. */
	bool dirExists()
	{ return exists()&&isDir(); }


public:

	/*! Helper function using the fileExists() method on a given file. */
	static bool fileExists(std::string filePath)
	{ return FileInfo(filePath).fileExists(); }


private:

	boost::filesystem::path _path;

};

}
}

#endif /* _ROCS_CORE_FILEINFO_H_ */
