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

    Buf genericHash(const Buf& in, size_t size) {
      Buf out(size);

      crypto_generichash(
        &out.value[0],
        out.value.size(),
        &in.value[0],
        in.value.size(),
        nullptr,
        0
      );

      return out;
    }

    Buf genericHash(const Buf& in, const Buf& key, size_t size) {
      Buf out(size);

      crypto_generichash(
        &out.value[0],
        out.value.size(),
        &in.value[0],
        in.value.size(),
        &key.value[0],
        key.value.size()
      );

      return out;
    }

  } // namespace Sodium
} // namespace Hyper


