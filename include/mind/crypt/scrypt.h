#ifndef MIND_CRYPT_SCRYPT_H
#define MIND_CRYPT_SCRYPT_H 1

#include <algorithm>
#include "mind/mind.h"
#include "cryptopp/scrypt.h"
#include "cryptopp/secblock.h"
#include "cryptopp/cryptlib.h"

namespace mind {

/**
 * \brief Scrypt configuration
 * Configuration parameters for the scrypt algorithm are:
 * - `P` (Parallelization) = 1
 * - `R` (Blockmix) = 24
 * - `N` (Cost) = 8192
 */
class scrypt_config {
public:
  static constexpr u P = 1U;
  static constexpr u R = 24U;
  static constexpr u N = 8192U;
};

/**
 * \brief Scrypt hash function
 * \tparam L The length of the hash value in bytes
 */
template <u L>
class scrypt : public scrypt_config {
public:
  /**
   * \brief Compute the hash of a data block
   * \tparam In The type of the input iterator
   * \tparam Sl The type of the salt
   * \param in The input iterator
   * \param len The length of the input data block
   * \param salt The salt
   * \return The hash value
   */
  template <typename In, class Sl>
  sblk<L> operator()(const In in,
    u len, const Sl& salt) noexcept {
    sblk<L> dk;
    m_hg.DeriveKey(dk.data(), L,
      std::addressof(*in), len, salt.data(), salt.size(), N, R, P);
    return dk;
  }

protected:
  CryptoPP::Scrypt m_hg;
};

} /* namespace mind */

#endif /* MIND_CRYPT_SCRYPT_H */
