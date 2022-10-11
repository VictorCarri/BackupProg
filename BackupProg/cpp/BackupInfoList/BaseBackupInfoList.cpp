/* Boost */
#include <boost/json.hpp> // boost::json::array

/* Boost or Standard C++ */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

/* Our headers */
#include "BackupInfoList/BaseBackupInfoList.hpp" // Class def'n

/*
* \desc Returns a const iterator that points to the beginning of our implementation list. Lets our user avoid caring about the actual implementation of the list.
* \return A const iterator that points to the beginning of our implementation list.
*/
BaseBackupInfoList::const_iterator BaseBackupInfoList::cbegin() const
{
	return impl.cbegin();
}

/*
* \desc Returns a const iterator that points to the end of our implementation list. Lets our user avoid caring about the actual implementation of the list.
* \return A const iterator that points to the end of our implementation list.
*/
BaseBackupInfoList::const_iterator BaseBackupInfoList::cend() const
{
	return impl.cend();
}

/*
* \desc Constructs a new backup path info object in-place at the (conceptual) end of our list.
* \param backupPath The path which this object will store info about.
* \param dirsArr The list of directories under this path that we should skip.
* \param filesArr The list of files under this path that we should skip backing up.
*/
void BaseBackupInfoList::emplace(FILESYSTEM_PATH backupPath, boost::json::array dirsArr, boost::json::array filesArr)
{
	impl.emplace_front(backupPath, dirsArr, filesArr); // Construct a new backup path info object in place.
}

/*
* \desc Returns a mutable iterator that points to the beginning of our implementation list. Lets our user avoid caring about the actual implementation of the list.
* \return A mutable iterator that points to the beginning of our implementation list.
*/
BaseBackupInfoList::iterator BaseBackupInfoList::begin()
{
	return impl.begin();
}

/*
* \desc Returns a mutable iterator that points to the end of our implementation list. Lets our user avoid caring about the actual implementation of the list.
* \return A mutable iterator that points to the end of our implementation list.
*/
BaseBackupInfoList::iterator BaseBackupInfoList::end()
{
	return impl.end();
}