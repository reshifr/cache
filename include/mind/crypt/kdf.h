#ifndef MIND_CRYPT_KDF_H
#define MIND_CRYPT_KDF_H 1

#include "mind/types.h"
#include "mind/crypt/scrypt.h"

namespace mind {

/**
 * \brief Abstract key derivation function
 * \tparam L Block length in bytes
 * \note The default key derivation function is scrypt
 */
template <u L>
class kdf : public scrypt<L> {};

} // namespace mind

#endif // MIND_CRYPT_KDF_H
