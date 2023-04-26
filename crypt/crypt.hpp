#ifndef CRYPT_CRYPT_HPP
#define CRYPT_CRYPT_HPP 1

#include <array>
#include <cstdint>
#include <vector>

using byte = std::uint8_t;
using uint = std::uint32_t;
using ubigint = std::uint64_t;
using dynamic_block = std::vector<byte>;
template <uint Length> using static_block = std::array<byte, Length>;

#endif // CRYPT_CRYPT_HPP