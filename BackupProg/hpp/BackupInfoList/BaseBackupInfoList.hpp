#ifndef BASEBACKUPINFOLIST_HPP
#define BASEBACKUPINFOLIST_HPP

	/* Standard C++ */
	#include <forward_list> // std::forward_list

	/* Boost */
	#include <boost/json.hpp> // boost::json::array

	/* Boost or Standard C++ */
	#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

	/* Our headers */
	#include "BackupPathInfo/BaseBackupPathInfo.hpp" // Base class of our backup path info objects

	/*
	* Base class for the classes that store the list of objects that describe which paths to back up and associated information for each path.
	* Created because compilers are stupid and don't allow me to override a method that returns a list of class A with a derived method that returns a list of a class B that's derived from class A.
	*/
	class BaseBackupInfoList
	{
		public:
			typedef std::forward_list<BaseBackupPathInfo> impl_type; // The type we use for our actual implementation. Exposed so that users can get the type without needing to know what it is.
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

		protected:
			impl_type impl; // The actual list of backup path info objects
	};

#endif