#ifndef GNODE_NODE_H
#define GNODE_NODE_H

#include <map>
#include <list>
#include <iostream>

namespace GNode {

    /**
     * 节点
     */
    class Node {

    public:

        /**
         * 初始化一个节点，同时给这个节点赋值
         *
         * @param int value 节点的值
         * @return void
         */
        Node(int value) {
            this->value = value;
        }

        /**
         * 初始化一个节点
         *
         * @return void
         */
        Node() {
        }

        /**
         * 返回此节点的值
         *
         * @return int
         */
        int getValue() {
            return this->value;
        }

        /**
         * 改变节点的值
         *
         * @param int value 值
         * @return void
         */
        void changeValue(int value) {
            this->value = value;
        }

        /**
         * 调试节点
         *
         * @return void
         */
        void debug() {
            using namespace std;
            cout << "Node value = " << this->value << endl;
            cout << "Children = " << this->children.size() << endl;
        }

        /**
         * 返回所有子节点
         *
         * @return list<Node>
         */
        std::list<Node> getChildren() {
            using namespace std;
            list<Node> children;
            for (auto e : this->children) {
                children.emplace_back(e.second);
            }
            return children;
        }

        /**
         * 添加子节点
         *
         * @param const Node& child
         * @return void
         */
        void addChild(const Node& child) {
            using namespace std;
            this->children.insert(pair<const Node*, const Node&>(&child, child));
        }

        /**
         * 移除给定子节点
         *
         * @param const Node& child
         * @return void
         */
        void removeChild(const Node& child) {
            this->children.erase(&child);
        }

    private:

        /** @var int 保存节点的值 */
        int value = 0;

        /** @var map<const Node*, const Node&> 存放子节点 */
        std::map<const Node*, const Node&> children;
    };

}

#endif
