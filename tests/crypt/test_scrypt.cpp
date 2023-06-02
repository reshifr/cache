#include <string_view>
#include "gtest/gtest.h"
#include "mind/crypt/scrypt.h"

TEST(test_scrypt, scrypt) {
  // Inputs
  constexpr mind::u size = 16;
  constexpr std::string_view data = "The Fox and the Grapes";
  auto datav = mind::dblk(data.begin(), data.end());
  constexpr mind::sblk<size> salt = {
    0xe3, 0xe8, 0x62, 0xe5, 0x77, 0xbc, 0xc1, 0x28,
    0x7a, 0xae, 0x01, 0xbb, 0x6d, 0x40, 0xdc, 0x2f
  };

  // Expectations
  constexpr mind::u exp_size = size;
  constexpr mind::sblk<exp_size> exp_hv = {
    0xe3, 0x36, 0xdd, 0x66, 0xaf, 0x91, 0xdb, 0x14,
    0x99, 0xc9, 0x6a, 0x74, 0xf6, 0x9d, 0x58, 0x5f
  };

  // Providing inputs
  mind::scrypt<size, decltype(salt)> h(salt);
  auto hv = h(datav);

  // Checking outputs
  EXPECT_EQ(exp_size, hv.size());
  EXPECT_EQ(exp_hv, exp_hv);
}
