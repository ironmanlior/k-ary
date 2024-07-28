#pragma once

#include "Node.hpp"
#include "iterator.hpp"

using namespace std;
namespace ariel{

template<typename T, int k = 2> class Tree {
	private:
		Node<T>* root;
		vector<Node<T>> pre, in, post, bfs, dfs;
		
	public:
		Tree();
		~Tree();

		void set_root(Node<T> *node);
		Node<T>* get_root();

		void add_sub_node(Node<T> *parent, Node<T> *child);

		auto begin_pre_order() const;
		auto end_pre_order() const;

		auto begin_post_order() const;
		auto end_post_order() const;

		auto begin_in_order() const;
		auto end_in_order() const;

		auto begin_bfs_scan() const;
		auto end_bfs_scan() const;

		auto begin_dfs_scan() const;
		auto end_dfs_scan() const;

		vector<T> myHeap() const {
            vector<T> values;
            for (auto it = begin_dfs(); it != end_dfs(); ++it) {
                values.push_back(it->value);
            }

            sort(values.begin(), values.end());

            auto last = unique(values.begin(), values.end());
            values.erase(last, values.end());

            return values;
        }

		void draw(QGraphicsScene* scene, double xOffset = 0, double yOffset = 0);
};
}
