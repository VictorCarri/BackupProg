/* C++ versions of C headers*/
#ifdef _DEBUG
#include <cstdlib> // std::exit
#endif
#include <cctype> // std::tolower

/* Standard C++ */
#include <string> // std::string
#include <algorithm> // std::for_each
#include <iterator> // std::advance
#include <stdexcept> // std::runtime_error
#ifdef _DEBUG // Debug build
#include <iostream> // std::clog, std::endl
#include <sstream> // std::ostringstream
#include "ExitCodes.hpp"
#endif

/* Boost */
#include <boost/thread.hpp> // boost::thread

/* Our includes */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH
#include "bosmacros/thread.hpp" // THREAD_CLASS
#include "DriveBackupMaker.hpp" // Class declaration

/*
* \desc Constructor. Stores data and starts the process of backing up a drive. Creates the internal thread.
* \param _drive The path to the drive that we'll be backing up.
* \backupPath Path to the external drive.
*/
DriveBackupMaker::DriveBackupMaker(FILESYSTEM_PATH drive, FILESYSTEM_PATH backupPath) : folderToBackup(drive), backupDrivePath(backupPath)
{
#ifdef _DEBUG
	std::clog << "DriveBackupMaker::DriveBackupMaker: drivePath = " << folderToBackup << std::endl;
#endif

	worker = THREAD_CLASS(&DriveBackupMaker::runBackup, this); // Start the backup in the background
}

/*
* \desc Destructor. Cleans up our resources.
*/
DriveBackupMaker::~DriveBackupMaker()
{
	worker.join(); // End our thread
}

/*
* \desc Backs up the drive.
*/
void DriveBackupMaker::runBackup()
{
#ifdef _DEBUG
	std::clog << "DriveBackupMaker::runBackup starting backup of path " << folderToBackup << "." << std::endl;
#endif

#ifdef _DEBUG
	std::clog << "DriveBackupMaker::runBackup ending backup of path " << folderToBackup << "." << std::endl;
#endif
}