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
      auto size = crypto_generichash_BYTES;
      auto out = Hyper::Sodium::genericHash(in, size);

      std::string expected = "511bc81dde11180838c562c82bb35f3223f46061ebde4a955c27b3f489cf1e03";
      t->equal(out.toString("hex"), expected, "hashed buffer");
    }

    {
      auto size = crypto_generichash_BYTES_MIN;
      auto out = Hyper::Sodium::genericHash(in, size);

      std::string expected = "3895c59e4aeb0903396b5be3fbec69fe";
      t->equal(out.toString("hex"), expected, "hashed buffer min");
    }

    {
      auto size = crypto_generichash_BYTES_MAX;
      auto out = Hyper::Sodium::genericHash(in, size);

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
      auto size = crypto_generichash_BYTES;
      auto out = Hyper::Sodium::genericHash(in, key, size);

      std::string expected = "f4113fe33d43c24c54627d40efa1a78838d4a6d689fd6e83c213848904fffa8c";
      t->equal(out.toString("hex"), expected, "hashed buffer");
    }

    {
      auto size = crypto_generichash_BYTES_MIN;
      auto out = Hyper::Sodium::genericHash(in, key, size);

      t->equal(out.toString("hex"), "c8226257b0d1c3dcf4bbc3ef79574689", "hashed buffer min");
    }

    {
      auto size = crypto_generichash_BYTES_MAX;
      auto out = Hyper::Sodium::genericHash(in, key, size);

      auto res = "763eda46f4c6c61abb4310eb8a488950e9e0667b2fca03c463dc7489e94f065b7af6063fe86b0441c3eb9052800121d55730412abb2cbe0761b1d66f9b047c1c";
      t->equal(out.toString("hex"), res, "hashed buffer max");
    }

    t->end();
  });

  t.test("generic multipart hash", [](auto t) {
    Hyper::Sodium::MultipartHash mph(crypto_generichash_BYTES);
    Hyper::Util::Buffer<uint8_t> filler("Hej, Verden");

    for (size_t i = 0; i < 10; i++) {
      mph.update(filler);
    }

    auto out = mph.final(crypto_generichash_BYTES);

    t->equal(out.toString("hex"), "cbc20f347f5dfe37dc13231cbf7eaa4ec48e585ec055a96839b213f62bd8ce00", "streaming hash");
    t->end();
  });

  t.test("crypto_generichash_instance with key", [](auto t) {
    Hyper::Util::Buffer<uint8_t> keyBuf(crypto_generichash_KEYBYTES);
    auto key = keyBuf.fill("lo");

    Hyper::Sodium::MultipartHash mph(key, crypto_generichash_BYTES);
    Hyper::Util::Buffer<uint8_t> filler("Hej, Verden");

    for (size_t i = 0; i < 10; i++) {
      mph.update(filler);
    }

    auto out = mph.final(crypto_generichash_BYTES);

    t->equal(out.toString("hex"), "405f14acbeeb30396b8030f78e6a84bab0acf08cb1376aa200a500f669f675dc", "streaming hash");
    t->end();
  });

  t.test("crypto_generichash_instance with hash length", [](auto t) {
    Hyper::Sodium::MultipartHash mph(crypto_generichash_BYTES_MIN);
    Hyper::Util::Buffer<uint8_t> filler("Hej, Verden");

    for (size_t i = 0; i < 10; i++) {
      mph.update(filler);
    }

    auto out = mph.final(crypto_generichash_BYTES_MIN);

    t->equal(out.toString("hex"), "decacdcc3c61948c79d9f8dee5b6aa99", "streaming short hash");
    t->end();
  });
}
