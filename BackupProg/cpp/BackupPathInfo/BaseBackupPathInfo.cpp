/* Boost or STL */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

/* Our headers */
#include "BackupPathInfo/BaseBackupPathInfo.hpp" // Class def'n

/*
* \desc Fetches the path whose backup info we describe.
* \return The path whose backup info we describe.
*/
FILESYSTEM_PATH BaseBackupPathInfo::getPathToBackup() const
{
	return pathToBackup;
}

/*
* \desc Constructor. Stores the path which we store info about.
* \param backupPath The path which we store info about.
*/
BaseBackupPathInfo::BaseBackupPathInfo(FILESYSTEM_PATH backupPath) : pathToBackup(backupPath)
{
}