// BackupProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* C++ versions of C headers */
#include <cstdlib> // std::exit

/* Standard C++ */
#include <iostream> // std::cout, std::cerr, std::boolalpha
#include <string> // std::string
#include <stdexcept> // std::runtime_error

/* Boost */
#include <boost/program_options.hpp> // boost::program_options::options_description,  boost::program_options::positional_options_description, boost::program_options::store, boost::program_options::command_line_parser, boost::program_options::notify, boost::program_options::value

/* Macros to control whether we use Boost or the standard library when the standard library is based on Boost */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

/* Our headers */
#include "ExitCodes.hpp" // Exit codes

#if defined(WINDOWS_BUILD)
    #include "ConfigHandler/WindowsConfigHandler.hpp" // Configuration handler for Windows
    #include "BackupInfoList/WindowsBackupInfoList.hpp" // Backup info list class for Windows
    #include "BackupHandler/WindowsBackupHandler.hpp" // Backup handler for Windows

#elif defined(LINUX_BUILD)
#include "ConfigHandler/LinuxConfigHandler.hpp"
#endif

int main(int argc, char* argv[])
{
#ifdef _DEBUG
    std::clog << std::boolalpha;
    std::cerr << std::boolalpha;
#endif // _DEBUG

    /* Get our name */
    FILESYSTEM_PATH ourPath(argv[0]);
    FILESYSTEM_PATH ourName = ourPath.filename();
    std::string nameToPrint = ourName.string();

    /* Setup command line options */
    boost::program_options::options_description helpOpts; // Command-line options
    helpOpts.add_options()
        ("help,h", "Print this help message");

    /* Setup positional options */
    boost::program_options::options_description posConvOpts("Options to map positional options to");
    posConvOpts.add_options()
        ("backup-drive,b", boost::program_options::value<FILESYSTEM_PATH>()->default_value("D:"), "Path to backup drive")
        ("config-file,c", boost::program_options::value<FILESYSTEM_PATH>()->default_value("/Data/config.json"), "Path to config file relative to backup drive");

    boost::program_options::positional_options_description posOpts; // Positional options
    posOpts.add("backup-drive", 1); // The path to the backup drive
    posOpts.add("config-file", 2); // The path to the config file, relative to the backup drive

    boost::program_options::options_description cmdOpts("All command-line options");
    cmdOpts.add(helpOpts).add(posConvOpts); // All options used to parse the command line

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(cmdOpts).positional(posOpts).run(), vm);
    boost::program_options::notify(vm);

    if (vm.count("help") || ! (vm.count("backup-drive") && vm.count("config-file"))) // Print help message and exit if user asked for help or they didn't give both a path to the backup drive and a path to the config file
    {
        std::cerr << "Usage: " << nameToPrint << " /path/to/backup/drive ./config/file/path/relative/to/backup/drive" << std::endl
            << helpOpts << std::endl;
        std::exit(HELP);
    }

    try
    {
        FILESYSTEM_PATH backupDrivePath = vm["backup-drive"].as<FILESYSTEM_PATH>();
        FILESYSTEM_PATH confFilePath(backupDrivePath); // Path to config file. Starts with backup drive
        confFilePath /= vm["config-file"].as<FILESYSTEM_PATH>(); // Add relative path to config file

#ifdef _DEBUG
        std::clog << "main: Path to backup drive: " << backupDrivePath << std::endl
            << "main: Path to config file: " << confFilePath << std::endl;
#endif // _DEBUG

        if (FILESYSTEM_EXISTS(confFilePath)) // Config file exists
        {
#ifdef _DEBUG
            std::clog << "main: Config file " << confFilePath << " exists." << std::endl;
#endif // _DEBUG

#ifdef WINDOWS_BUILD
            windows::ConfigHandler ch(confFilePath); // Parse our config file and load the lists of directories and files to skip
            const windows::BackupInfoList* backupInfoList = ch.getBackupInfoList(); // Turn it back into a Windows-specific class
            const windows::BackupHandler bh(*backupInfoList); // Create an object that will handle the backup

            /* Backup each drive  that's listed in parallel */

#elif defined(OPENSUSE_BUILD)
#error "Sorry, but the backup program is only designed to work on Windows and openSUSE. Maybe you could extend it!"

#else
#error "Sorry, but the backup program is only designed to work on Windows. Maybe you could extend it!"
#endif

            return NORMAL;
        }

        else
        {
            std::cerr << "main: Config file " << confFilePath << " DNE." << std::endl;
            return NO_CONFIG_FILE;
        }
    }

    catch (FILESYSTEM_ERROR fe)
    {
        std::cerr << "main: caught filesystem error." << std::endl
            << "\t" << fe.what() << std::endl;
        return MAIN_FILESYSTEM_ERROR;
    }

    catch (std::runtime_error& sre)
    {
        std::cerr << "main: caught runtime error." << std::endl
            << sre.what() << std::endl;
        return MAIN_RUNTIME_ERROR;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
