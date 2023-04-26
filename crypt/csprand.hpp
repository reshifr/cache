#ifndef CRYPT_CSPRAND_HPP
#define CRYPT_CSPRAND_HPP 1

#include <crypt/crypt.hpp>
#include <crypt/osrand.hpp>

template <uint Length, class Rand = osrand<Length>> class csprand {
  static_assert(Length > 0, "Length must be greater than 0.");

public:
  static_block<Length> operator()(void) {
    Rand randgen;
    return randgen();
  }
};

#endif // CRYPT_CSPRAND_HPP