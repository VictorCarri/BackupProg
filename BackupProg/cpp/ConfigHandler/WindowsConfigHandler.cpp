/* Standard C++ */
#ifdef _DEBUG
	#include <iostream> // std::clog
#endif // _DEBUG

#include <sstream> // std::ostringstream
#include <string> // std::string

/* Boost or Standard C++ */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

/* Boost */
#include <boost/json.hpp> // boost::json::value, boost::json::object, boost::json::array, boost::json::string

/* Our headers */
#include "ConfigHandler/BaseConfigHandler.hpp" // Base class
#include "ConfigHandler/WindowsConfigHandler.hpp" // Class def'n
#include "BackupPathInfo/BaseBackupPathInfo.hpp" // Base backup path info class
#include "BackupPathInfo/WindowsBackupPathInfo.hpp" // Windows-specific backup info class

/*
* \desc Constructor. Reads the entire JSON file in as a string, then uses Boost.JSON to parse it as JSON and save it.
* \param confFilePath The path to the config JSON file.
*/
windows::ConfigHandler::ConfigHandler(FILESYSTEM_PATH confFilePath) : BaseConfigHandler(confFilePath) // Construct the common variables
{
	boost::json::object optionsObj = options.as_object(); // Get options object
	boost::json::value backupList = optionsObj["backupList"]; // Get the value of the backup list key
	boost::json::array backupInfoArr = backupList.as_array(); // Convert the value to an array
	
	for (boost::json::value drive : backupInfoArr) // Loop through the objects inside the array of backup info
	{
		/* Get the path to back up */
		boost::json::object driveObj = drive.as_object();
		boost::json::value backupPathVal = driveObj["backupPath"]; // Path of the drive to back up
		boost::json::string backupPathJSONStr = backupPathVal.as_string(); // Get the drive path as a JSON string
		const char* backupPathCStr = backupPathJSONStr.c_str(); // Get it as a C string
		FILESYSTEM_PATH drivePath(backupPathCStr); // Create a filesystem path that we can put into our map
		
#ifdef _DEBUG
		std::clog << "windows::ConfigHandler::ConfigHandler: drive path = " << drivePath << std::endl;
#endif // _DEBUG


		/* Create the list of paths to skip for this drive */
		boost::json::value excludeVal = driveObj["exclude"]; // Object containing exclusion info as a value

#ifdef _DEBUG
		std::clog << "windows::ConfigHandler::ConfigHandler: excludeVal = " << excludeVal << std::endl;
#endif // _DEBUG

		boost::json::object excludeObj = excludeVal.as_object(); // Convert the value to an object
		boost::json::value dirsVal = excludeObj["dirs"]; // List of directories to skip
		boost::json::value filesVal = excludeObj["files"]; // List of files to skip

#ifdef _DEBUG
		std::clog << "windows::ConfigHandler::ConfigHandler: dirsVal = " << dirsVal << std::endl
			<< std::endl
			<< "windows::ConfigHandler::ConfigHandler: filesVal = " << filesVal << std::endl << std::endl;
#endif // _DEBUG

		/* Get the arrays of directories and files to skip as arrays */
		boost::json::array dirsArr = dirsVal.as_array();
		boost::json::array filesArr = filesVal.as_array();

#ifdef _DEBUG
		std::clog << "windows::ConfigHandler::ConfigHandler: dirsArr = " << dirsArr << std::endl
			<< std::endl
			<< "windows::ConfigHandler::ConfigHandler: filesArr = " << filesArr << std::endl << std::endl;
#endif // _DEBUG

		backupInfoList.emplace(drivePath, dirsArr, filesArr); // Add a drive path info object in place for this drive

#ifdef _DEBUG
		std::clog << "=====================================================================================" << std::endl
			<< std::endl;
#endif // _DEBUG
	}
}

/*
* \desc Fetches the list of objects that contain info about each path that we should backup.
* \returns The list of objects that contain info about each path that we should backup.
*/
const windows::BackupInfoList* windows::ConfigHandler::getBackupInfoList() const
{
	return &backupInfoList; // Return our Windows-specific backup list
}