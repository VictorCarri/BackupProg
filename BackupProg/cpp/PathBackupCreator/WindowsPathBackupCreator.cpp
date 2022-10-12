/* Standard C++ */
#ifdef _DEBUG
#include <iostream> // std::clog
#endif // _DEBUG
#include <algorithm> // for_each

/* Boost or Standard C++ */
#include "bosmacros/filesystem.hpp" // RECURSIVE_DIRECTORY_ITERATOR, DIRECTORY_OPTIONS

/* Our headers */
#include "BackupPathInfo/WindowsBackupPathInfo.hpp" // Class that holds information about how to backup a particular path on Windows
#include "PathBackupCreator/WindowsPathBackupCreator.hpp" // Class def'n

/*
* \desc Constructor. Creates a new task class that backs up the path named in the given info object.
* \param pathInfo An object that describes the path to be backed up.
*/
windows::PathBackupCreator::PathBackupCreator(windows::BackupPathInfo pathInfo) : BasePathBackupCreator(pathInfo), ourPathInfo(pathInfo) // Construct the base class and store our info
{
}

/*
* \desc Performs the backup. Iterates through all paths under the given path and checks whether any of the file's times are more recent than the last backup time.
*		If at least one of the file's times is more recent than the last backup time, it determines what path on the backup drive this file should be copied to.
*		Then, it copies the file there.
*/
void windows::PathBackupCreator::operator()()
{
#ifdef _DEBUG
	std::clog << "windows::PathBackupCreator::operator(): backing up path " << ourPathInfo.getPathToBackup() << std::endl;
#endif // _DEBUG

	/*
	* Part 1: Build a list of the directories which we'll back up.
	* Iterate over all of the top-level directories, and only store the ones that *don't* match any of the ones we're supposed to skip.
	*/
	DIRECTORY_ITERATOR endIt; // Default construct the iterator to create an end iterator
	DIRECTORY_OPTIONS iterOpts = DIRECTORY_OPTIONS::follow_directory_symlink | DIRECTORY_OPTIONS::skip_permission_denied; // Follow all files, except those for which we'd be denied permission
	DIRECTORY_ITERATOR startIt(ourPathInfo.getPathToBackup(), iterOpts); // Start the iteration at our path, using the options we just set. We use a regular directory iterator to avoid recursing into directories, because that takes too long and then crashes.
	std::for_each(startIt, endIt, [this](DIRECTORY_ENTRY dirEnt) // Check each directory entry
		{
			FILESYSTEM_PATH entPath = dirEnt.path(); // Get the entry's path
#ifdef _DEBUG
			std::clog << entPath << std::endl;
#endif // _DEBUG
		}
	);
}