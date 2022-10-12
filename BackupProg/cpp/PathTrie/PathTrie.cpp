/* Standard C++ */
#include <string> // std::u8string
#include <memory> // std::shared_ptr

/* Boost or Standard C++ */
#include "bosmacros/filesystem.hpp" // FILESYSTEM_PATH

/* Our headers */
#include "PathTrie/PathTrieNode.hpp" // Node class
#include "PathTrie/PathTrie.hpp" // Class def'n

/*
* \desc Stores the given path into the trie.
* \param toStore The path to store.
*/
void pathTrie::Trie::insert(FILESYSTEM_PATH toStore)
{
	std::string pathStr = toStore.string(); // Get the path as a string
	std::shared_ptr<pathTrie::Node> curNode(root); // A pointer to the current node. Initialized as a copy of the pointer to our root node.

	for (char c : pathStr) // Loop through each string in the path
	{
		if (curNode->hasChild(c)) // The current node has a child with this character
		{
			curNode = curNode->getChild(c); // Update the current node to point to the child
		}

		else // The current node has no child with this character
		{
			curNode->addChild(c); // Add a child with this character
			curNode = curNode->getChild(c); // Move to the new node so that we can keep inserting nodes
		}
	}
}

/*
* \desc Default constructor. Constructs a Trie with a null root.
*/
pathTrie::Trie::Trie() : root(new Node(NULL))
{
}