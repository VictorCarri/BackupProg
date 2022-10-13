/* Our headers */
#include "PathTrie/PathTrieNode.hpp" // Our Node class
#include "PathTrie/NodeComp.hpp" // Class def'n

/*
* \desc Call operator. Compares the left and right Nodes by comparing their characters.
* \param left The left Node.
* \param right The right Node.
* \return True if the left Node's character < the right Node's one, false otherwise.
*/
bool pathTrie::NodeComp::operator()(const std::shared_ptr<pathTrie::Node> left, const std::shared_ptr<pathTrie::Node> right)
{
	return left->getData() < right->getData(); // One node is less than another if its character is less than the other's
}