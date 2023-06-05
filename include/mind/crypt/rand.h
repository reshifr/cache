#ifndef MIND_CRYPT_RAND_H
#define MIND_CRYPT_RAND_H 1

#include "mind/mind.h"
#include "mind/crypt/rdrand.h"
#include "mind/crypt/osrand.h"

namespace mind {

/**
 * \brief Abstract random number generator
 * \tparam L Block length in bytes, the default is 0
 * \note If the RDRAND instruction is available, it is used.
 *       Otherwise, the OS random number generator is used.
 */
#if defined(MIND_RDRAND_ENABLED)
template <u L=u(0)>
class rand : public rdrand<L> {};
#else
template <u L=u(0)>
class rand : public osrand<L> {};
#endif /* MIND_RDRAND_ENABLED */

} /* namespace mind */

#endif /* MIND_CRYPT_RAND_H */
