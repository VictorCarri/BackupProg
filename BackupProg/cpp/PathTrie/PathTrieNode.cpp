/* Standard C++ */
#include <algorithm> // std::binary_search, std::lower_bound

/* Our headers */
#include "PathTrie/PathTrieNode.hpp" // Class definition

/*
* \desc Returns this node's data.
* \return This node's character.
*/
char pathTrie::Node::getData() const
{
	return data;
}

/*
* \desc Constructs a Node that contains the given character.
*/
pathTrie::Node::Node(char c) : data(c)
{
}

/*
* \desc Tells the caller whether this node is a leaf in the trie or not.
* \return True if this Node is a leaf, false otherwise.
*/
bool pathTrie::Node::isLeaf() const
{
	return children.empty(); // We're a leaf node if we have no children
}

/*
* \desc Determines whether this node has an *immediate* child that has the given character.
* \param c The character to search for in our children.
* \return True if we have an *immediate* child node which stores this character, false otherwise.
*/
bool pathTrie::Node::hasChild(char c) const
{
	/* 
	* ASSUMPTION: The insert operation has already sorted the list of children by character.
	* So we just need to run a binary search.
	*/
	return std::binary_search(children.begin(), children.end(), c); // Search the list of nodes to see if there's one that has the given value.
}

/*
* \desc Less-than operator. We need to define this to enable comparison, and thus sorting and searching.
* \param left The left Node to compare.
* \param right The Node on the right of the comparison.
* \returns True if the Node on the left has a character that's < the character that the Node on the right has, false otherwise.
*/
bool operator<(const pathTrie::Node& left, const pathTrie::Node& right)
{
	return left.getData() < right.getData();
}

/*
* \desc Compares 2 Nodes for equality. Note: this *can't* be used to search the trie, because it assumes that no 2 Nodes store the same character. Which is obviously false in a trie.
* \param left The left Node to compare.
* \param right The right Node to compare.
* \returns True if the 2 Nodes store the same character, false otherwise.
*/
bool operator==(const pathTrie::Node& left, const pathTrie::Node& right)
{
	return left.getData() == right.getData(); // Check whether they store the same character
}

/*
* \desc Fetches a pointer to the node which stores the given character.
* \assumption This Node has a child which stores this character.
* \param c The character to check for.
* \returns A pointer to the Node which stores the given character.
*/
std::shared_ptr<pathTrie::Node> pathTrie::Node::getChild(char c)
{
	auto 
}