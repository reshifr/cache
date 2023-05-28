#ifndef MIND_CRYPT_HASH_H
#define MIND_CRYPT_HASH_H 1

#include "types.h"
#include "crypt/scrypt.h"

namespace mind {

template <u L, class Slt, class H>
concept hash_concept = requires(H h) {
  requires L>0;
  requires requires(const Slt& salt) {
    { h(salt) } noexcept;
    { h(salt) } noexcept -> std::same_as<H&>;
  };
  requires requires(const str& data) {
    { h.operator()(data) } noexcept -> std::same_as<sblk<L>>;
  };
};

template <u L, class Slt, class H=scrypt<L, Slt>>
requires hash_concept<L, Slt, H>
using hash = H;

} // namespace mind

#endif // MIND_CRYPT_HASH_H
