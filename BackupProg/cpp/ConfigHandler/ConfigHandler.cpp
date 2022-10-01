/* STL */
#include <sstream> // std::ostringstream, std::endl, std::istringstream
#include <exception> // std::runtime_error
#ifdef _DEBUG
#include <iostream> // std::clog
#endif
#include <string> // std::string
#include <iomanip> // std::get_time, std::quoted

/* Boost or STL */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH, FILESYSTEM_ERROR

/* Boost */
#include <boost/json.hpp> // boost::json::parse, boost::json::value, boost::json::object, boost::json::string

/* Our headers */
#include "ConfigHandler/ConfigHandler.hpp" // Class def'n

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
	boost::json::object confObj = options.as_object(); // Get the options as a JSON object
	boost::json::value dateVal = confObj["lastBackupTime"]; // Get last backup time as a JSON value
	boost::json::string dateJSONStr = dateVal.as_string(); // Get last backup time as JSON string
	char const* dateCStr = dateJSONStr.c_str(); // Get last backup time as a C string
	std::string dateCPPStr(dateCStr); // Convert it to a  C++ string
	std::istringstream dateStrm(dateCPPStr); // Populate the stream with the date
	const char* timeFormatStr = "%Y-%m-%d %H:%M:%S"; // Use the ISO date format followed by the ISO time format.
	
	dateStrm.imbue(std::locale(""));
	dateStrm >> std::get_time(&lastBackupTime, timeFormatStr); // Parse the date when we last ran a backup

#ifdef _DEBUG
	std::clog << "ConfigHandler::storeLastBackupTime: dateJSONStr = " << dateJSONStr << std::endl
		<< "\tdateCStr = " << std::quoted(dateCStr) << std::endl
		<< "\tdateCPPStr = " << std::quoted(dateCPPStr) << std::endl
		<< "\tdateStrm contents = " << std::quoted(dateStrm.str()) << std::endl << std::endl;
#endif // DEBUG


	if (dateStrm.fail())
	{
		std::ostringstream ess;
		ess << "ConfigHandler::storeLastBackupTime: couldn't parse date string " << std::quoted(dateCPPStr) << std::endl;
		std::runtime_error sre(ess.str());
		throw sre;
	}

	else
	{
#ifdef _DEBUG
		std::cerr << "Parsed last backup time string " << std::quoted(dateCPPStr) << " as " << std::put_time(&lastBackupTime, timeFormatStr) << std::endl;
#endif // _DEBUG
	}
}