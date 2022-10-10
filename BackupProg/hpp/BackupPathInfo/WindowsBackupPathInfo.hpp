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
				* \desc skipDirs JSON array of directory paths relative to our backup path that we should skip backing up.
				* \desc skipFiles JSON array of file paths relative to our backup path that we should skip backing up.
				* \param backupPath The path we store info about.
				*/
				BackupPathInfo(FILESYSTEM_PATH backupPath, boost::json::array skipDirs, boost::json::array skipFiles);

			private:
				/*
				* \desc Converts the given filesystem path to a regex
				*		Doubles slashes so that the regex parser won't interpret them as the start of an escape sequence.
				*/
				REGEX pathToRegex(FILESYSTEM_PATH path);
		};
	};

#endif // !WINDOWSBACKUPPATHINFO_HPP