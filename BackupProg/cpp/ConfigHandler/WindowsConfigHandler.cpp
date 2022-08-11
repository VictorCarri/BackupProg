/* Boost or STL */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

/* Our headers */
#include "ConfigHandler/ConfigHandler.hpp" // Base class
#include "ConfigHandler/WindowsConfigHandler.hpp" // Class def'n

/*
* \desc Constructor. Reads the entire JSON file in as a string, then uses Boost.JSON to parse it as JSON and save it.
* \param confFilePath The path to the config JSON file.
*/
WindowsConfigHandler::WindowsConfigHandler(FILESYSTEM_PATH confFilePath) : ConfigHandler(confFilePath) // Construct the common variables
{
	/* Build a list of regexes to use to check whether we should skip the current directory or file */
}