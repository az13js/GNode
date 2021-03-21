#include "GNode/node.h"
#include <iostream>

using namespace std;
using namespace GNode;

int main() {
    auto x = Node(555);
    auto a = Node(1), b = Node(2), c = Node(3);
    x.debug();
    return 0;
}
