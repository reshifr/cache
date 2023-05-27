#ifndef MIND_CRYPT_SCRYPT_H
#define MIND_CRYPT_SCRYPT_H 1

#include <algorithm>

#include "types.h"
#include "cryptopp/scrypt.h"
#include "cryptopp/secblock.h"
#include "cryptopp/cryptlib.h"

namespace mind {

class scrypt_conf {
public:
  static constexpr auto P = 1U;
  static constexpr auto R = 24U;
  static constexpr auto N = 8192U;
};

template <u L, class Slt>
class scrypt : public scrypt_conf {
  static_assert(L>0, "Length must be greater than 0.");
public:
  sblk<L> operator()(const str& data, const Slt& salt) {
    CryptoPP::SecByteBlock dk(L);
    CryptoPP::Scrypt hg;
    hg.DeriveKey(dk, L,
      reinterpret_cast<const b*>(data.c_str()),
      data.length(), salt.data(), salt.size(), N, R, P);
    sblk<L> hv;
    std::copy_n(dk.begin(), L, hv.begin());
    return hv;
  }
};

} // namespace mind

#endif // MIND_CRYPT_SCRYPT_H
