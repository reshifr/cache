#ifndef MIND_CRYPT_ISO10126_H
#define MIND_CRYPT_ISO10126_H

#include "mind/types.h"
#include "mind/crypt/rand.h"

namespace mind {

class iso10126_config {
public:
  static constexpr u MIN_LENGTH = 256U;
  static constexpr u ALIGN_LENGTH = 8U;
};

template <template <u L> class Rd=rand>
class iso10126 : public iso10126_config {
public:
  static constexpr void pad(dblk& blk) {
  }
  static constexpr void unpad(dblk& blk) {
  }

private:
  static constexpr u get_pad_length(u len) {
    u dlen = len+MIN_LENGTH;
    
  }
};

}

#endif // MIND_CRYPT_ISO10126_H
