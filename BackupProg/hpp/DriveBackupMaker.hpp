#ifndef DRIVEBACKUPMAKER_HPP
#define DRIVEBACKUPMAKER_HPP

	/* Standard C++ */
	#include <string> // std::string

	/* Boost */
	#include <boost/thread.hpp>// boost::thread

	/* Our headers */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH
	#include "bosmacros/thread.hpp" // THREAD_CLASS

	/*
	* Creates the backup for a single drive.
	*/
	class DriveBackupMaker
	{
		public:
			/*
			* \desc Constructor. Stores data and starts the process of backing up a drive. Creates the internal thread.
			* \param _drive The path to the drive that we'll be backing up.
			* \backupPath Path to the external drive.
			*/
			DriveBackupMaker(FILESYSTEM_PATH drive, FILESYSTEM_PATH backupPath);

			/*
			* \desc Destructor. Cleans up our resources.
			*/
			~DriveBackupMaker();

		private:

			/*
			* \desc Backs up the drive.
			*/
			void runBackup();

			FILESYSTEM_PATH backupDrivePath; // Path to drive where backups are stored
			FILESYSTEM_PATH folderToBackup; // Path to folder to backup
			THREAD_CLASS worker; // The thread which runs the backup function in the background
	};

#endif // DRIVEBACKUPMAKER_HPP