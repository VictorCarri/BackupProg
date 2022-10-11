#ifndef WINDOWSCONFIGHANDLER_HPP
#define WINDOWSCONFIGHANDLER_HPP

	/* Standard C++ */
	#include <forward_list> // std::forward_list

	/* Boost or STL */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH
	#include "bosmacros/regex.hpp" // REGEX

	/* Our headers */
	#include "ConfigHandler/BaseConfigHandler.hpp" // Base class
	#include "BackupPathInfo/WindowsBackupPathInfo.hpp" // Windows backup info object

	namespace windows
	{
		/*
		* A configuration file handler that's specialized to handle backup Windows configuration for Windows.
		*/
		class ConfigHandler : public BaseConfigHandler
		{
			public:
				/*
				* \desc Constructor. Reads the entire JSON file in as a string, then uses Boost.JSON to parse it as JSON and save it.
				* \param confFilePath The path to the config JSON file.
				*/
				ConfigHandler(FILESYSTEM_PATH confFilePath);

			private:
				std::forward_list<windows::BackupPathInfo> backupInfo; // List of information objects for each path to back up
		};
	}

#endif // WINDOWSCONFIGHANDLER_HPP