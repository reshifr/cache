#ifndef MIND_CRYPT_SCRYPT_H
#define MIND_CRYPT_SCRYPT_H 1

#include <algorithm>
#include "mind/types.h"
#include "mind/traits.h"
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
class scrypt_conf {
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
 *       The salt must be of type `dblk` or `sblk<L>`.
 */
template <u L, class Slt>
requires(L>0 && is_blk<Slt>)
class scrypt : public scrypt_conf {
public:
  using blk = sblk<L>;
  using slt = Slt;

  /**
   * \brief Initialize the object with a salt
   * \param salt A salt
   */
  scrypt(const slt& salt) noexcept: m_salt(salt) {}

  /**
   * \brief Compute the hash of a data block
   * \param data The data block
   * \tparam Blk The type of the data block
   * \return The hash of the data block
   * \note The data block must be of type `dblk` or `sblk<L>`.
   */
  template <class Blk>
  requires(is_blk<Blk>)
  blk operator()(const Blk& data) noexcept {
    CryptoPP::SecByteBlock dk(L);
    CryptoPP::Scrypt hg;
    hg.DeriveKey(dk, L, data.data(),
      data.size(), m_salt.data(), m_salt.size(), N, R, P);
    blk hv;
    std::copy_n(dk.begin(), L, hv.begin());
    return hv;
  }

private:
  slt m_salt;
};

} // namespace mind

#endif // MIND_CRYPT_SCRYPT_H
