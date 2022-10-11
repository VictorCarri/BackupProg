#ifndef BASECONFIGHANDLER_HPP
#define BASECONFIGHANDLER_HPP

	/* Standard C++ */
	#include <string> // std::string
	#include <boost/json.hpp> // boost::json::value
	#include <vector> // std::vector
	#include <forward_list> // std::forward_list

	/* STL versions of C headers */
	#include <ctime> // std::tm

	/* Boost or STL */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH, IFSTREAM
	#include "bosmacros/regex.hpp" // REGEX

	/* Our headers */
	#include "BackupInfoList/BaseBackupInfoList.hpp" // Base class for backup info lists

	/*
	* Parses our JSON config file and stores the value as a JSON object.
	* NOTE: This class assumes that the config file is complete, but not necessarily valid.
	* I.e., it assumes that none of the required object keys has a null value. And that each of the required fields exists in the object.
	* But it verifies the data of each field.
	* A separate program is needed to actually update the configuration file.
	*/
	class BaseConfigHandler
	{
		public:
			/*
			* \desc Constructor. Reads the entire JSON file in as a string, then uses Boost.JSON to parse it as JSON and save it.
			* \param confFilePath The path to the config JSON file.
			*/
			BaseConfigHandler(FILESYSTEM_PATH confFilePath);

			/*
			* \desc Fetches the options we read from the file.
			* \return The options as a JSON object.
			*/
			boost::json::value getOpts() const;

			/*
			* \desc Fetches the list of objects that contain info about each path that we should backup.
			* \returns The list of objects that contain info about each path that we should backup.
			*/
			virtual const BaseBackupInfoList* getBackupInfoList() const;

			/*
			* \desc Default virtual destructor, just in case.
			*/
			virtual ~BaseConfigHandler() = default;

		protected:
			/*
			* \desc Converts the last backup time stored in the JSON into a C++ time point.
			*/
			void storeLastBackupTime();

			/*
			* \desc Reads the entire file into a string.
			* \param strm A reference to the stream to read.
			*/
			void readFileIntoString(FILESYSTEM_IFSTREAM& strm);

			std::string fConts; // Holds the JSON as a string for Boost.JSON
			boost::json::value options; // Our options
			std::tm lastBackupTime; // Holds the last time the backup was run
			BaseBackupInfoList backupInfoList; // The list of backup info objects
	};

#endif // BASECONFIGHANDLER_HPP