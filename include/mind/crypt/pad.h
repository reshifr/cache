#ifndef MIND_CRYPT_PAD_H
#define MIND_CRYPT_PAD_H 1

#include "mind/mind.h"
#include "mind/crypt/rand.h"
#include "mind/crypt/iso10126.h"
#include "mind/crypt/pad_types.h"

namespace mind {

/**
 * \brief Padding scheme
 * \tparam Cfg The padding configuration scheme
 * \tparam Rd The random number generator
 */
template <
  class Cfg=xchacha_pad_config,
  template <u L> class Rd=rand>
class pad : public iso10126<Cfg, Rd> {};

} /* namespace mind */

#endif /* MIND_CRYPT_PAD_H */
