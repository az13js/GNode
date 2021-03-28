#ifndef GNODE_NODE_H
#define GNODE_NODE_H

#include <set>

namespace GNode {

    template<class T>
    class Node {

    public:

        Node() {
        }

        Node(T val) {
            value = val;
        }

        ~Node() {
        }

        T getValue() {
            return value;
        }

        void add(Node* child) {
            if (nodes.count(child) != 0) {
                return;
            }
            nodes.insert(child);
            child->add(this);
        }

        std::set<Node*> getNodes() {
            return nodes;
        }

        void remove(Node* node) {
            if (nodes.count(node) == 0) {
                return;
            }
            nodes.erase(node);
            node->remove(this);
        }

    private:

        T value = 0;

        std::set<Node*> nodes;

    };

}

#endif
