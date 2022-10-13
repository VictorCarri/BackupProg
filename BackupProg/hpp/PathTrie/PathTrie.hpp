#ifndef PATHTRIE_HPP
#define PATHTRIE_HPP

/* Standard C++ */
#include <memory> // std::shared_ptr

/* Boost or Standard C++ */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

/* Our headers */
#include "PathTrie/PathTrieNode.hpp" // A node in the trie

namespace pathTrie
{
	/*
	* A data structure that efficiently stores path prefixes. Meant to be used to store directory paths that should be skipped, since directory paths that we should exclude are always plain strings,
	* not regexes.
	*/
	class Trie
	{
		public:
			/*
			* \desc Stores the given path into the trie.
			* \param toStore The path to store.
			*/
			void insert(FILESYSTEM_PATH toStore);

			/*
			* \desc Default constructor. Constructs a Trie with a null root.
			*/
			Trie();

			/*
			* \desc Checks whether this trie stores a string that's a prefix of or equal to the given path.
			* \param path The path to check.
			* \returns True if either condition is true, false if both conditions are false.
			*/
			bool hasPrefixOrIsEqual(FILESYSTEM_PATH path);

		private:

			/*
			* \desc Checks whether or not this path exists in the trie.
			* \param path The path to check.
			* \returns True if the *entire* path is in the trie, false otherwise.
			*/
			bool inTrie(FILESYSTEM_PATH path);

			/*
			* \desc Checks whether or not a prefix of the given path is in the trie.
			* \param path The path to check.
			* \returns True if we reach the bottom of the trie before reaching the end of the path, false otherwise.
			*/
			bool prefixInTrie(FILESYSTEM_PATH path);

			std::shared_ptr<Node> root; // The trie's root node
	};
};

#endif // PATHTRIE_HPP