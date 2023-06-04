#ifndef MIND_CRYPT_ISO10126_H
#define MIND_CRYPT_ISO10126_H

#include "mind/types.h"
#include "mind/crypt/rand.h"

namespace mind {

class iso10126_config {
public:
  static constexpr u ALIGN_MASK = 7U;
  static constexpr u ALIGN_SHIFT = 3U;
  static constexpr u META_LENGTH = 1U;
  static constexpr u MIN_PAD_LENGTH = 128U;
};

template <template <u L> class Rd=rand>
class iso10126 : public iso10126_config {
public:
  void add(dblk& blk) {
    auto len = blk.size();
    auto max = iso10126::max_length(len);
    auto pl = max-len;
    blk.resize(max);
    m_rng(blk.data()+len, pl-META_LENGTH);
    blk[max-1] = static_cast<u8>(pl);
  }
  
  void del(dblk& blk) noexcept {
    auto len = blk.size();
    auto pl = blk[len-1];
    blk.resize(len-pl);
  }

protected:
  Rd<u(0)> m_rng;

  static u max_length(u len) noexcept {
    len += MIN_PAD_LENGTH;
    return (len&~ALIGN_MASK)+(((len&ALIGN_MASK)!=u(0))<<ALIGN_SHIFT);
  }
};

}

#endif // MIND_CRYPT_ISO10126_H
