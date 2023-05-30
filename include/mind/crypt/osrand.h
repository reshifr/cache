#ifndef MIND_CRYPT_OSRAND_H
#define MIND_CRYPT_OSRAND_H 1

#include "mind/types.h"
#include "cryptopp/osrng.h"

namespace mind {

template <u L>
class osrand {
public:
  sblk<L> operator()(void) const noexcept {
    sblk<L> rn;
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock(rn.data(), L);
    return rn;
  }
};

} // namespace mind

#endif // MIND_CRYPT_OSRAND_H
