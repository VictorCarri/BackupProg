/* Standard C++ */
#include <ostream> // std::ostream
#include <string> // std::wstring

/* Standard C++ */
#ifdef _DEBUG
#include <iostream> // std::clog
#endif // _DEBUG


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
* \param skipFiles JSON array of file paths relative to our backup path that we should skip backing up.
*/
BaseBackupPathInfo::BaseBackupPathInfo(FILESYSTEM_PATH backupPath, boost::json::array skipFiles) : pathToBackup(backupPath)
{
	/* Add slashes to the backup path if it's a drive name and doesn't have them */
	if (!pathToBackup.has_root_directory()) // Just a drive name
	{
#ifdef _DEBUG
		std::clog << "BaseBackupPathInfo::BaseBackupPathInfo: backup path (" << pathToBackup << ") is just a drive name." << std::endl;
		pathToBackup /= FILESYSTEM_PATH(std::wstring(1, FILESYSTEM_PATH::preferred_separator)); // Add a backslash or slash
		std::clog << "BaseBackupPathInfo::BaseBackupPathInfo: backup path = " << pathToBackup << " after adding a backslash." << std::endl;
#endif // _DEBUG
	}
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