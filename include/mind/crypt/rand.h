#ifndef MIND_CRYPT_RAND_H
#define MIND_CRYPT_RAND_H 1

#include <concepts>
#include "mind/types.h"
#include "mind/crypt/osrand.h"

#if defined(MIND_RDRAND_ENABLED)
# include "mind/crypt/rdrand.h"
#endif // MIND_RDRAND_ENABLED

namespace mind {

/**
 * \brief Random number generator constraint
 * \tparam L Block length in bytes
 * \tparam Rd Random number generator
 */
template <u L, class Rd>
concept rand_concept = requires(Rd rand) {
  requires(L>0);
  { rand.operator()() } -> std::same_as<typename Rd::blk>;
};

/**
 * \brief Abstract random number generator
 * \tparam L Block length in bytes
 * \tparam Rd Random number generator
 * \note `L` must be greater than 0.
 *       If the RDRAND instruction is available, it is used.
 *       Otherwise, the OS random number generator is used.
 */
#if defined(MIND_RDRAND_ENABLED)
template <u L, class Rd=rdrand<L>>
#else
template <u L, class Rd=osrand<L>>
#endif // MIND_RDRAND_ENABLED
requires rand_concept<L, Rd>
using rand = Rd;

} // namespace mind

#endif // MIND_CRYPT_RAND_H
