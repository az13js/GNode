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

        /** @var unsigned int 自增ID */
        static unsigned int increasedId;

        /**
         * 初始化一个节点，同时给这个节点赋值
         *
         * @param int value 节点的值
         * @return void
         */
        Node(int value) {
            autoSetUuid();
            changeValue(value);
        }

        /**
         * 初始化一个节点
         *
         * @return void
         */
        Node() {
            autoSetUuid();
        }

        /**
         * 返回此节点的唯一ID
         *
         * @return unsigned int
         */
        unsigned int getUuid() {
            return uuid;
        }

        /**
         * 返回此节点的值
         *
         * @return int
         */
        int getValue() {
            return value;
        }

        /**
         * 改变节点的值
         *
         * @param int val 值
         * @return void
         */
        void changeValue(int val) {
            value = val;
        }

        /**
         * 调试节点
         *
         * @return void
         */
        void debug() {
            using namespace std;
            auto childrenTotal = children.size();
            cout << "---------- Node debug ----------" << endl;
            cout << "Node uuid = " << getUuid() << endl;
            cout << "Node value = " << getValue() << endl;
            cout << "Children = " << childrenTotal << endl;
            if (childrenTotal > 0) {
                cout << "Children uuid:" << endl;
                for (auto e : children) {
                    cout << e.second.getUuid() << endl;
                }
            }
            cout << "--------- Debug Finish ---------" << endl;
        }

        /**
         * 返回所有子节点
         *
         * @return list<Node>
         */
        std::list<Node> getChildren() {
            using namespace std;
            list<Node> childrenList;
            for (auto e : children) {
                childrenList.emplace_back(e.second);
            }
            return childrenList;
        }

        /**
         * 添加子节点
         *
         * @param Node& child
         * @return void
         */
        void addChild(Node child) {
            using namespace std;
            children.insert(pair<unsigned int, Node>(child.getUuid(), child));
        }

        /**
         * 移除给定子节点
         *
         * @param Node& child
         * @return void
         */
        void removeChild(Node& child) {
            children.erase(child.getUuid());
        }

    private:

        /** @var unsigned int 节点唯一ID */
        unsigned int uuid;

        /** @var int 保存节点的值 */
        int value = 0;

        /** @var map<unsigned int, Node> 存放子节点 */
        std::map<unsigned int, Node> children;

        /**
         * 自动设置uuid
         *
         * @return void
         */
        void autoSetUuid() {
            uuid = increasedId++;
        }

    };

    unsigned int Node::increasedId = 0;
}

#endif
