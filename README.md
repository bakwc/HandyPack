# SaveLoad
[![Build Status][travis-image]][travis]

[travis-image]: https://travis-ci.org/bakwc/SaveLoad.svg?branch=master
[travis]: https://travis-ci.org/bakwc/SaveLoad

C++ serializer
```cpp
#include "saveload.h"

using namespace NSaveLoad;

struct Bar {
  int A;
  std::vector<std::string> B;
  std::list<Foo> C;
  SAVELOAD(A, B, C)
}

Bar bar;
std::stringstream out;
bar.Save(out);

std::string data = out.str();

Bar bar2;
imemstream in(data.c_str(), data.size());
bar2.Load(in);

```
