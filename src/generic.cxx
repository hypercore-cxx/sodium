#include "generic.hxx"

namespace Hyper {
  using Buf = Util::Buffer<uint8_t>;

  namespace Sodium {
    MultiPart::MultiPart (size_t size) : hashSize(size) {
      crypto_generichash_init(
        &this->state,
        nullptr,
        0,
        this->hashSize
      );
    }

    MultiPart::MultiPart (const Buf& key, size_t size) : hashSize(size) {
      crypto_generichash_init(
        &this->state,
        &key.value[0],
        key.value.size(),
        this->hashSize
      );
    }

    void MultiPart::update (const Buf& buf) {
      crypto_generichash_update(
        &this->state,
        &buf.value[0],
        buf.value.size()
      );
    }

    void MultiPart::update (const std::string str) {
      Buf buf(str);

      crypto_generichash_update(
        &this->state,
        &buf.value[0],
        buf.value.size()
      );
    }

    Buf MultiPart::final () {
      Buf res(this->hashSize);

      crypto_generichash_final(
        &this->state,
        &res.value[0],
        res.value.size()
      );

      return res;
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

    Buf genericHashBatch(std::vector<Buf> batch, size_t size) {
      Buf res(size);

      crypto_generichash_state state;
      crypto_generichash_init(&state, nullptr, 0, size);

      for (auto& buf : batch) {
        crypto_generichash_update(
          &state,
          &buf.value[0],
          buf.value.size()
        );
      }

      crypto_generichash_final(
        &state,
        &res.value[0],
        res.value.size()
      );

      return res;
    };

    Buf genericHashBatch(std::vector<Buf> batch, const Buf& key, size_t size) {
      Buf res(size);

      crypto_generichash_state state;
      crypto_generichash_init(&state, &key.value[0], key.value.size(), size);

      for (auto& buf : batch) {
        crypto_generichash_update(
          &state,
          &buf.value[0],
          buf.value.size()
        );
      }

      crypto_generichash_final(
        &state,
        &res.value[0],
        res.value.size()
      );

      return res;
    };
  } // namespace Sodium
} // namespace Hyper
