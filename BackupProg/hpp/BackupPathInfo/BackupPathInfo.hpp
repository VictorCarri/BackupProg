#ifndef BACKUPPATHINFO_HPP
#define BACKUPPATHINFO_HPP

	/* Boost or STL */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH, IFSTREAM

	/**
	* Stores information about a path that needs to be backed up.
	* Also stores information about the directories and files that should be skipped while backing up the path.
	**/
	class BackupPathInfo
	{
		private:
			FILESYSTEM_PATH itemPath; // Path of the drive/directory to be backed up (depending on whether we're running on Linux or Windows)
	};

#endif // !BACKUPPATHINFO_HPP