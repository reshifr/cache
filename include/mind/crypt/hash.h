#ifndef MIND_CRYPT_HASH_H
#define MIND_CRYPT_HASH_H 1

#include <concepts>
#include "mind/types.h"
#include "mind/traits.h"
#include "mind/crypt/scrypt.h"

namespace mind {

/**
 * \brief Hash function constraint
 * \tparam L Block length in bytes
 * \tparam Slt Salt type
 * \tparam H Hash function
 */
template <u L, class Slt, class H>
concept hash_concept = requires(H h) {
  requires(L>0);
  requires(is_blk<Slt>);
  requires(
    requires(const typename H::slt& salt) {
      { h(salt) } noexcept;
    }
  );
  requires(
    requires(const dblk& data) {
      { h.operator()(data) } noexcept -> std::same_as<typename H::blk>;
    }
  );
};

/**
 * \brief Abstract hash function
 * \tparam L Block length in bytes
 * \tparam Slt Salt type
 * \tparam H Hash function
 * \note `L` must be greater than 0.
 *       The salt must be of type `dblk` or `sblk<L>`.
 */
template <u L, class Slt, class H=scrypt<L, Slt>>
requires hash_concept<L, Slt, H>
using hash = H;

} // namespace mind

#endif // MIND_CRYPT_HASH_H
