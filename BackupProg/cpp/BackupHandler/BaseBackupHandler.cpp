/* Boost or Standard C++ */
#include "bosmacros/thread.hpp" // THREAD_CLASS

/* Our headers */
#include "BackupInfoList/BaseBackupInfoList.hpp" // List of backup info objects
#include "BackupHandler/BaseBackupHandler.hpp" // Base class

/*
* \desc Constructor. Stores the given reference in our member for later use.
* \param toStore The reference to store.
*/
BaseBackupHandler::BaseBackupHandler(BaseBackupInfoList toStore) : backupInfoList(toStore)
{
}

/*
* \desc Destructor. Waits for all threads to join.
*/
BaseBackupHandler::~BaseBackupHandler()
{
	/* Wait for all of our threads to join. */
	for (THREAD_CLASS& thread : backupThreads) // Loop through each thread. We use references to thread objects because the thread classes lack copy or move constructors.
	{
		thread.join(); // Wait for it to join
	}
}