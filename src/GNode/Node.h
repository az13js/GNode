#ifndef GNODE_NODE_H
#define GNODE_NODE_H

#include <set>

namespace GNode {

    class Node {

    public:

        Node() {
        }

        Node(int val) {
            value = val;
        }

        ~Node() {
        }

        int getValue() {
            return value;
        }

        void add(Node* child) {
            nodes.insert(child);
        }

        std::set<Node*> getNodes() {
            return nodes;
        }

        void remove(Node* node) {
            nodes.erase(node);
        }

    private:

        int value = 0;

        std::set<Node*> nodes;

    };

}

#endif
