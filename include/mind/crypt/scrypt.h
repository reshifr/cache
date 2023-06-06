#ifndef MIND_CRYPT_SCRYPT_H
#define MIND_CRYPT_SCRYPT_H 1

#include <algorithm>
#include "mind/mind.h"
#include "cryptopp/scrypt.h"
#include "cryptopp/cryptlib.h"

namespace mind {

/**
 * \brief Scrypt key derivation function configuration
 * Configuration parameters for the scrypt are:
 * - `P` (parallelization) = 1
 * - `R` (blockmix) = 24
 * - `N` (cost) = 8192
 */
class scrypt_config {
public:
  static constexpr auto P = u(1);
  static constexpr auto R = u(24);
  static constexpr auto N = u(8192);
};

/**
 * \brief Scrypt key derivation function
 * \tparam L The length of the derived key in bytes
 * \tparam Kdg The key derivation generator dependency
 */
template <u L, class Kdg=CryptoPP::Scrypt>
class scrypt : public scrypt_config {
public:
  /**
   * \brief Compute the derived key
   * \tparam In The type of the input iterator
   * \tparam Sl The type of the salt
   * \param in The input iterator
   * \param len The length of the input data block
   * \param salt The salt
   * \return The derived key
   */
  template <typename In, class Sl>
  sblk<L> operator()(const In in,
    u len, const Sl& salt) noexcept {
    sblk<L> dk;
    m_kdg.DeriveKey(dk.data(), L,
      std::addressof(*in), len, salt.data(), salt.size(), N, R, P);
    return dk;
  }

protected:
  Kdg m_kdg;
};

} /* namespace mind */

#endif /* MIND_CRYPT_SCRYPT_H */
