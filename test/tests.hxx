#ifndef HYPER_SODIUM_TEST_H
#define HYPER_SODIUM_TEST_H

#include <iostream>
#include <sodium.h>

#include "../deps/heapwolf/cxx-tap/index.hxx"
#include "../index.hxx"

using Buf = Hyper::Util::Buffer<uint8_t>;
void genericHashing(TAP::Test& t);

#endif
