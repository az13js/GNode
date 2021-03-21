#include "GNode/node.h"
#include <iostream>

using namespace std;
using namespace GNode;

void addNode(Node &n, int value) {
    cout << "Before add:" << endl;
    n.debug();
    auto a = Node(value);
    n.addChild(a);
    cout << "after add:" << endl;
    n.debug();
}

int main() {
    auto x = Node(555);
    addNode(x, 1);
    addNode(x, 3);
    addNode(x, 2);
    return 0;
}
