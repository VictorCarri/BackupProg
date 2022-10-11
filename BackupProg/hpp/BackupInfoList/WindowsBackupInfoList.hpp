#ifndef WINDOWSBACKUPINFOLIST_HPP
#define WINDOWSBACKUPINFOLIST_HPP
	
	/* Our headers */
	#include "BackupPathInfo/WindowsBackupPathInfo.hpp" // Class that holds backup path info. that's specific to Windows
	#include "BackupInfoList/BaseBackupInfoList.hpp" // Base class

	/*
	* Namespace for Windows-specific classes.
	*/
	namespace windows
	{
		/*
		* A specialization of the backup info list for Windows.
		*/
		class BackupInfoList : public BaseBackupInfoList
		{
			public:
				typedef std::forward_list<windows::BackupPathInfo> impl_type; // The type we use for our actual implementation. Exposed so that users can get the type without needing to know what it is.
				typedef impl_type::const_iterator const_iterator; // Expose our const iterator type.
				typedef impl_type::value_type value_type; // Expose our value type
				typedef impl_type::iterator iterator; // Expose our iterator type

				/*
				* \desc Returns a const iterator that points to the beginning of our implementation list. Lets our user avoid caring about the actual implementation of the list.
				* \return A const iterator that points to the beginning of our implementation list.
				*/
				const_iterator cbegin() const;

				/*
				* \desc Returns a const iterator that points to the end of our implementation list. Lets our user avoid caring about the actual implementation of the list.
				* \return A const iterator that points to the end of our implementation list.
				*/
				const_iterator cend() const;

				/*
				* \desc Constructs a new backup path info object in-place at the (conceptual) end of our list.
				* \param backupPath The path which this object will store info about.
				* \param dirsArr The list of directories under this path that we should skip.
				* \param filesArr The list of files under this path that we should skip backing up.
				*/
				void emplace(FILESYSTEM_PATH backupPath, boost::json::array dirsArr, boost::json::array filesArr);

				/*
				* \desc Returns a mutable iterator that points to the beginning of our implementation list. Lets our user avoid caring about the actual implementation of the list.
				* \return A mutable iterator that points to the beginning of our implementation list.
				*/
				iterator begin();

				/*
				* \desc Returns a mutable iterator that points to the end of our implementation list. Lets our user avoid caring about the actual implementation of the list.
				* \return A mutable iterator that points to the end of our implementation list.
				*/
				iterator end();

			private:
				impl_type impl; // The actual list of backup path info objects
		};
	}

#endif // WINDOWSBACKUPINFOLIST_HPP