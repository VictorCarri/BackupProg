/* Standard C++ */
#include <ostream> // std::ostream

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
* \param skipDirs JSON array of directory paths relative to our backup path that we should skip backing up.
* \param skipFiles JSON array of file paths relative to our backup path that we should skip backing up.
*/
BaseBackupPathInfo::BaseBackupPathInfo(FILESYSTEM_PATH backupPath, boost::json::array skipDirs, boost::json::array skipFiles) : pathToBackup(backupPath)
{
}

/*
* \desc Writes this object to an output stream.
* \param out The output stream that this object will write itself to.
* \param bbpi The object to be written to the stream.
* \returns The stream, to enable chaining.
*/
std::ostream& operator<<(std::ostream& out, const BaseBackupPathInfo& bbpi)
{
	out << "Backup path info object for path " << bbpi.pathToBackup << std::endl;
	return out;
}