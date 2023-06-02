#ifndef MIND_TRAITS_H
#define MIND_TRAITS_H 1

#include <concepts>
#include <type_traits>
#include <bits/utility.h>
#include "mind/types.h"

namespace mind {

/**
 * \brief Check if a type is a block
 * The block type must be either `dblk` or `sblk<L>`.
 * \tparam blk Block type
 */
template <class blk>
concept is_blk =
  std::is_same_v<std::remove_cv_t<blk>, dblk> ||
  std::is_same_v<std::remove_cv_t<blk>,
    sblk<std::tuple_size_v<std::remove_cv_t<blk>>>>;

} // namespace mind

#endif // MIND_TRAITS_H
