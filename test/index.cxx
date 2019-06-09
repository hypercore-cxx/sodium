#include <iostream>
#include <sodium.h>

#include "../deps/heapwolf/cxx-tap/index.hxx"
#include "../index.hxx"

static const char chars[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(chars) - 1;

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

  t.test("base64 encode", [](auto t) {
    std::string str = "Hello, world!";

    auto expectedEncoded = std::string("SGVsbG8sIHdvcmxkIQ==");
    expectedEncoded.push_back('\0');

    auto encoded = Hyper::Sodium::base64Encode(str);
    t->equal(encoded, expectedEncoded, "matches gnu output");
    t->end();
  });

  t.test("base64 encode/decode random size", [](auto t) {

    std::string str;
    const int r = rand() % stringLength + 1;
    t->comment("encoding " + std::to_string(r) + " bytes");

    for (int i = 0; i < r; i++) {
      str.push_back(chars[rand() % stringLength]);
    }

    auto encoded = Hyper::Sodium::base64Encode(str);
    auto decoded = Hyper::Sodium::base64Decode(encoded);
    t->equal(decoded, str, "decoded expected");

    t->end();
  });
}
