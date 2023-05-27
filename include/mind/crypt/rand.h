#ifndef MIND_CRYPT_RAND_H
#define MIND_CRYPT_RAND_H 1

#include "types.h"
#include "crypt/osrand.h"

namespace mind {

template <u L, class Rd=osrand<L>>
class rand {
  static_assert(L>0, "Length must be greater than 0.");
public:
  sblk<L> operator()(void) {
    Rd rng;
    return rng();
  }
};

} // namespace mind

#endif // MIND_CRYPT_RAND_H
