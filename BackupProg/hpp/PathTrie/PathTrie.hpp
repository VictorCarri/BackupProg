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

		private:
			std::shared_ptr<Node> root; // The trie's root node
	};
};

#endif // PATHTRIE_HPP