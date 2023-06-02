#ifndef MIND_CRYPT_RDRAND_H
#define MIND_CRYPT_RDRAND_H 1

#include "mind/types.h"
#include "cryptopp/cpu.h"
#include "cryptopp/rdrand.h"

namespace mind {

/**
 * \brief RDRAND random number generator error
 */
class rdrand_error : exception {
public:
  static constexpr auto RDRAND_FAILED =
    "Mind Error: RDRAND instruction failed to generate random number.";
  static constexpr auto RDRAND_UNSUPPORTED =
    "Mind Error: RDRAND instruction is not supported.";
  const char* what(void) const noexcept override
    { return CryptoPP::HasRDRAND() ? RDRAND_FAILED : RDRAND_UNSUPPORTED; }
};

/**
 * \brief RDRAND random number generator
 * \tparam L Block length in bytes
 * \note `L` must be greater than 0.
 */
template <u L>
requires(L>0)
class rdrand {
public:
  using blk = sblk<L>;

  /**
   * \brief Generate secure random block
   * \return A secure random block
   * \throws rdrand_error Error in generating random number
   */
  blk operator()(void) const {
    blk rn;
    try {
      CryptoPP::RDRAND rng;
      rng.GenerateBlock(rn.data(), L);
    } catch(...) {
      throw rdrand_error();
    }
    return rn;
  }
};

} // namespace mind

#endif // MIND_CRYPT_RDRAND_H
