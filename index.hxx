#ifndef HYPER_SODIUM_H
#define HYPER_SODIUM_H

#include <cstring>
#include <initializer_list>
#include <sodium.h>
#include <string>

#include "deps/datcxx/buffer/index.hxx"
#include "src/generic.hxx"

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
  } // namespace Sodium
} // namespace Hyper

#endif
