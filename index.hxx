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
    /// comment returns std::string of random bytes.
    ///
    std::string randomBytes(size_t size);

    ///
    /// function genericHash(const std::string& str)
    /// comment Generate a generic hash.
    /// param str the string to be hashed.
    ///
    /// return std::string
    /// comment the result from hashing the input.
    ///
    void genericHash(Buf& out, const Buf& in);
    void genericHash(Buf& out, const Buf& in, const Buf& key);

  } // namespace Sodium
} // namespace Hyper

#endif
