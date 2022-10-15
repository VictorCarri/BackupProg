/* Standard C++ */
#include <algorithm> // std::binary_search, std::lower_bound
#include <memory> // std::shared_ptr
#include <stdexcept> // std::invalid_argument, std::runtime_error
#include <sstream> // std::ostringstream
#include <iomanip> // std::quoted

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
* \param c The character this Node should store.
* \param d The Node's depth in the tree
*/
pathTrie::Node::Node(char c, int d) : data(c), depth(d)
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
	return std::binary_search(children.cbegin(), children.cend(), c, comparer); // Search the list of nodes to see if there's one that has the given value.
}

/*
* \desc Fetches a pointer to the node which stores the given character.
* \assumption This Node has a child which stores this character.
* \param c The character to check for.
* \returns A pointer to the Node which stores the given character.
*/
std::shared_ptr<pathTrie::Node> pathTrie::Node::getChild(char c)
{
	if (hasChild(c)) // Ensure that we have an (immediate) child that contains this character
	{
		auto charIt = std::lower_bound(children.cbegin(), children.cend(), c, comparer); // Find the iterator that points to the Node that has this character
		return *charIt; // Return the pointer to the Node
	}

	else // Error - bad operation
	{
		std::ostringstream ess;
		ess << "pathTrie::Node::getChild: no child has character " << c << " @ depth " << depth;
		throw std::invalid_argument(ess.str());
	}
}

/*
* \desc Adds a new child Node that stores the given character.
* \param c The character that this Node stores.
* \throws std::runtime_error If something fails
*/
void pathTrie::Node::addChild(char c)
{
	children.emplace_front(c, depth+1); // Create a new Node that stores the given character at the next lowest depth. Insert it at the front of the list.
	children.sort(comparer); // Sort the list again so that the next search will work properly
}

/*
* \desc Stream insertion operator that prints the Node.
* \param out The stream to write to.
* \param n The Node to print.
* \returns The stream, to enable chaining.
*/
std::ostream& pathTrie::operator<<(std::ostream& out, const pathTrie::Node& n)
{
	out << "Node @ depth " << n.depth << " with data ";
	return out;
}