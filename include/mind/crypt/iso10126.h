#ifndef MIND_CRYPT_ISO10126_H
#define MIND_CRYPT_ISO10126_H 1

#include "mind/mind.h"
#include "mind/crypt/rand.h"
#include "mind/crypt/pad_types.h"

namespace mind {

/**
 * \brief ISO 10126 padding configuration scheme
 * Configuration parameters for the ISO 10126 padding scheme are:
 * - `META_LENGTH` (padding meta data length) = 1 byte
 * - `MIN_PAD_LENGTH` (minimum padding length) = 128 bytes
 */
class iso10126_config {
public:
  static constexpr auto META_LENGTH = u(1);
  static constexpr auto MIN_PAD_LENGTH = u(128);
};

/**
 * \brief ISO 10126 padding scheme
 * \tparam Cfg The padding configuration scheme
 * \tparam Rd The random number generator
 */
template <
  class Cfg=xchacha_pad_config,
  template <u L> class Rd=rand>
class iso10126 : public iso10126_config {
public:
  /**
   * \brief Add padding to a data block
   * \param blk The data block
   * \throws rand_error If the random number generator fails
   */
  void add(dblk& blk) {
    auto len = blk.size();
    auto max = max_length(len);
    auto pl = max-len;
    blk.resize(max);
    m_rng(blk.data()+len, pl-META_LENGTH);
    blk.back() = static_cast<u8>(pl-MIN_PAD_LENGTH);
  }

  /**
   * \brief Create a padded data block
   * \param blk The data block
   * \return The padded data block
   * \throws rand_error If the random number generator fails
   */
  dblk add(const dblk& blk) {
    dblk rblk(blk);
    add(rblk);
    return rblk;
  }

  /**
   * \brief Remove padding from a data block
   * \param blk The data block
   */
  void del(dblk& blk) noexcept {
    auto len = blk.size();
    auto pl = blk.back()+MIN_PAD_LENGTH;
    blk.resize(len-pl);
  }

  /**
   * \brief Create an unpadded data block
   * \param blk The data block
   * \return The unpadded data block
   */
  dblk del(const dblk& blk) noexcept {
    dblk rblk(blk);
    del(rblk);
    return rblk;
  }

protected:
  Rd<u(0)> m_rng;

  /**
   * \brief Count the maximum length of the data block can be padded
   * \param len The length of the data block
   * \return The maximum length of the data block can be padded
   */
  static u max_length(u len) noexcept {
    len += MIN_PAD_LENGTH;
    return (len&~Cfg::ALIGN_MASK)+
      (((len&Cfg::ALIGN_MASK)!=u(0))<<Cfg::ALIGN_SHIFT);
  }
};

} /* namespace mind */

#endif /* MIND_CRYPT_ISO10126_H */
