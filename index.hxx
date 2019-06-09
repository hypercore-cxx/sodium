#ifndef HYPER_SODIUM_H
#define HYPER_SODIUM_H

#include <string>
#include <sodium.h>

///
/// namespace Hyper
///
namespace Hyper {
  ///
  /// namespace Sodium
  ///
  namespace Sodium {
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
    /// function base64Encode(const std::string& str)
    /// comment base64 encodes a string.
    /// param str the string to be encoded.
    ///
    /// return std::string
    /// comment provides the base64 encoded string.
    ///
    std::string base64Encode(const std::string& str);

    ///
    /// function base64Encode(const std::string& str)
    /// comment decodes a base64 encoded string.
    /// param str the string to be decoded.
    ///
    /// return std::string
    /// comment provides the decoded string.
    ///
    std::string base64Decode(const std::string& str);
  } // namespace Sodium
} // namespace Hyper

#endif
