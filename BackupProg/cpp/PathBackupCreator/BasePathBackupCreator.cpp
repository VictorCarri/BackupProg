/* Our headers */
#include "BackupPathInfo/BaseBackupPathInfo.hpp" // Backup path info class
#include "PathBackupCreator/BasePathBackupCreator.hpp" // Class def'n

/*
* \desc Constructor. Stores the given path info.
* \desc toStore The path info object that describes the path we should backup.
*/
BasePathBackupCreator::BasePathBackupCreator(BaseBackupPathInfo toStore) : pathInfo(toStore)
{
}