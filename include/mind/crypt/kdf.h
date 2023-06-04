#ifndef MIND_CRYPT_KDF_H
#define MIND_CRYPT_KDF_H 1

#include "mind/types.h"
#include "mind/crypt/scrypt.h"

namespace mind {

/**
 * \brief Abstract key derivation function
 * \tparam L Block length in bytes
 * \tparam Kdf Key derivation function
 * \note The default key derivation function is scrypt
 */
template <u L, class Kdf=scrypt<L>>
using kdf = Kdf;

} // namespace mind

#endif // MIND_CRYPT_KDF_H
