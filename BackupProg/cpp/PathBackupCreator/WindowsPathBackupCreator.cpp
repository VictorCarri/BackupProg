/* Standard C++ */
#ifdef _DEBUG
#include <iostream> // std::clog
#endif // _DEBUG


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

}