#include <sodium.h>
#include <cstring>
#include "index.hxx"

namespace Hyper {
  namespace Sodium {
    std::string randomBytes(const size_t size) {
        const std::string s(size, 0);
        auto d = const_cast<char*>(s.data());
        randombytes_buf(d, size);
        return s;
    }

    std::string base64Encode (const std::string& str) {
      auto mlen = sodium_base64_ENCODED_LEN(str.size(), sodium_base64_VARIANT_URLSAFE);

      std::string res;
      res.resize(mlen);

      auto size = const_cast<char*>(res.data());
      auto data = (const unsigned char*) str.data();

      sodium_bin2base64(size, mlen, data, str.size(), sodium_base64_VARIANT_URLSAFE);
      return res;
    }

    std::string base64Decode (const std::string& str) {
      size_t bin_len;
      std::string res;
      res.resize(str.size());

      auto size = str.size();
      auto data = (uint8_t*) res.c_str();

		  sodium_base642bin(data, size, str.c_str(), size, 0, &bin_len, 0, sodium_base64_VARIANT_URLSAFE);
		  res.resize(bin_len);
      return res;
    }

  } // namespace Sodium
} // namespace Hyper


