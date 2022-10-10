#ifndef WINDOWSBACKUPPATHINFO_HPP
#define WINDOWSBACKUPPATHINFO_HPP

	/* Boost */
	#include <boost/json.hpp> // boost::json::array

	/* Boost or STL */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH
	#include "bosmacros/regex.hpp" // REGEX, MATCH_RESULTS, REGEX_REPLACE

	/* Our headers */
	#include "BackupPathInfo/BaseBackupPathInfo.hpp" // Base class

	namespace windows
	{
		class BackupPathInfo : public BaseBackupPathInfo
		{
			public:
				/*
				* \desc Constructor. Initializes our base class and stores the path we store info about.
				* \param skipDirs JSON array of directory paths relative to our backup path that we should skip backing up.
				* \param skipFiles JSON array of file paths relative to our backup path that we should skip backing up.
				* \param backupPath The path we store info about.
				*/
				BackupPathInfo(FILESYSTEM_PATH backupPath, boost::json::array skipDirs, boost::json::array skipFiles);

			private:
				/*
				* \desc Converts the given filesystem path to a regex
				*		Doubles slashes so that the regex parser won't interpret them as the start of an escape sequence.
				*/
				REGEX pathToRegex(FILESYSTEM_PATH path);

				/*
				* \desc Creates regexes for either directory or file paths that we should skip.
				* \param forDirs True if we create directory regexes, false if we should create file regexes.
				* \param skipList List of directories or files that we should skip.
				* \param backupPath The path this object stores info about.
				*/
				void createRegs(bool forDirs, boost::json::array skipList, FILESYSTEM_PATH backupPath);
		};
	};

#endif // !WINDOWSBACKUPPATHINFO_HPP