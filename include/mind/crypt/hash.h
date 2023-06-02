#ifndef MIND_CRYPT_HASH_H
#define MIND_CRYPT_HASH_H 1

#include "mind/types.h"
#include "mind/crypt/scrypt.h"

namespace mind {

/**
 * \brief Abstract hash function
 * \tparam L Block length in bytes
 * \tparam Slt Salt type
 * \tparam H Hash function
 * \note `L` must be greater than 0.
 */
template <u L, class Slt, class H=scrypt<L, Slt>>
using hash = H;

} // namespace mind

#endif // MIND_CRYPT_HASH_H
