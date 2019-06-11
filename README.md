# SYNOPSIS
Libsodium utilities (work in progress).


# USAGE
This module is designed to work with the [`datcxx`][0] build tool. To add this
module to your project us the following command...

```bash
build add datcxx/sodium
```


# TEST

```bash
build test
```


# EXAMPLE

```c++
#include "deps/datcxx/sodium/index.hxx"

auto r = Hyper::Sodium::randomBytes(128);
// r.size() == 128
```


[0]:https://github.com/datcxx/build
