#ifndef CRYPT_CIPHER_HPP
#define CRYPT_CIPHER_HPP 1

#include <crypt/chacha20poly1305.hpp>
#include <crypt/crypt.hpp>
#include <string>

template <class Salt, class Chiper = chacha20poly1305<Salt>> class cipher {
public:
  cipher(const Salt &salt) : m_salt(salt){};
  dynamic_block encrypt(const std::string &secret, const std::string &message) {
    Chiper chipergen(m_salt);
    return chipergen.encrypt(secret, message);
  }

  std::string decrypt(const std::string &secret,
                      const dynamic_block &cipherblock) {
    Chiper chipergen(m_salt);
    return chipergen.decrypt(secret, cipherblock);
  }

private:
  Salt m_salt;
};

#endif // CRYPT_CIPHER_HPP