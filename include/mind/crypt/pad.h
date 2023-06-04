#ifndef MIND_CRYPT_PAD_H
#define MIND_CRYPT_PAD_H 1

#include "mind/types.h"
#include "mind/crypt/rand.h"
#include "mind/crypt/iso10126.h"

namespace mind {

template <template <u L> class Rd=rand>
class pad : public iso10126<Rd> {};

} // namespace mind

#endif // MIND_CRYPT_PAD_H
