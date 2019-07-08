#ifndef HYPER_SODIUM_H
#define HYPER_SODIUM_H

#include <string>
#include <initializer_list>
#include <sodium.h>

#include "deps/datcxx/buffer/index.hxx"

///
/// namespace Hyper
///
namespace Hyper {
  ///
  /// namespace Sodium
  ///
  namespace Sodium {
    using Buf = Util::Buffer<uint8_t>;

    ///
    /// class MultiPart
    /// comment Provides a way to create, update and digest generic hashes.
    ///
    class MultiPart {
      size_t hashSize = 0;
      crypto_generichash_state state;

      public:

        ///
        /// constructor MultiPart(size_t size)
        /// comment creates a hash that can be updated.
        ///
        /// param size the specified output size.
        ///
        MultiPart (size_t size);

        ///
        /// constructor MultiPart(const Buf& key, size_t size)
        /// comment creates a hash that can be updated.
        ///
        /// param key a buffer containing a key.
        /// param size the specified output size.
        ///
        MultiPart (const Buf& key, size_t size);

        ///
        /// method update(const Buf& buf)
        /// comment update the instance of the hash.
        ///
        /// param buf the buffer to be used as the update value.
        ///
        /// return void
        ///
        void update (const Buf& buf);

        ///
        /// method update(const std::string str)
        /// comment update the instance of the hash.
        ///
        /// param buf the string to be used as the update value.
        ///
        /// return void
        ///
        void update (const std::string str);

        ///
        /// method final(size_t size)
        /// commment get the final value as a buffer.
        ///
        /// params size the size of the buffer to be returned.
        ///
        /// return Hyper::Util::Buffer<uint8_t>
        ///
        Buf final ();
    };

    ///
    /// function randomBytes(size_t size)
    /// comment https://libsodium.gitbook.io/doc/generating_random_data#usage
    /// param size the total number of random bytes produced.
    ///
    /// return std::string
    /// comment returns a string of random bytes.
    ///
    std::string randomBytes(size_t size);

    ///
    /// function genericHash(const Hyper::Util::Buffer& in, size_t size)
    /// comment Generate a generic hash.
    /// param in the value to be hashed.
    /// param size the size of the output.
    ///
    /// return Hyper::Util::Buffer<uint8_t>
    /// comment returns a new buffer.
    ///
    Buf genericHash(const Buf& in, size_t size);

    ///
    /// function genericHash(const Hyper::Util::Buffer& in, const Hyper::Util::Buffer& key, size_t size)
    /// comment Generate a generic hash using a key.
    /// param in the value to be hashed.
    /// param key the the buffer containing the key.
    /// param size the size of the output.
    ///
    /// return Hyper::Util::Buffer<uint8_t>
    /// comment returns a new buffer.
    ///
    Buf genericHash(const Buf& in, const Buf& key, size_t size);

    ///
    /// function genericBatchHash(std::vector<Hyper::Util::Buffer> batch, size_t size)
    /// comment Generate a generic hash from a batch of hashes.
    /// param batch the vector of hashes to be hashed.
    /// param size the size of the output.
    ///
    /// return Hyper::Util::Buffer<uint8_t>
    /// comment returns a new buffer.
    ///
    Buf genericHashBatch(std::vector<Buf> batch, size_t size);

    ///
    /// function genericBatchHash(std::vector<Hyper::Util::Buffer> batch, const Hyper::Util::Buffer& key, size_t size)
    /// comment Generate a generic hash from a batch of hashes.
    /// param batch the vector of hashes to be hashed.
    /// param key the the buffer containing the key.
    /// param size the size of the output.
    ///
    /// return Hyper::Util::Buffer<uint8_t>
    /// comment returns a new buffer.
    ///
    Buf genericHashBatch(std::vector<Buf> batch, const Buf& key, size_t size);

  } // namespace Sodium
} // namespace Hyper

#endif
