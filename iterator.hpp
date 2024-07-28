
#include <iostream>
#include <vector>
#include <algorithm>
#include "node.hpp"

using namespace std;

namespace ariel{
template<typename T, int k> class Iterator {
    private:
        vector<Node<T>*> nodes;
		Node<T>* lastVisited;
		int type;

		void pushLeftmostBranch(Node<T> *node);
		bool isLastChild(Node<T> *parent, Node<T> *child);
		Iterator preOrderNext();
		Iterator postOrderNext();
		Iterator inOrderNext();
		Iterator bfsNext();
		Iterator dfsNext();

    public:
        Iterator(Node<T> *root, int type);

        Node<T> &operator*() const {
            if (nodeStack.empty()) {
                throw out_of_range("Iterator: Dereferencing an empty iterator");
            }
            return *nodeStack.top();
        }

        Node<T> *operator->() const {
            if (nodeStack.empty()) {
                throw out_of_range("Iterator: Dereferencing an empty iterator");
            }
            return nodeStack.top();
        }

        Iterator &operator++() {
            if (type == 0) return this->preOrderNext();
			else if (type == 1) return this->inOrderNext();
			else if (type == 2) return this->postOrderNext();
			else if (type == 3) return this->bfsNext();
			else return this->dfsNext();
        }


        Iterator &operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator &other) const {
            return this->nodes == other.nodes;
        }

        bool operator!=(const Iterator &other) const {
            return !(*this == other);
        }
};
}