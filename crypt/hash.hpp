#ifndef CRYPT_HASH_HPP
#define CRYPT_HASH_HPP 1

#include <crypt/crypt.hpp>
#include <crypt/csprand.hpp>
#include <crypt/scrypt.hpp>
#include <string>

template <uint Length, class Salt> class hash {
  static_assert(Length > 0, "Length must be greater than 0.");

public:
  hash(const Salt &salt) : m_salt(salt){};
  static_block<Length> operator()(const std::string &data) {
    scrypt<Length, Salt> hashgen;
    return hashgen(data, m_salt);
  }

private:
  Salt m_salt;
};

#endif // CRYPT_HASH_HPP