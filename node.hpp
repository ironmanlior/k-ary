#pragma once

#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <type_traits>
#include "node.hpp"
#include "iterator.hpp"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include "complex.hpp"


using namespace std;

namespace ariel{

template <typename T> class Node {
private:
    T value;
    vector<Node<T>*> children;

public:
    Node(T arr);
	~Node();
    T getValue();
	void setValue(T value);
	void addChild(Node<T>* child);
	void removeChild(Node<T>* child);
	Node<T>* getChild(int index);
	bool operator==(const Node<T>& other);
	string toString();

	void draw(QGraphicsScene *scene, Node<T> *node, double x, double y, double hSpacing, double vSpacing, int level);
};
}
