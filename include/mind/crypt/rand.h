#ifndef MIND_CRYPT_RAND_H
#define MIND_CRYPT_RAND_H 1

#include <concepts>

#include "mind/types.h"
#include "mind/crypt/osrand.h"

namespace mind {

/**
 * \brief Random number generator
 * \tparam L Block length in bytes
 */
template <u L, class Rd>
concept rand_concept = requires(Rd rand) {
  requires L>0;
  { rand.operator()() } -> std::same_as<sblk<L>>;
};

/**
 * \brief Abstract random number generator
 * \tparam L Block length in bytes
 * \tparam Rd Random number generator
 */
template <u L, class Rd=osrand<L>>
requires rand_concept<L, Rd>
using rand = Rd;

} // namespace mind

#endif // MIND_CRYPT_RAND_H
