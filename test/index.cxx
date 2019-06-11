#include <iostream>
#include <sodium.h>

#include "../deps/heapwolf/cxx-tap/index.hxx"
#include "../deps/datcxx/buffer/index.hxx"
#include "../index.hxx"

int main() {
  TAP::Test t;

  t.test("sanity", [](auto t) {
    t->ok(true, "true is true");
    t->end();
  });

  t.test("init sodium", [](auto t) {
    if (sodium_init() < 0) {
      t->fail("coult not init sodium");
      t->end();
    }

    t->pass("initialized sodium");
    t->end();
  });

  t.test("random bytes", [](auto t) {
    srand(time(NULL));

    auto size = rand() % 100 + 1;
    auto r = Hyper::Sodium::randomBytes(size);

    t->equal(r.size(), size, "correct number of bytes");
    t->end();
  });

  t.test("generic hash", [](auto t) {
    Hyper::Util::Buffer<uint8_t> in("Hello, world!");
    Hyper::Util::Buffer<uint8_t> out(crypto_generichash_BYTES_MAX);

    Hyper::Sodium::genericHash(out, in);

    std::string expected = "511bc81dde11180838c562c82bb35f3223f46061ebde4a955c27b3f489cf1e03";

    t->equal(out.toString("hex"), expected, "hashed buffer");
    t->end();
  });
}
