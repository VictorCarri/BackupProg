#ifndef WINDOWSCONFIGHANDLER_HPP
#define WINDOWSCONFIGHANDLER_HPP

	/* Standard C++ */
	#include <vector> // std::vector
	#include <map> // std::map

	/* Boost or STL */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

	/* Our headers */
	#include "ConfigHandler/BaseConfigHandler.hpp" // Base class

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

		};
	}

#endif // WINDOWSCONFIGHANDLER_HPP