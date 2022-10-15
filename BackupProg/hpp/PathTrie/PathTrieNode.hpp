#ifndef PATHTRIENODE_HPP
#define PATHTRIENODE_HPP

/* Standard C++ */
#include <forward_list> // std::forward_list
#include <memory> // std::shared_ptr
#include <ostream> // std::ostream

/* Our headers */
#include "PathTrie/NodeComp.hpp" // Node comparison functor

#define TRIE_ALPHABET_SIZE 256 // We only allow ASCII or UTF-8 paths

namespace pathTrie
{
	/*
	* One node in the trie. Stores data (a character), and a (singly) linked list of pointers to other tries.
	*/
	class Node
	{
		public:
			/*
			* \desc Returns this node's data.
			* \return This node's character.
			*/
			char getData() const;

			/*
			* \desc Constructs a Node that contains the given character.
			* \param c The character this Node should store.
			* \param d The Node's depth in the tree
			*/
			Node(char c, int d);

			/*
			* \desc Tells the caller whether this node is a leaf in the trie or not.
			* \return True if this Node is a leaf, false otherwise.
			*/
			bool isLeaf() const;

			/* Defaulted constructors and assignment operators */
			Node(Node& other) = default; // Default copy constructor
			Node(Node&& other) = default; // Default move constructor
			Node& operator=(Node& other) = default; // Default copy assignment
			Node& operator=(Node&& other) = default; // Default move assignment

			/*
			* \desc Determines whether this node has an *immediate* child that has the given character.
			* \param c The character to search for in our children.
			* \return True if we have an *immediate* child node which stores this character, false otherwise.
			*/
			bool hasChild(char c) const;

			/*
			* \desc Fetches a pointer to the node which stores the given character.
			* \assumption This Node has a child which stores this character.
			* \param c The character to check for.
			* \returns A pointer to the Node which stores the given character.
			*/
			std::shared_ptr<Node> getChild(char c);

			/*
			* \desc Adds a new child Node that stores the given character.
			* \param c The character that this Node stores.
			* \throws std::runtime_error If something fails
			*/
			void addChild(char c);

			/*
			* \desc Stream insertion operator that prints the Node.
			* \param out The stream to write to.
			* \param n The Node to print.
			* \returns The stream, to enable chaining.
			*/
			friend std::ostream& operator<<(std::ostream& out, const Node& n);

		private:
			char data; // A single ASCII/UTF-8 value

			/*
			* Holds this node's child nodes. We use pointers so that we don't have to reserve space for the entire alphabet of 256 characters.And so that each node can be allocated in a different
			* part of memory, rather than Nodes holding Nodes holding Nodes etc... That would lead to us using huge amounts of memory.
			*/
			std::forward_list<std::shared_ptr<Node>> children;
			short depth; // This Node's depth in the trie
			NodeComp comparer; // Compares 2 Nodes. For use with algorithms.
	};
};

#endif // !PATHTRIENODE_HPP