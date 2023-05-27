#ifndef MIND_TYPES_H
#define MIND_TYPES_H 1

#include <array>
#include <string>
#include <vector>
#include <cstdint>

namespace mind {
  /**
   * Integer types.
   */
  using b = std::uint8_t;
  using i = std::int32_t;
  using u = std::uint32_t;
  using i8 = std::int8_t;
  using u8 = std::uint8_t;
  using i16 = std::int16_t;
  using u16 = std::uint16_t;
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  /**
   * Block types.
   */
  using str = std::string;
  using dblk = std::vector<b>;
  template <u L> using sblk = std::array<b, L>;
} // namespace mind

#endif // MIND_TYPES_H
