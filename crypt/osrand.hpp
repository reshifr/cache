#ifndef CRYPT_OSRAND_HPP
#define CRYPT_OSRAND_HPP 1

#include <crypt/crypt.hpp>
#include <cryptopp/osrng.h>

template <uint Length> class osrand {
  static_assert(Length > 0, "Length must be greater than 0.");

public:
  static_block<Length> operator()(void) {
    static_block<Length> block;
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock(block.data(), Length);
    return block;
  }
};

#endif // CRYPT_OSRAND_HPP