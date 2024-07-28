K-ary Tree Container
====================

This project implements a generic k-ary tree container in C++. The main components are:

- `Node`: Represents a node in the tree, with a value and a vector of child pointers.
- `Tree`: Represents the k-ary tree, with methods for adding nodes and traversing the tree using various iterators.
- `Complex`: A simple class representing complex numbers, used to demonstrate the tree's ability to handle user-defined types.

The project does not use any external libraries. The GUI output is not yet implemented.

To build the project, run `cd /home/guy/CLionProjects/CPP_EX4/cmake-build-debug
ninja
./TreeVisualization
`.