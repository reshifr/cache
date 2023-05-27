#ifndef MIND_CRYPT_OSRAND_H
#define MIND_CRYPT_OSRAND_H 1

#include "types.h"
#include "cryptopp/osrng.h"

namespace mind {

template <u L>
class osrand {
  static_assert(L>0, "Length must be greater than 0.");
public:
  sblk<L> operator()(void) {
    sblk<L> rn;
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock(rn.data(), L);
    return rn;
  }
};

} // namespace mind

#endif // MIND_CRYPT_OSRAND_H
