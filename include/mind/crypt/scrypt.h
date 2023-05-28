#include <utility>
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
public:
  scrypt(const Slt& salt) noexcept: m_salt(salt) {}
  scrypt& operator()(const Slt& salt) noexcept {
    m_salt = salt;
    return *this;
  }

  sblk<L> operator()(const str& data, const Slt& salt) noexcept {
    CryptoPP::SecByteBlock dk(L);
    CryptoPP::Scrypt hg;
    hg.DeriveKey(dk, L,
      reinterpret_cast<const b*>(data.c_str()),
      data.length(), salt.data(), salt.size(), N, R, P);
    sblk<L> hv;
    std::copy_n(dk.begin(), L, hv.begin());
    return hv;
  }

private:
  Slt m_salt;
};

} // namespace mind

#endif // MIND_CRYPT_SCRYPT_H
