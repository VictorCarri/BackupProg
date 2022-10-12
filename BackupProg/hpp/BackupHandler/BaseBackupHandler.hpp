#ifndef BASEBACKUPHANDLER_HPP
#define BASEBACKUPHANDLER_HPP

	/* Standard C++ */
	#include <forward_list> // std::forward_list

	/* Boost or Standard C++ */
	#include "bosmacros/thread.hpp" // THREAD_CLASS
	
	/* Our headers */
	#include "BackupInfoList/BaseBackupInfoList.hpp" // Base backup info list class

	/*
	* Base class for the task classes that manage the backup threads. Meant to be specialized for each OS.
	*/
	class BaseBackupHandler
	{
		public:
			/*
			* \desc Constructor. Stores the given reference in our member for later use.
			* \param toStore The reference to store.
			*/
			BaseBackupHandler(BaseBackupInfoList toStore);

			/*
			* \desc Destructor. Waits for all threads to join.
			*/
			~BaseBackupHandler();

		protected:
			BaseBackupInfoList backupInfoList; // A reference to the backup info
			std::forward_list<THREAD_CLASS> backupThreads; // List of threads that we've started
	};

#endif // BASEBACKUPHANDLER_HPP