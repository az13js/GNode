# GNode

GNode 是一个使用 `C++` 实现的节点库，它由少量的头文件组成，你可以简单地把它们集成到你
的项目中。

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
    auto graph = new Graph<int>(1);
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
auto graph = new Graph<int>(1);
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
用来添加到其它节点的连接。例如代码中连接情况是

         1  (root)
       /   \
      |     |
      2     3

实现这个图的构建的操作是：

```C++
root->add(graph->create(2));
root->add(graph->create(3));
```

想获得已知节点所连接的节点，可以使用`getNodes()`方法。

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
    auto graph = new Graph<int>(0);
    // 创建100个没用的节点
    for (int i = 0; i < 100; i++) {
        graph->create(1);
    }
    graph->gc(); // 执行垃圾节点清除，上面的100个节点会在这里被删掉

    // ...

    delete graph;
    return 0;
}
```

节点库的`Graph`类是模板类，除了`int`类型之外，支持使用其它类型作为节点容纳的对象类型。

```C++
#include "GNode/Graph.h"
#include <iostream>

using namespace std;
using namespace GNode;

int main() {
    auto graph = new Graph<double>(1.1);
    auto root = graph->getRoot();
    cout << "root = " << root->getValue() << endl;
    root->add(graph->create(2.1));
    root->add(graph->create(3.1));
    cout << "node in root:" << endl;
    for (auto n : root->getNodes()) {
        cout << n->getValue() << endl;
    }
    delete graph;
    return 0;
}
```

运行结果：

    root = 1.1
    node in root:
    2.1
    3.1

删除回调函数。你可以在创建图的时候，指定一个函数作为`gc()`方法或者删除节点时接收删除通知，以得知哪些节点被删除。如：

```C++
#include "GNode/Graph.h"
#include <iostream>

using namespace std;
using namespace GNode;

int main() {
    Graph<int> g(12, [](int x) {cout << "x=" << x << endl;});
    return 0;
}
```

上述代码当`g`被析构的时候，节点`12`会被删除，此时会输出：

    x=12

这种特性使得我们使用自定义的、创建在堆上的对象作为节点容纳的值的时候，能够获得节点删除的回调，使得我们可以同步地删除堆上的无用对象。

最后，`Graph`类的节点是双向连接的，这意味着我们从中间节点遍历时，会获得第一层的节点，如：

      A
     / \
    B   C
       / \
      D   E

我们调用`C`的`getNodes()`方法会得到`A`、`D`、`E`三个节点，因为这三个节点都连接到了`C`上。但我们不总是想要这样的特性，例如在一个由上到下构建的树结构的时候

      A
     / \
    v   v
    B   C
       / \
      v   v
      D   E

此时遍历应该是有方向的，只能从上到下不能反之，这种时候我们需要获得`C`的子节点就只能返回`D`和`E`才对。

针对这种情况请使用`Tree`模板类。

```C++
#include "GNode/Tree.h"
#include <iostream>

using namespace std;
using namespace GNode;

int main() {
    auto t = new Tree<char>('A');
    t->getRoot()->add(t->create('B'));
    auto c = t->create('B');
    c->add(t->create('D'));
    c->add(t->create('E'));
    t->getRoot()->add(c);
    for (auto e : c->getNodes()) {
        cout << e->getValue() << endl;
    }
    delete t;
    return 0;
}
```

上面代码执行将输出：

    D
    E
