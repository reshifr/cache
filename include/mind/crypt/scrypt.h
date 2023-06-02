#ifndef MIND_CRYPT_SCRYPT_H
#define MIND_CRYPT_SCRYPT_H 1

#include <algorithm>
#include "mind/types.h"
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
  static constexpr auto P = 1U;
  static constexpr auto R = 24U;
  static constexpr auto N = 8192U;
};

/**
 * \brief Scrypt hash function
 * \tparam L The length of the hash
 * \tparam Slt The type of the salt
 * \note `L` must be greater than 0.
 */
template <u L, class Slt>
class scrypt : public scrypt_config {
public:
  using blk_t = sblk<L>;
  using slt_t = Slt;

  /**
   * \brief Initialize the object with a salt
   * \param salt The salt
   */
  scrypt(const slt_t& salt) noexcept: m_salt(salt) {}

  /**
   * \brief Compute the hash of a data block
   * \param data The data block
   * \tparam Blk The type of the data block
   * \return The hash of the data block
   */
  template <class Blk>
  blk_t operator()(const Blk& data) noexcept {
    CryptoPP::SecByteBlock dk(L);
    CryptoPP::Scrypt hg;
    hg.DeriveKey(dk, L, data.data(),
      data.size(), m_salt.data(), m_salt.size(), N, R, P);
    blk_t hv;
    std::copy_n(dk.begin(), L, hv.begin());
    return hv;
  }

private:
  slt_t m_salt;
};

} // namespace mind

#endif // MIND_CRYPT_SCRYPT_H
