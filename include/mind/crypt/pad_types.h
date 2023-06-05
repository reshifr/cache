#ifndef MIND_CRYPT_PAD_TYPES_H
#define MIND_CRYPT_PAD_TYPES_H 1

#include <bit>
#include "mind/mind.h"

namespace mind {

/**
 * \brief Padding configuration
 * \tparam L The length of the padding block
 * \note `L` must be a power of 2 between 1 and 128 bytes.
 */
template <u L>
class pad_config {
  static_assert(L>u(0) && L<=u(128) && (L&(L-u(1)))==u(0));
public:
  static constexpr u ALIGN_MASK = L-u(1);
  static constexpr u ALIGN_SHIFT = std::countr_zero(L);
};

class aes_pad_config : public pad_config<u(16)> {};
class chacha_pad_config : public pad_config<u(64)> {};
class twofish_pad_config : public pad_config<u(8)> {};
class serpent_pad_config : public pad_config<u(8)> {};
class xchacha_pad_config : public pad_config<u(64)> {};
class blowfish_pad_config : public pad_config<u(8)> {};

} /* namespace mind */

#endif /* MIND_CRYPT_PAD_TYPES_H */
