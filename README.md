# SYNOPSIS
Libsodium utilities (work in progress).


# USAGE
This module is designed to work with the [`datcxx`][0] build tool. To add this
module to your project us the following command...

```bash
build add datcxx/libsodium
```


# TEST

```bash
build test
```


# EXAMPLE

```c++
auto r = Hyper::Sodium::randomBytes(128);
// r.size() == size

auto encoded = Hyper::Sodium::base64Encode("Hello, world!");
// encoded == SGVsbG8sIHdvcmxkIQ==

auto decoded = Hyper::Sodium::base64Decode(encoded);
// decoded == "Hello, world!"
```

