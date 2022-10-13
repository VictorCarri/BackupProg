/* Standard C++ */
#include <string> // std::u8string
#include <memory> // std::shared_ptr
#ifdef _DEBUG
#include <iostream> // std::clog
#include <iomanip> // std::quoted
#endif // _DEBUG


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
#ifdef _DEBUG
	std::clog << "pathTrie::Trie::insert: pathStr = " << std::quoted(pathStr) << std::endl;
#endif // _DEBUG

	std::shared_ptr<pathTrie::Node> curNode(root); // A pointer to the current node. Initialized as a copy of the pointer to our root node.

	for (char c : pathStr) // Loop through each string in the path
	{
#ifdef _DEBUG
		std::clog << "pathTrie::Trie::insert: current character = " << std::quoted(&c, '\'') << std::endl
			<< "Current node = " << curNode << std::endl;
#endif // _DEBUG

		if (curNode->hasChild(c)) // The current node has a child with this character
		{
#ifdef _DEBUG
			std::clog << "pathTrie::Trie::insert: current node has child w/ char. " << std::quoted(&c, '\'') << std::endl;
#endif // _DEBUG

			curNode = curNode->getChild(c); // Update the current node to point to the child that has this character
#ifdef _DEBUG
			std::clog << "pathTrie::Trie::insert: updated curNode to child node w/ char. " << std::quoted(&c, '\'') << std::endl
				<< "curNode = " << curNode << std::endl;
#endif // _DEBUG

		}

		else // The current node has no child with this character
		{
#ifdef _DEBUG
			std::clog << "pathTrie::Trie::insert: current node has no child w/ char. " << std::quoted(&c, '\'') << std::endl;
#endif // _DEBUG

			curNode->addChild(c); // Add a child with this character

#ifdef _DEBUG
			std::clog << "pathTrie::Trie::insert: added a child w/ char. " << std::quoted(&c, '\'') << std::endl;
#endif // _DEBUG

			curNode = curNode->getChild(c); // Move to the new node so that we can keep inserting nodes

#ifdef _DEBUG
			std::clog << "pathTrie::Trie::insert: updated curNode to point to new node: " << curNode << std::endl;
#endif // _DEBUG
		}
	}
}

/*
* \desc Default constructor. Constructs a Trie with a null root.
*/
pathTrie::Trie::Trie() : root(new Node(NULL, 0)) // The root is @ depth 0
{
}

/*
* \desc Checks whether this trie stores a string that's a prefix of or equal to the given path.
* \param path The path to check.
* \returns True if either condition is true, false if both conditions are false.
*/
bool pathTrie::Trie::hasPrefixOrIsEqual(FILESYSTEM_PATH path)
{
	return inTrie(path) || prefixInTrie(path);
}

/*
* \desc Checks whether or not this path exists in the trie.
* \param path The path to check.
* \returns True if the *entire* path is in the trie, false otherwise.
*/
bool pathTrie::Trie::inTrie(FILESYSTEM_PATH path)
{
	std::string pathStr = path.string(); // Get the path as a string
#ifdef _DEBUG
	std::clog << "pathTrie::Trie::inTrie: pathStr = " << std::quoted(pathStr) << std::endl;
#endif // _DEBUG

	std::shared_ptr<pathTrie::Node> curNode(root); // A pointer to the current node. Initialized as a copy of the pointer to our root node.
	std::string::size_type curPos = 0; // Current position in the string
	bool toReturn = false;

	while (curNode) // Keep looping until the node pointer becomes a null pointer
	{
		/* The checks which we must do differ depending on whether this node is a leaf or not */
		if (curNode->isLeaf()) // We've reached a leaf node
		{
			/*
			* At this point, there are 2 possibilities.
			* 1) We've reached the end of the string.
			* 2) We haven't reached the end of the string.
			* 
			* In the first case, we can return true only if this node's character is equal to the final character in the string.
			* In the second case, we can return false because we can't have reached the bottom of the trie without also having reached the end of the string if it were in the trie.
			*/

			if (curPos == (pathStr.length() - 1)) // Last possible index
			{
				toReturn = (curNode->getData() == pathStr.at(curPos)); // Return true or false, depending on whether the final character matches
				curNode = nullptr; // Stop the loop
			}

			else // We've reached the bottom of the trie w/o also reaching the end of the string
			{
				toReturn = false; // The string isn't in the trie in this case
				curNode = nullptr; // Stop the loop
			}
		}

		else // This node has children
		{
			/*
			* 2 possibilities:
			* 
			* 1) The current character in the string matches the character of one of this node's child nodes.
			* 2) The current character matches none of the child nodes' characters.
			* 
			* In the first case, we need to move to the node's child (which we know exists) and check the next character.
			* In the second case, we can return false because we didn't find the match we expected at this position.
			*/

			if (curNode->hasChild(pathStr.at(curPos))) // The current character in the string matches this node's character
			{
				curNode = curNode->getChild(pathStr.at(curPos)); // Move to the child that has the current character in the string
				++curPos; // Check the next character on the next loop
			}

			else // None of this node's children have a character that matches the current character in the string
			{
				toReturn = false; // The string can't be in the trie if there's a mismatch at this position
				curNode = nullptr; // Stop the loop
			}
		}
	}

	return toReturn;
}