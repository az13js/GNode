# GNode

GNode 是一个使用 `C++` 实现的节点库。

## 使用指导

- 在你的源码中包含头文件 `GNode/Node.h` 。
- 使用命名空间 `GNode` 以引入 GNode 提供的功能。

示例：

```C++
#include "GNode/Node.h"

int main() {
    using namespace GNode;
    auto a = Node();
    a.debug();
    return 0;
}
```

## 基本用法

### 创建节点

```C++
auto a = Node(1); // 节点 a 的值等于 1
a.debug();
auto b = Node(); // 节点 b 没有赋初始值
b.debug();
```

节点的 `debug()` 方法用来打印关于此节点的信息。可在初始化时赋予节点值，也可以
不赋值，不赋值时默认值为 `0` 。节点的值是一个 `int` 类型的整数。

### 修改节点的值

可以在初始化节点的时候对节点赋予初始化值，例如：

```C++
auto a = Node(12);
```

而在创建后可以通过 `changeValue()` 方法修改节点的值，如：

```C++
auto a = Node(12);
a.debug();
a.changeValue(2);
a.debug();
```

### 获取节点的值

可以通过 `getValue()` 方法，获得节点的值。

```C++
#include "GNode/Node.h"
#include <iostream>

int main() {
    using namespace GNode;
    using namespace std;
    auto a = Node(12);
    cout << a.getValue() << endl;
    return 0;
}
```

### 添加子节点

方法 `addChild()` 提供在一个节点下添加子节点的功能。

```C++
auto a = Node();
a.addChild(Node(1));
a.addChild(Node(2));
a.addChild(Node(3));
for (auto i : a.getChildren()) {
    cout << "i value:" << i.getValue() << endl;
}
```

### 获取所有的子节点

方法 `getChildren()` 返回一个列表，包含了节点中存在的所有子节点。注意列表中的
子节点顺序和添加时的顺序不一定是相同的。

```C++
#include "GNode/node.h"
#include <iostream>

using namespace std;
using namespace GNode;

int main() {
    auto a = Node();
    a.addChild(Node(1));
    a.addChild(Node(2));
    a.addChild(Node(3));
    for (auto i : a.getChildren()) {
        cout << "i value:" << i.getValue() << endl;
    }
    return 0;
}
```

### 移除给定的子节点

方法 `removeChild()` 可以移除指定的子节点。

```C++
#include "GNode/node.h"
#include <iostream>

using namespace std;
using namespace GNode;

int main() {
    auto x = Node();
    auto a = Node(1), b = Node(2), c = Node(3);
    x.addChild(a);
    x.addChild(b);
    x.addChild(c);
    cout << "Before remove:" << endl;
    for (auto i : x.getChildren()) {
        cout << "i value:" << i.getValue() << endl;
    }
    x.removeChild(b);
    cout << "After remove:" << endl;
    for (auto i : x.getChildren()) {
        cout << "i value:" << i.getValue() << endl;
    }
    return 0;
}
```

执行上面的示例，输出如下：

    Before remove:
    i value:3
    i value:2
    i value:1
    After remove:
    i value:3
    i value:1
