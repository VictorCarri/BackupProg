/* Standard C++ */
#ifdef _DEBUG
#include <iostream> // std::clog
#endif // _DEBUG

/* Boost or STL */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH
#include "bosmacros/regex.hpp" // REGEX, MATCH_RESULTS, REGEX_REPLACE

/* Boost */
#include <boost/json.hpp> // boost::json::array, boost::json::value, boost::json::string

/* Our headers */
#include "BackupPathInfo/WindowsBackupPathInfo.hpp" // Class def'n

/*
* \desc Constructor. Initializes our base class and stores the path we store info about.
* \desc skipDirs JSON array of directory paths relative to our backup path that we should skip backing up.
* \desc skipFiles JSON array of file paths relative to our backup path that we should skip backing up.
* \param backupPath The path we store info about.
*/
windows::BackupPathInfo::BackupPathInfo(FILESYSTEM_PATH backupPath, boost::json::array skipDirs, boost::json::array skipFiles) : BaseBackupPathInfo(backupPath) // Initialize my base class
{
	for (boost::json::value dir : skipDirs) // Create regexes for each directory to skip
	{
#ifdef _DEBUG
		std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: dir = " << dir << std::endl;
#endif // _DEBUG

		/* Get the directory value as a string */
		boost::json::string dirJSONStr = dir.as_string(); // Get the directory as a JSON string

#ifdef _DEBUG
		std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: dirJSONStr = " << dirJSONStr << std::endl
			<< "windows::BackupPathInfo::BackupPathInfo: dir for: Does the path have a root name? " << (backupPath.has_root_name() ? "Yes" : "No") << std::endl;

		if (backupPath.has_root_name())
		{
			std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: backupPath's root name = " << backupPath.root_name() << std::endl;
		}

		std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: Does the path have a root directory? " << (backupPath.has_root_directory() ? "Yes" : "No") << std::endl;

		if (backupPath.has_root_directory())
		{
			std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: backupPath's root directory = " << backupPath.root_directory() << std::endl;
		}
#endif // _DEBUG

		/* We need to add slashes to paths that only have a drive name. I.e., paths that have an empty root directory. */
		FILESYSTEM_PATH dirPath(backupPath); // Initialize the directory path to the drive path

#ifdef _DEBUG
		std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: dirPath = " << dirPath << " after initialization." << std::endl;
#endif // _DEBUG

		if (!backupPath.has_root_directory()) // Just a drive name
		{
#ifdef _DEBUG
			std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: no root dir if: backupPath lacks a root directory." << std::endl;
#endif // _DEBUG

			dirPath += "\\"; // Add slashes to the bare drive name. This provides a root directory before the directory name.

#ifdef _DEBUG
			std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: no root dir if: dirPath = " << dirPath << " after adding slashes." << std::endl;
#endif // _DEBUG
		}

		/* Add the directory to the drive path which has been modified if necessary. */
		FILESYSTEM_PATH dirJSONPathFSPath(dirJSONStr.cbegin(), dirJSONStr.cend()); // Convert the JSON string to a filesystem path

#ifdef _DEBUG
		std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: dirJSONPathFSPath = " << dirJSONPathFSPath << std::endl;
#endif // _DEBUG

		dirPath /= dirJSONPathFSPath; // Add the directory name to the drive path

#ifdef _DEBUG
		std::clog << "windows::BackupPathInfo::BackupPathInfo: dir for: dirPath = " << dirPath << " after appending the directory's name." << std::endl;
#endif // _DEBUG

#ifdef _DEBUG
		std::clog << std::endl; // Pretty printing
#endif // _DEBUG

		REGEX escapedReg = pathToRegex(dirPath); // Escape the backslashes in the path so that we can get the regex engine to recognize literal backslashes
		dirRegs.push_back(escapedReg); // Add this regex to the list of regexes that match directories that we should skip
	}
}

/*
* \desc Converts the given filesystem path to a regex
*		Doubles slashes so that the regex parser won't interpret them as the start of an escape sequence.
*/
REGEX windows::BackupPathInfo::pathToRegex(FILESYSTEM_PATH path)
{
#ifdef _DEBUG
	std::clog << "windows::BackupPathInfo::pathToRegex: path = " << path << " at start." << std::endl;
#endif // _DEBUG

	std::string pathStr = path.string(); // Convert the path to a string so that we can replace the single backslashes with double ones

#ifdef _DEBUG
	std::clog << "windows::BackupPathInfo::pathToRegex: pathStr = " << pathStr << " at start." << std::endl;
#endif // _DEBUG

	/*
	* A regex that will match single backslashes. This requires 2 levels of escaping. The regex engine needs to see 2 backslashes in a row so that it'll understand that it should replace a
	* literal backslash. But C++ requires us to escape literal backslashes when typing the string in as well. So, we end up with four backslash characters. The compiler will reduce the 4 to
	* 2 literal backslashes. Then, the regex engine will reduce the 2 literal backslashes to a single literal backslash.
	*/
	std::string singleBackslashRegInp("\\\\"); // Holds the regex so that we can print it
	REGEX backslashReplacementReg(singleBackslashRegInp); // The regex we'll replace backslashes with

	/*
	* We need to use 8 backslashes to get the regex engine to see 2 backslashes in a row. This is what we want to replace the single backslashes with.
	* The compiler will see the 8 backslashes, and interpret half of them as escapes. So, the 8 backslashes will get reduced to 4.
	* Then the regex engine will see the 4 backslashes. It will interpret half of them as escapes. So, the 4 backslashes will be reduced to 2.
	* Finally, the regex engine will use 2 literal backslash characters to replace every backslash in the original string.
	*/
	std::string replacementRegexFormat("\\\\\\\\");

#ifdef _DEBUG
	std::clog << "windows::BackupPathInfo::pathToRegex: toReplace = " << singleBackslashRegInp << std::endl;
#endif // _DEBUG
	std::string pathWithDoubleBackslashes = REGEX_REPLACE(pathStr, backslashReplacementReg, replacementRegexFormat); // Replace each individual backslash in the path with 2 
	// so that we can pass the string to the regex engine. The regex engine will interpret each pair of backslashes as a literal backslash.

#ifdef _DEBUG
	std::clog << "windows::BackupPathInfo::pathToRegex: pathWithDoubleBackslashes = " << pathWithDoubleBackslashes << std::endl;
#endif // _DEBUG

#ifdef _DEBUG
	std::clog << "===-------------------------------===================================================================" << std::endl
		<< std::endl;
#endif // _DEBUG

	REGEX pathReg(pathWithDoubleBackslashes); // Convert the string to a regex to return
	return pathReg; // Return the regex we created
}