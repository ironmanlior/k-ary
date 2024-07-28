#include "node.hpp"

using namespace std;

namespace ariel{
template <typename T> Node<T>::Node(T value) {
    this->value = value;
}

template <typename T> Node<T>::~Node() {
    for (int i = 0; i < this->children.size(); i++){
		delete this->children[i];
	}
}

template <typename T> void Node<T>::setValue(T value) {
    this->value = value;
}

template <typename T> T Node<T>::getValue() {
    return this->value;
}

template <typename T> void Node<T>::addChild(Node<T>* child){
	this->children.push_back(child);
}

template <typename T> void Node<T>::removeChild(Node<T>* child){
	auto it = find(this->children.begin(), this->children.end(), child);
	this->children.erase(*it);
}

template <typename T> Node<T>* Node<T>::getChild(int index){
	return this->children[index];
}

template <typename T> void Node<T>::addChild(Node<T>* child){
	
}

template <typename T> string Node<T>::toString() {
    return to_string(this->value);
}


template <typename T> bool Node<T>::operator==(const Node<T>& other){
	return this->value == other.getValue();
}

template <typename T> void Node<T>::draw(QGraphicsScene *scene, double x, double y, double hSpacing, double vSpacing, int level){

	QGraphicsEllipseItem* ellipse = scene->addEllipse(x - 20, y - 20, 40, 40);
	QString nodeText;
	if constexpr (std::is_same_v<T, Complex>) {
		nodeText = QString::fromStdString(this->value.to_string());
	} else if constexpr (std::is_same_v<T, std::string>) {
		nodeText = QString::fromStdString(this->value);
	} else {
		nodeText = QString::number(this->value);
	}
	QGraphicsTextItem* text = scene->addText(nodeText);
	text->setPos(x - 10, y - 10);

	double childrenWidth = hSpacing * (k - 1);
	double startX = x - childrenWidth / 2;
	for (int i = 0; i < this->children.size(); i++) {
		if (!this->children[i]) continue;
		double childX = startX + i * hSpacing;
		double childY = y + vSpacing;

		scene->addLine(x, y + 20, childX, childY - 20);
		
		this->children[i]->draw(scene, childX, childY, hSpacing / 2, vSpacing, level + 1);
	}
}

}