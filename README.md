# GNode

GNode 是一个使用 `C++` 实现的节点库。

## 使用说明

- 在你的源码中包含头文件 `GNode/Graph.h` 。
- 使用命名空间 `GNode` 以引入 GNode 提供的功能。

示例：

```C++
#include "GNode/Graph.h"
#include <iostream>

using namespace std;
using namespace GNode;

int main() {
    auto graph = new Graph(1);
    auto root = graph->getRoot();
    cout << "root = " << root->getValue() << endl;
    root->add(graph->create(2));
    root->add(graph->create(3));
    cout << "node in root:" << endl;
    for (auto n : root->getNodes()) {
        cout << n->getValue() << endl;
    }
    delete graph;
    return 0;
}
```

示例的输出是：

    root = 1
    node in root:
    2
    3

首先需要创建图（`Graph`），因为节点都是算到某一张图里面的。代码里面的参数`1`表示初始化
图的时候给根节点赋值为`1`。一张图必须且只能有一个根节点。

```C++
auto graph = new Graph(1);
```

创建图之后，可以使用`getRoot()`方法获得图的根节点，使用的时候其它节点都是以根节点为
中心扩展的。

```C++
auto root = graph->getRoot();
```

无论根节点还是我们新建的节点，都有一个`getValue()`方法，用来获得节点存储的值。代码获取
并输出了根节点的值。

```C++
cout << "root = " << root->getValue() << endl;
```

可以在图上面使用`create()`方法创建新的节点，比如代码中的`graph->create(2)`和
`graph->create(3)`，是分别创建新的节点并初始化值为`2`和`3`。节点带有`add()`方法可以
用来添加指向其它节点的连接。例如代码中连接情况是

         1  (root)
       /   \
      |     |
      v     v
      2     3

实现这个图的构建的操作是：

```C++
root->add(graph->create(2));
root->add(graph->create(3));
```

想获得已知节点所指向的节点，可以使用`getNodes()`方法。

```C++
for (auto n : root->getNodes()) {
    cout << n->getValue() << endl;
}
```

除此之外示例代码中没有出现的用法是：

使用图的`getNodes()`方法可以获得图中所有创建出来的节点，无论节点有没有被根节点连接。

```C++
for (auto n : graph->getNodes()) {
    cout << n->getValue() << endl;
}
```

在给定节点上使用`remove()`方法可以断开节点到节点的连接。

```C++
auto node4 = graph->create(4);
root->add(node4);
root->remove(node4);
```

不需要手动`delete`删除节点，只需要删除图即可。如果中间创建了大量的节点且节点没有使用，
即没有直接或间接地从根节点连接到，那么这些节点占据的内存显然是多余的，此时使用
`graph->gc()`方法可以执行垃圾节点的删除。

```C++
#include "GNode/Graph.h"
#include <iostream>

using namespace GNode;

int main() {
    auto graph = new Graph();
    // 创建100个没用的节点
    for (int i = 0; i < 100; i++) {
        graph->create();
    }
    graph->gc(); // 执行垃圾节点清除，上面的100个节点会在这里被删掉

    // ...

    delete graph;
    return 0;
}
```
