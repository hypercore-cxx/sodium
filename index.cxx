#include <sodium.h>
#include <cstring>

#include "deps/datcxx/buffer/index.hxx"
#include "index.hxx"

namespace Hyper {
  using Buf = Util::Buffer<uint8_t>;

  namespace Sodium {
    std::string randomBytes(const size_t size) {
        const std::string s(size, 0);
        const auto d = const_cast<char*>(s.data());

        randombytes_buf(d, size);
        return s;
    }

    void genericHash(Buf& out, const Buf& in) {
      crypto_generichash(
        &out.value[0],
        out.value.size(),
        &in.value[0],
        in.value.size(),
        nullptr,
        0
      );
    }

    void genericHash(Buf& out, const Buf& in, const Buf& key) {
      crypto_generichash(
        &out.value[0],
        out.value.size(),
        &in.value[0],
        in.value.size(),
        &key.value[0],
        key.value.size()
      );
    }

  } // namespace Sodium
} // namespace Hyper


