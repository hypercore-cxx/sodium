#include "tests.hxx"

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

  genericHashing(t);
}
