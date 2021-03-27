#ifndef GNODE_GRAPH_H
#define GNODE_GRAPH_H

#include "Node.h"
#include <set>
#include <list>
#include <queue>

namespace GNode {

    class Graph {

    public:

        Graph() {
            root = new Node();
            nodes.insert(root);
        }

        Graph(int rootValue) {
            root = new Node(rootValue);
            nodes.insert(root);
        }

        ~Graph() {
            for (auto e : nodes) {
                delete e;
            }
            nodes.clear();
        }

        Node* getRoot() {
            return root;
        }

        Node* create(int val) {
            auto node = new Node(val);
            nodes.insert(node);
            return node;
        }

        Node* create() {
            return create(0);
        }

        std::set<Node*> getNodes() {
            return nodes;
        }

        void gc() {
            using namespace std;
            set<Node*> searched;
            list<Node*> removeNode;
            queue<Node*> queryQueue;
            auto queryNode = root;

            // 从根节点开始遍历整张图，查找所有节点
            queryQueue.push(root);
            while (!queryQueue.empty()) {
                queryNode = queryQueue.front();
                queryQueue.pop();
                searched.insert(queryNode);
                for (auto e : queryNode->getNodes()) {
                    if (searched.count(e) == 0) {
                        queryQueue.push(e);
                    }
                }
            }

            // 查找不到的节点就是不可达的节点，删除不可达节点
            for (auto e : nodes) {
                if (searched.count(e) == 0) {
                    // 不能直接在这里进行 nodes.erase(e) 操作！
                    removeNode.emplace_back(e);
                    delete e;
                }
            }

            // 从图的节点集合中移除删除掉的节点
            for (auto e : removeNode) {
                nodes.erase(e);
            }
        }

    private:

        Node* root;

        std::set<Node*> nodes;

    };

}

#endif
