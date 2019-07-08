#ifndef HYPER_SODIUM_H
#define HYPER_SODIUM_H

#include <string>
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
    Util::Buffer<uint8_t> genericHash(const Buf& in, size_t size);

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
    Util::Buffer<uint8_t> genericHash(const Buf& in, const Buf& key, size_t size);

  } // namespace Sodium
} // namespace Hyper

#endif
