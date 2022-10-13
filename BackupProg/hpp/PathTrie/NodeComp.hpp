#ifndef PATHTRIE_NODECOMP_HPP
#define PATHTRIE_NODECOMP_HPP

/* Standard C++ */
#include <memory> // std::shared_ptr

/* Our headers */
#include "PathTrie/PathTrieNode.hpp" // Our Node class

namespace pathTrie
{
	/*
	* \desc A predicate class that compares 2 Nodes in a path trie.
	*/
	class NodeComp
	{
		public:
			/*
			* \desc Call operator. Compares the left and right Nodes by comparing their characters.
			* \param left The left Node.
			* \param right The right Node.
			* \return True if the left Node's character < the right Node's one, false otherwise.
			*/
			bool operator()(const std::shared_ptr<Node> left, const std::shared_ptr<Node> right);
	};
};

#endif // !PATHTRIE_NODECOMP_HPP