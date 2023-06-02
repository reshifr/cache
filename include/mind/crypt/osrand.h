#ifndef MIND_CRYPT_OSRAND_H
#define MIND_CRYPT_OSRAND_H 1

#include "mind/types.h"
#include "cryptopp/osrng.h"

namespace mind {

/**
 * \brief OS random number generator error
 */
class osrand_error : exception {
public:
  static constexpr auto OSRAND_FAILED =
    "Mind Error: OS failed to generate random number.";
  const char* what(void) const noexcept override { return OSRAND_FAILED; }
};

/**
 * \brief OS random number generator
 * \tparam L Block length in bytes
 * \note `L` must be greater than 0.
 */
template <u L>
class osrand {
public:
  using blk_t = sblk<L>;

  /**
   * \brief Generate secure random block
   * \return A secure random block
   * \throws osrand_error Error in generating random number
   */
  blk_t operator()(void) const {
    blk_t rn;
    try {
      CryptoPP::AutoSeededRandomPool rng;
      rng.GenerateBlock(rn.data(), L);
    } catch(...) {
      throw osrand_error();
    }
    return rn;
  }
};

} // namespace mind

#endif // MIND_CRYPT_OSRAND_H
