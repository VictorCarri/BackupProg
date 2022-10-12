#ifndef BASEPATHBACKUPCREATOR_HPP
#define BASEPATHBACKUPCREATOR_HPP

	/* Our headers */
	#include "BackupPathInfo/BaseBackupPathInfo.hpp" // Backup path info class

	/*
	* This is the base class of the task classes that create backups of a given path.
	*/
	class BasePathBackupCreator
	{
		public:
			/*
			* \desc Constructor. Stores the given path info.
			* \desc toStore The path info object that describes the path we should backup.
			*/
			BasePathBackupCreator(BaseBackupPathInfo toStore);

			/*
			* \desc Performs the backup. Left pure virtual (abstract) in this class because it's meant to be specialized for each OS.
			*/
			virtual void operator()() = 0;

		private:
			BaseBackupPathInfo pathInfo; // Info about the path we should back up.
	};

#endif // BASEPATHBACKUPCREATOR_HPP