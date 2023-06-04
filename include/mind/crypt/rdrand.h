#ifndef MIND_CRYPT_RDRAND_H
#define MIND_CRYPT_RDRAND_H 1

#include "mind/types.h"
#include "cryptopp/cpu.h"
#include "cryptopp/rdrand.h"

namespace mind {

/**
 * \brief RDRAND random number generator error
 */
class rdrand_error : rand_error {
public:
  static constexpr auto RDRAND_FAILED =
    "Mind Error: RDRAND instruction failed to generate random number.";
  static constexpr auto RDRAND_UNSUPPORTED =
    "Mind Error: RDRAND instruction is not supported.";
  const char* what(void) const noexcept override
    { return CryptoPP::HasRDRAND() ? RDRAND_FAILED : RDRAND_UNSUPPORTED; }
};

/**
 * \brief RDRAND random number generator base class
 */
class rdrand_base {
public:
  /**
   * \brief Generate dynamic secure random block
   * \param len Block length in bytes
   * \return A secure random block
   * \throws rdrand_error Error in generating random number
   * \throws rdrand_error RDRAND instruction is not supported
   */
  dblk operator()(u len) {
    dblk rn(len);
    try {
      m_rng.GenerateBlock(rn.data(), len);
    } catch(...) {
      throw rdrand_error();
    }
    return rn;
  }

  /**
   * \brief Generate secure random in-place block
   * \tparam In Input iterator type
   * \param in Iterator to the beginning of the block
   * \param len Block length in bytes
   * \throws rdrand_error Error in generating random number
   * \throws rdrand_error RDRAND instruction is not supported
   */
  template <typename In>
  void operator()(In in, u len) {
    try {
      m_rng.GenerateBlock(std::addressof(*in), len);
    } catch(...) {
      throw rdrand_error();
    }
  }

protected:
  CryptoPP::RDRAND m_rng;
};

/**
 * \brief RDRAND random number generator with `L` greater than 0
 * \tparam L Block length in bytes
 * \note If `L` is 0, then the base class functors are used.
 */
template <u L=u(0)>
class rdrand : public rdrand_base {
public:
  /**
   * \brief Generate static secure random block
   * \return A secure random block
   * \throws rdrand_error Error in generating random number
   * \throws rdrand_error RDRAND instruction is not supported
   */
   sblk<L> operator()(void) {
    sblk<L> rn;
    try {
      m_rng.GenerateBlock(rn.data(), L);
    } catch(...) {
      throw rdrand_error();
    }
    return rn;
  }
};

/**
 * \brief RDRAND random number generator with `L` equal to 0
 */
template <>
class rdrand<u(0)> : public rdrand_base {};

} // namespace mind

#endif // MIND_CRYPT_RDRAND_H
