#ifndef BASEBACKUPPATHINFO_HPP
#define BASEBACKUPPATHINFO_HPP

	/* Standard C++ */
	#include <forward_list> // std::forward_list

	/* Boost or STL */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH
	#include "bosmacros/regex.hpp" // REGEX

	/*
	* Base class for classes that store backup info. Meant to be specialized by classes for each OS.
	*/
	class BaseBackupPathInfo
	{
		public:
			/*
			* \desc Constructor. Stores the path which we store info about.
			* \param backupPath The path which we store info about.
			*/
			BaseBackupPathInfo(FILESYSTEM_PATH backupPath);

			/*
			* \desc Fetches the path whose backup info we describe.
			* \return The path whose backup info we describe.
			*/
			FILESYSTEM_PATH getPathToBackup() const;

		protected:
			FILESYSTEM_PATH pathToBackup; // The path that we store backup information about
			std::forward_list<REGEX> dirRegs; // List of regexes that describe directories under this path that we should skip
			std::forward_list<REGEX> fileRegs; // List of regexes that describe files under this path that we should skip
	};

#endif // BASEBACKUPPATHINFO_HPP