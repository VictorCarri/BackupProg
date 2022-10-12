#ifndef WINDOWS_PATHBACKUPCREATOR_HPP
#define WINDOWS_PATHBACKUPCREATOR_HPP

	/* Our headers */
	#include "BackupPathInfo/WindowsBackupPathInfo.hpp" // Class that holds information about how to backup a particular path on Windows
	#include "PathBackupCreator/BasePathBackupCreator.hpp" // Base class

	namespace windows
	{
		class PathBackupCreator : public BasePathBackupCreator
		{
			public:
				/*
				* \desc Constructor. Creates a new task class that backs up the path named in the given info object.
				* \param pathInfo An object that describes the path to be backed up.
				*/
				PathBackupCreator(BackupPathInfo pathInfo);

				/*
				* \desc Performs the backup. Iterates through all paths under the given path and checks whether any of the file's times are more recent than the last backup time.
				*		If at least one of the file's times is more recent than the last backup time, it determines what path on the backup drive this file should be copied to.
				*		Then, it copies the file there.
				*/
				void operator()();

			private:
				BackupPathInfo ourPathInfo; // Stores info about the path to backup
		};
	};

#endif // WINDOWS_PATHBACKUPCREATOR_HPP