/* Boost */
#include <boost/json.hpp> // boost::json::array

/* Boost or Standard C++ */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

/* Our headers */
#include "BackupInfoList/WindowsBackupInfoList.hpp" // Class def'n

/*
* \desc Returns a const iterator that points to the beginning of our implementation list. Lets our user avoid caring about the actual implementation of the list.
* \return A const iterator that points to the beginning of our implementation list.
*/
windows::BackupInfoList::const_iterator windows::BackupInfoList::cbegin() const
{
	return impl.cbegin();
}

/*
* \desc Returns a const iterator that points to the end of our implementation list. Lets our user avoid caring about the actual implementation of the list.
* \return A const iterator that points to the end of our implementation list.
*/
windows::BackupInfoList::const_iterator windows::BackupInfoList::cend() const
{
	return impl.cend();
}

/*
* \desc Constructs a new backup path info object in-place at the (conceptual) end of our list.
* \param backupPath The path which this object will store info about.
* \param dirsArr The list of directories under this path that we should skip.
* \param filesArr The list of files under this path that we should skip backing up.
*/
void windows::BackupInfoList::emplace(FILESYSTEM_PATH backupPath, boost::json::array dirsArr, boost::json::array filesArr)
{
	impl.emplace_front(backupPath, dirsArr, filesArr); // Construct a new backup path info object in place.
}

/*
* \desc Returns a mutable iterator that points to the beginning of our implementation list. Lets our user avoid caring about the actual implementation of the list.
* \return A mutable iterator that points to the beginning of our implementation list.
*/
windows::BackupInfoList::iterator windows::BackupInfoList::begin()
{
	return impl.begin();
}

/*
* \desc Returns a mutable iterator that points to the end of our implementation list. Lets our user avoid caring about the actual implementation of the list.
* \return A mutable iterator that points to the end of our implementation list.
*/
windows::BackupInfoList::iterator windows::BackupInfoList::end()
{
	return impl.end();
}