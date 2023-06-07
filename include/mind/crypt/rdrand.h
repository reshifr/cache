#ifndef MIND_CRYPT_RDRAND_H
#define MIND_CRYPT_RDRAND_H 1

#include "mind/mind.h"
#include "cryptopp/cpu.h"
#include "cryptopp/rdrand.h"
#include "mind/crypt/rand_types.h"

namespace mind {

/**
 * \brief RDRAND random number generator error
 */
class rdrand_error : public rand_error {
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
 * \tparam Rng Random number generator dependency
 */
template <class Rng>
class rdrand_base {
public:
  /**
   * \brief Default constructor
   * \throws rdrand_error Error in generating random number
   * \throws rdrand_error RDRAND instruction is not supported
   */
  rdrand_base() try {} catch(...)
    { throw rdrand_error(); }

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
  Rng m_rng;
};

/**
 * \brief RDRAND random number generator with `L` greater than 0
 * \tparam L Block length in bytes
 * \tparam Rng Random number generator dependency
 * \note If `L` is 0, then the base class functors are used.
 */
template <u L=u(0), class Rng=CryptoPP::RDRAND>
class rdrand : public rdrand_base<Rng> {
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
      this->m_rng.GenerateBlock(rn.data(), L);
    } catch(...) {
      throw rdrand_error();
    }
    return rn;
  }
};

/**
 * \brief RDRAND random number generator with `L` equal to 0
 */
template <class Rng>
class rdrand<u(0), Rng> : public rdrand_base<Rng> {};

} /* namespace mind */

#endif /* MIND_CRYPT_RDRAND_H */
