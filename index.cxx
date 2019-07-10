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
  } // namespace Sodium
} // namespace Hyper


