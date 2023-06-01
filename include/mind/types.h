#ifndef MIND_TYPES_H
#define MIND_TYPES_H 1

#include <array>
#include <string>
#include <vector>
#include <cstdint>
#include <utility>
#include <exception>

namespace mind {

/**
 * \brief Integer types
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
 * \brief String
 */
using str = std::string;

/**
 * \brief Dynamic block of bytes
 */
using dblk = std::vector<b>;

/**
 * \brief Static block of bytes
 * \tparam L Block length in bytes
 */
template <u L> using sblk = std::array<b, L>;

/**
 * \brief Exception
 */
class exception : public std::exception {
public:
  static constexpr auto NOT_IMPLEMENTED =
    "Mind Error: Not implemented codes.";
  exception(void) = default;
  exception(const str& msg) noexcept: m_msg(msg) {}
  exception(str&& msg) noexcept: m_msg(std::forward<str>(msg)) {}
  exception& operator=(exception&&) = default;
  exception& operator=(const exception&) = default;
  const char* what(void) const noexcept { return m_msg.c_str(); }

private:
  str m_msg;
};

} // namespace mind

#endif // MIND_TYPES_H
