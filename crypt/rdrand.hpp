#ifndef CRYPT_RDRAND_HPP
#define CRYPT_RDRAND_HPP 1

#include <crypt/crypt.hpp>
#include <cryptopp/rdrand.h>

template <uint Length> class rdrand {
  static_assert(Length > 0, "Length must be greater than 0.");

public:
  static_block<Length> operator()(void) {
    static_block<Length> block;
    CryptoPP::RDRAND rng;
    rng.GenerateBlock(block.data(), Length);
    return block;
  }
};

#endif // CRYPT_RDRAND_HPP