#include "gtest/gtest.h"
#include "mind/crypt/rdrand.h"

TEST(test_rdrand, rdrand) {
  // Inputs
  constexpr mind::u size = 16;

  // Expectations
  constexpr mind::u exp_size = size;
  mind::sblk<size> exp_rn = mind::sblk<size>();

  // Providing inputs
  mind::rdrand<size> rng;
  auto rn = rng();

  // Checking outputs
  EXPECT_EQ(exp_size, rn.size());
  EXPECT_NE(exp_rn, rn);
}
