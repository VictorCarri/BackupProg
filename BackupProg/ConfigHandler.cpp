/* STL */
#include <sstream> // std::ostringstream, std::endl
#include <exception> // std::runtime_error
#ifdef _DEBUG
#include <iostream> // std::clog
#endif

/* Boost or STL */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH, FILESYSTEM_ERROR

/* Boost */
#include <boost/json.hpp> // boost::json::parse, boost::json::value, boost::json::object, boost::json::string

/* Our headers */
#include "ConfigHandler.hpp" // Class def'n

/*
* Constructor. Reads the entire JSON file in as a string, then uses Boost.JSON to parse it as JSON and save it.
*/
ConfigHandler::ConfigHandler(FILESYSTEM_PATH confFilePath)
{
	try
	{
		FILESYSTEM_IFSTREAM cfStrm(confFilePath); // Open the file
		readFileIntoString(cfStrm); // Read the file's contents
		options = boost::json::parse(fConts); // Parse the file's contents as JSON
		storeLastBackupTime();
	}

	catch (FILESYSTEM_ERROR& fe)
	{
		std::ostringstream ess;
		ess << "ConfigHandler::ConfigHandler: caught filesystem error while loading our configuration." << std::endl
			<< fe.what();
		std::runtime_error sre(ess.str());
		throw sre;
	}
}

/*
* \desc Reads the entire file into a string.
* \param strm A reference to the stream to read.
*/
void ConfigHandler::readFileIntoString(FILESYSTEM_IFSTREAM& strm)
{
	std::ostringstream fcss; // For 'f'ile 'c'ontents
	fcss << strm.rdbuf(); // Read the entire file
	fConts = fcss.str(); // Store the file's contents as a string

#ifdef _DEBUG
	std::clog << "ConfigHandler::readFileIntoString: config file contents = \"" << fConts << "\"" << std::endl;
#endif // _DEBUG

}

/*
* \desc Fetches the options we read from the file.
* \return The options as a JSON object.
*/
boost::json::value ConfigHandler::getOpts() const
{
	return options;
}

/*
* \desc Converts the last backup time stored in the JSON into a C++ time point.
*/
void ConfigHandler::storeLastBackupTime()
{
	/*
	* TODO: Check if the JSON object has a last backup time.
	* 
	* 1) If there isn't a backup time: // First time the drive was used
	*	a) Add a backup time string to the JSON object.
	*	b) Ask the user to provide a date. Assume that the time is midnight.
	*	c) Convert this to the time object to compare against.
	* 2) If there is a backup time string:
	*	a) Convert it to a time object to compare against.
	*/
}