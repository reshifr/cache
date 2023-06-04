#ifndef MIND_CRYPT_OSRAND_H
#define MIND_CRYPT_OSRAND_H 1

#include "mind/mind.h"
#include "cryptopp/osrng.h"

namespace mind {

/**
 * \brief OS random number generator error
 */
class osrand_error : rand_error {
public:
  static constexpr auto OSRAND_FAILED =
    "Mind Error: OS failed to generate random number.";
  const char* what(void) const noexcept override { return OSRAND_FAILED; }
};

/**
 * \brief OS random number generator base class
 */
class osrand_base {
public:
  /**
   * \brief Generate dynamic secure random block
   * \param len Block length in bytes
   * \return A secure random block
   * \throws osrand_error Error in generating random number
   */
  dblk operator()(u len) {
    dblk rn(len);
    try {
      m_rng.GenerateBlock(rn.data(), len);
    } catch(...) {
      throw osrand_error();
    }
    return rn;
  }

  /**
   * \brief Generate secure random in-place block
   * \tparam In Input iterator type
   * \param in Iterator to the beginning of the block
   * \param len Block length in bytes
   * \throws osrand_error Error in generating random number
   */
  template <typename In>
  void operator()(In in, u len) {
    try {
      m_rng.GenerateBlock(std::addressof(*in), len);
    } catch(...) {
      throw osrand_error();
    }
  }

protected:
  CryptoPP::AutoSeededRandomPool m_rng;
};

/**
 * \brief OS random number generator with `L` greater than 0
 * \tparam L Block length in bytes
 * \note If `L` is 0, then the base class functors are used.
 */
template <u L=u(0)>
class osrand : public osrand_base {
public:
  /**
   * \brief Generate static secure random block
   * \return A secure random block
   * \throws osrand_error Error in generating random number
   */
   sblk<L> operator()(void) {
    sblk<L> rn;
    try {
      m_rng.GenerateBlock(rn.data(), L);
    } catch(...) {
      throw osrand_error();
    }
    return rn;
  }
};

/**
 * \brief OS random number generator with `L` equal to 0
 */
template <>
class osrand<u(0)> : public osrand_base {};

} /* namespace mind */

#endif /* MIND_CRYPT_OSRAND_H */
