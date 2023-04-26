#ifndef CRYPT_SCRYPT_HPP
#define CRYPT_SCRYPT_HPP 1

#include <algorithm>
#include <crypt/crypt.hpp>
#include <cryptopp/cryptlib.h>
#include <cryptopp/scrypt.h>
#include <cryptopp/secblock.h>

template <uint Length, class Salt> class scrypt {
  static_assert(Length > 0, "Length must be greater than 0.");

public:
  static constexpr auto N = 8192U;
  static constexpr auto R = 24U;
  static constexpr auto P = 1U;

  static_block<Length> operator()(const std::string &data, const Salt &salt) {
    CryptoPP::SecByteBlock derived_key(Length);
    CryptoPP::Scrypt hashgen;
    hashgen.DeriveKey(derived_key, Length,
                      reinterpret_cast<const byte *>(data.c_str()),
                      data.length(), salt.data(), salt.size(), N, R, P);

    static_block<Length> hashval;
    std::copy_n(derived_key.begin(), Length, hashval.begin());
    return hashval;
  }
};

#endif // CRYPT_SCRYPT_HPP