#ifndef BASEBACKUPPATHINFO_HPP
#define BASEBACKUPPATHINFO_HPP

	/* Standard C++ */
	#include <forward_list> // std::forward_list
	#include <ostream> // std::ostream

	/* Boost or STL */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH
	#include "bosmacros/regex.hpp" // REGEX

	/* Boost */
	#include <boost/json.hpp> // boost::json::array

	/*
	* Base class for classes that store backup info. Meant to be specialized by classes for each OS.
	*/
	class BaseBackupPathInfo
	{
		public:
			/*
			* \desc Constructor. Stores the path which we store info about.
			* \param backupPath The path which we store info about.
			* \param skipDirs JSON array of directory paths relative to our backup path that we should skip backing up.
			* \param skipFiles JSON array of file paths relative to our backup path that we should skip backing up.
			*/
			BaseBackupPathInfo(FILESYSTEM_PATH backupPath, boost::json::array skipDirs, boost::json::array skipFiles);

			/*
			* \desc Fetches the path whose backup info we describe.
			* \return The path whose backup info we describe.
			*/
			FILESYSTEM_PATH getPathToBackup() const;

			/*
			* \desc Default virtual destructor, just in case.
			*/
			virtual ~BaseBackupPathInfo() = default;

			/*
			* \desc Writes this object to an output stream.
			* \param out The output stream that this object will write itself to.
			* \param bbpi The object to be written to the stream.
			* \returns The stream, to enable chaining.
			*/
			friend std::ostream& operator<<(std::ostream& out, const BaseBackupPathInfo& bbpi);

		protected:
			FILESYSTEM_PATH pathToBackup; // The path that we store backup information about
			std::forward_list<REGEX> dirRegs; // List of regexes that describe directories under this path that we should skip
			std::forward_list<REGEX> fileRegs; // List of regexes that describe files under this path that we should skip
	};

#endif // BASEBACKUPPATHINFO_HPP