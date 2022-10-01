#ifndef WINDOWSCONFIGHANDLER_HPP
#define WINDOWSCONFIGHANDLER_HPP

	/* Boost or STL */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

	/* Our headers */
	#include "ConfigHandler/ConfigHandler.hpp" // Base class

	namespace windows
	{
		/*
		* A configuration file handler that's specialized to handle Windows configuration.
		*/
		class WindowsConfigHandler : public ConfigHandler
		{
			public:
				/*
				* \desc Constructor. Reads the entire JSON file in as a string, then uses Boost.JSON to parse it as JSON and save it.
				* \param confFilePath The path to the config JSON file.
				*/
				WindowsConfigHandler(FILESYSTEM_PATH confFilePath);
		};
	}

#endif // WINDOWSCONFIGHANDLER_HPP