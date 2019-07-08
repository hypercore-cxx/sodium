#include <sodium.h>
#include <cstring>

#include "deps/datcxx/buffer/index.hxx"
#include "index.hxx"

namespace Hyper {
  using Buf = Util::Buffer<uint8_t>;

  namespace Sodium {
    MultipartHash::MultipartHash (size_t hashSize) {
      crypto_generichash_init(
        &this->state,
        nullptr,
        0,
        hashSize
      );
    }

    MultipartHash::MultipartHash (const Buf& key, size_t hashSize) {
      crypto_generichash_init(
        &this->state,
        &key.value[0],
        key.value.size(),
        hashSize
      );
    }

    void MultipartHash::update (const Buf& buf) {
      crypto_generichash_update(
        &this->state,
        &buf.value[0],
        buf.value.size()
      );
    }

    void MultipartHash::update (const std::string str) {
      Buf buf(str);

      crypto_generichash_update(
        &this->state,
        &buf.value[0],
        buf.value.size()
      );
    }

    Buf MultipartHash::final (size_t size) {
      Buf res(size);

      crypto_generichash_final(
        &this->state,
        &res.value[0],
        res.value.size()
      );

      return res;
    }

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


