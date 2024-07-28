#include "tree.hpp"

using namespace std;
namespace ariel{

template<typename T, int k> Tree<T, k>::Tree(){
	this->root = nullptr;
}
template<typename T, int k> Tree<T, k>::~Tree(){
	delete this->root;
}

template<typename T, int k> void Tree<T, k>::set_root(Node<T> *node){
	this->root = node;
}
template<typename T, int k> Node<T>* Tree<T, k>::get_root(){
	return this->root;
}


template<typename T, int k> void Tree<T, k>::add_sub_node(Node<T> *parent, Node<T> *child){
	if (parent->children.size() >= k)
		throw runtime_error("Cannot add child to full node");
	parent->children.push_back(child);
}


template<typename T, int k> auto Tree<T, k>::begin_pre_order() const{
	return Iterator<T, k>(root, 0);
}
template<typename T, int k> auto Tree<T, k>::end_pre_order() const {
	return Iterator<T, k>(nullptr, 0);
}


template<typename T, int k> auto Tree<T, k>::begin_post_order() const{
	return Iterator<T, k>(root, 2);
}
template<typename T, int k> auto Tree<T, k>::end_post_order() const {
	return Iterator<T, k>(nullptr, 2);
}


template<typename T, int k> auto Tree<T, k>::begin_in_order() const{
	return Iterator<T, k>(root, 1);
}
template<typename T, int k> auto Tree<T, k>::end_in_order() const {
	return Iterator<T, k>(nullptr, 1);
}


template<typename T, int k> auto Tree<T, k>::begin_bfs_scan() const{
	return Iterator<T, k>(root, 3);
}
template<typename T, int k> auto Tree<T, k>::end_bfs_scan() const {
	return Iterator<T, k>(nullptr, 3);
}


template<typename T, int k> auto Tree<T, k>::begin_dfs_scan() const{
	return Iterator<T, k>(root, 4);
}
template<typename T, int k> auto Tree<T, k>::end_dfs_scan() const {
	return Iterator<T, k>(nullptr, 4);
}
template<typename T, int k> void Tree<T, k>::draw(QGraphicsScene* scene, double xOffset = 0, double yOffset = 0){
	if (!root) return;

	double hSpacing = 200;  // Horizontal spacing between nodes
	double vSpacing = 100;  // Vertical spacing between levels

	drawNode(scene, root, xOffset + scene->width() / 4, yOffset, hSpacing, vSpacing, 0);
}
}