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
    Hyper::Util::Buffer<uint8_t> in("Hello, World!");

    {
      Hyper::Util::Buffer<uint8_t> out(crypto_generichash_BYTES);
      Hyper::Sodium::genericHash(out, in);

      std::string expected = "511bc81dde11180838c562c82bb35f3223f46061ebde4a955c27b3f489cf1e03";
      t->equal(out.toString("hex"), expected, "hashed buffer");
    }

    {
      Hyper::Util::Buffer<uint8_t> out(crypto_generichash_BYTES_MIN);
      Hyper::Sodium::genericHash(out, in);

      std::string expected = "3895c59e4aeb0903396b5be3fbec69fe";
      t->equal(out.toString("hex"), expected, "hashed buffer min");
    }

    {
      Hyper::Util::Buffer<uint8_t> out(crypto_generichash_BYTES_MAX);
      Hyper::Sodium::genericHash(out, in);

      std::string expected = "7dfdb888af71eae0e6a6b751e8e3413d767ef4fa52a7993daa9ef097f7aa3d949199c113caa37c94f80cf3b22f7d9d6e4f5def4ff927830cffe4857c34be3d89";
      t->equal(out.toString("hex"), expected, "hashed buffer max");
    }

    t->end();
  });

  t.test("generic hash with key", [](auto t) {
    Hyper::Util::Buffer<uint8_t> in("Hello, World!");
    Hyper::Util::Buffer<uint8_t> buf(crypto_generichash_KEYBYTES);

    auto key = buf.fill("lo");

    {
      Hyper::Util::Buffer<uint8_t> out(crypto_generichash_BYTES);
      Hyper::Sodium::genericHash(out, in, key);

      std::string expected = "f4113fe33d43c24c54627d40efa1a78838d4a6d689fd6e83c213848904fffa8c";
      t->equal(out.toString("hex"), expected, "hashed buffer");
    }

    t->end();
  });
}
