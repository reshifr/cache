#ifndef MIND_TYPES_H
#define MIND_TYPES_H 1

#include <array>
#include <string>
#include <vector>
#include <cstdint>
#include <exception>

namespace mind {

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
 * \brief Dynamic block of bytes
 */
using dblk = std::vector<b>;

/**
 * \brief Static block of bytes
 * \tparam L Block length in bytes
 */
template <u L>
using sblk = std::array<b, L>;

/**
 * \brief Error
 */
class error : public std::exception {
public:
  static constexpr auto APP_ERROR =
    "Mind Error: There is an error.";
  static constexpr auto NOT_IMPLEMENTED =
    "Mind Error: Not implemented codes.";

  error(void) noexcept = default;
  error(error&&) noexcept = default;
  error(const error&) noexcept = default;
  error& operator=(error&&) noexcept = default;
  error& operator=(const error&) noexcept = default;
  error(const std::string& msg) noexcept: m_msg(msg) {}
  const char* what(void) const noexcept override
    { return m_msg.empty() ? APP_ERROR : m_msg.c_str(); }

private:
  std::string m_msg;
};

} /* namespace mind */

#endif /* MIND_TYPES_H */
