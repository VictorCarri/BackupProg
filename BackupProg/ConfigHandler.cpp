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
		IFSTREAM cfStrm(confFilePath); // Open the file
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
void ConfigHandler::readFileIntoString(IFSTREAM& strm)
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
	/* Get the string data */
	boost::json::object& obj = options.as_object(); // Fetch the options as an object
	boost::json::value& lastBackupTimeVal = obj["lastBackupTime"]; // Fetch the last backup time as a value
	boost::json::string& lastBackupTimeStr = lastBackupTimeVal.as_string(); // Fetch the last backup time as a JSON string
	char const* lastBackupTimeArr = lastBackupTimeStr.data(); // Get the string data

#ifdef _DEBUG
	std::clog << "ConfigHandler::storeLastBackupTime: last backup time string = \"" << lastBackupTimeArr << "\"" << std::endl;
#endif // _DEBUG

	/* Convert the string data to a time point object*/
}