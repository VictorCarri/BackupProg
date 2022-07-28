#ifndef CONFIGFILEPARSER_HPP
#define CONFIGFILEPARSER_HPP

	/* Standard C++ */
	#include <string> // std::string
	#include <boost/json.hpp> // boost::json::value

	/* Boost or STL */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH, IFSTREAM

	/*
	* Parses our JSON config file and stores the value as a JSON object.
	*/
	class ConfigHandler
	{
		public:
			/*
			* \desc Constructor. Reads the entire JSON file in as a string, then uses Boost.JSON to parse it as JSON and save it.
			* \param confFilePath The path to the config JSON file.
			*/
			ConfigHandler(FILESYSTEM_PATH confFilePath);

			/*
			* \desc Fetches the options we read from the file.
			* \return The options as a JSON object.
			*/
			boost::json::value getOpts() const;

		private:
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
	};

#endif //sCONFIGFILEPARSER_HPP