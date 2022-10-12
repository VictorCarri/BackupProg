/* Standard C++ */
#include <algorithm> // std::transform
#include <iterator> // std::front_inserter
#include <forward_list> // std::forward_list

/* Boost or STL */
#include "bosmacros/thread.hpp" // THREAD_CLASS

/* Our headers */
#include "BackupHandler/BaseBackupHandler.hpp" // Base class
#include "BackupHandler/WindowsBackupHandler.hpp" // Class def'n
#include "BackupInfoList/WindowsBackupInfoList.hpp" // List of Windows-specific backup info objects
#include "PathBackupCreator/WindowsPathBackupCreator.hpp" // Task class that creates a backup of a single path

/*
* \desc Constructor. Builds a backup handler that will backup the paths in the given list, while excluding the given directories and files.
* \param infoObj The list of paths to backup and their associated exclusion lists.
*/
windows::BackupHandler::BackupHandler(windows::BackupInfoList infoObj) : BaseBackupHandler(infoObj), backupInfoList(infoObj)
{
	/* Go through the list of path info objects and create a thread for each. */
	std::transform(backupInfoList.cbegin(), backupInfoList.cend(), std::front_inserter(backupThreads), [this](windows::BackupInfoList::value_type pathInfoObj) -> THREAD_CLASS
		{
			/* Create a thread that will backup the current path */
			backupCreators.push_front(windows::PathBackupCreator(pathInfoObj)); // Create a new backup creator for this path
			return THREAD_CLASS(&windows::PathBackupCreator::operator(), backupCreators.front()); // Start a new thread that runs the backup creator by calling its function call operator.
				// This backs up this path.
		}
	);
}