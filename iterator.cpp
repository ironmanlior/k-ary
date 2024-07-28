#include "iterator.hpp"

namespace ariel{
template<typename T, int k> void Iterator<T, k>::pushLeftmostBranch(Node<T> *node){
	while (node) {
		this->nodes.push_back(node);
		if (!node->children.empty()) {
			node = node->children[0];
		} else {
			node = nullptr;
		}
	}
}

template<typename T, int k> bool Iterator<T, k>::isLastChild(Node<T> *parent, Node<T> *child){
	return !parent->children.empty() && parent->children.back() == child;
}

template<typename T, int k> Iterator<T, k> Iterator<T, k>::preOrderNext(){
	if (!this->nodes.empty()) {
		Node<T> *current = this->nodes.back();
		this->nodes.pop_back();
		for (int i = current->children.size() - 1; i >= 0; --i) {
			this->nodes.push_back(current->children[i]);
		}
	}
	return *this;
}


template<typename T, int k> Iterator<T, k> Iterator<T, k>::postOrderNext(){
	if (this->nodes.empty()) {
		throw out_of_range("Iterator: Incrementing an empty iterator");
	}
	Node<T> *node = this->nodes.back();
	this->nodes.pop_back();
	if (this->nodes.empty()) {
		this->lastVisited = nullptr;
		return *this;
	}

	if (this->nodes.back()->children.size() > 0 && this->lastVisited != this->nodes.top()->children.back()) {
		Node<T> *node1 = this->nodes.back();
		this->nodes.push_back(node1->children.back());
		this->lastVisited = node1->children.back();
		return *this;

	}
	if (node->children.size() > 0 && this->lastVisited != node->children.back()) {
		for (int i = node->children.size() - 1; i >= 0; --i) {
			this->nodes.push_back(node->children[i]);
		}
	}

	this->lastVisited = node;
	return *this;
}


template<typename T, int k> Iterator<T, k> Iterator<T, k>::inOrderNext(){
	if (!this->nodes.empty()) {
		Node <T>* node = this->nodes.back();
		this->nodes.pop_back();

		if (!node->children.empty()) {
			this->pushLeftmostBranch(node->children[1]);
		}
		if (this->nodes.empty()) {
			this->lastVisited = nullptr;
		}
	}
	return *this;
}


template<typename T, int k> Iterator<T, k> Iterator<T, k>::bfsNext(){
	if (!this->nodes.empty()) {
		Node<T> *current = this->nodes.front();
		this->nodes.erase(this->nodes.begin());
		for (auto child: current->children) {
			this->nodes.push_back(child);
		}
	}
	return *this;
}


template<typename T, int k> Iterator<T, k> Iterator<T, k>::dfsNext(){
	if (!this->nodes.empty()) {
		Node<T> *current = this->nodes.back();
		this->nodes.pop_back();
		for (int i = current->children.size() - 1; i >= 0; --i) {
			this->nodes.push_back(current->children[i]);
		}
	}
	return *this;
}


template<typename T, int k> Iterator<T, k>::Iterator(Node<T> *root, int type){
	// Create a new iterator object by type
	// 0. pre order
	// 1. in order
	// 2. post order
	// 3. breadth-first search (BFS)
	// 4. depth-first search (DFS)
	if (k <= 2) type = 4;

	this->type = type;
	
	if (type == 0 || type == 3 || type == 4) nodeStack.push(root);
	else if (type == 1 || type == 2) this->pushLeftmostBranch(root);
}




}