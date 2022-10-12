#ifndef WINDOWS_BACKUPHANDLER_HPP
#define WINDOWS_BACKUPHANDLER_HPP

	/* Standard C++ */
	#include <forward_list> // std::forward_list

	/* Boost or STL */
	#include "bosmacros/thread.hpp" // THREAD_CLASS

	/* Our headers */
	#include "BackupInfoList/WindowsBackupInfoList.hpp" // List of Windows-specific backup info objects
	#include "PathBackupCreator/WindowsPathBackupCreator.hpp" // Task class for creating a backup of a path
	#include "BackupHandler/BaseBackupHandler.hpp" // Base class

	namespace windows
	{
		/*
		* A specialization of the backup handler class for Windows. Handles all of the Windows-specific elements of running a backup on Windows.
		*/
		class BackupHandler : public BaseBackupHandler
		{
			public:
				/*
				* \desc Constructor. Builds a backup handler that will backup the paths in the given list, while excluding the given directories and files.
				* \param infoObj The list of paths to backup and their associated exclusion lists.
				*/
				BackupHandler(BackupInfoList infoObj);

			private:
				BackupInfoList backupInfoList; // A reference to the backup info
				std::forward_list<PathBackupCreator> backupCreators; // The list of task objects. Each one backs up a given path
		};
	};

#endif // WINDOWS_BACKUPHANDLER_HPP