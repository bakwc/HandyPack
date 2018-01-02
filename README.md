# HandyPack
[![Build Status][travis-image]][travis]

[travis-image]: https://travis-ci.org/bakwc/HandyPack.svg?branch=master
[travis]: https://travis-ci.org/bakwc/HandyPack

Tiny C++ serializer. Single-header, supports POD types, classes and STL containers.
```cpp
#include "handypack.hpp"

using namespace NHandyPack;

struct Bar {
  int A;
  std::vector<std::string> B;
  std::list<Foo> C;
  HANDYPACK(A, B, C)
}

Bar bar;
std::stringstream out;
bar.Save(out);

std::string data = out.str();

Bar bar2;
imemstream in(data.c_str(), data.size());
bar2.Load(in);

```
