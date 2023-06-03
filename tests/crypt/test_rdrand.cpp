#include "gtest/gtest.h"
#include "mind/crypt/rdrand.h"

////////////////////////////////////////////////////////////////////////////////
template <typename Tl>
class sblk_functor_test : public testing::Test {};
TYPED_TEST_SUITE_P(sblk_functor_test);

/**
 * \brief Test `rdrand<Tl::value>::operator()`
 */
TYPED_TEST_P(sblk_functor_test, sblk_functor) {
  // Inputs
  constexpr auto size = TypeParam::value;
  // Expectations
  constexpr auto exp_size = size;
  mind::sblk<size> exp_rn{};
  // Providing inputs
  mind::rdrand<size> rng;
  auto rn = rng();
  // Checking outputs
  EXPECT_EQ(exp_size, rn.size());
  EXPECT_NE(exp_rn, rn);
}

REGISTER_TYPED_TEST_SUITE_P(
  sblk_functor_test,
  sblk_functor
);

// Input types
using sblk_functor_test_types = testing::Types<
  std::integral_constant<mind::u, 1>,
  std::integral_constant<mind::u, 10>>;

INSTANTIATE_TYPED_TEST_SUITE_P(
  sblk_functor_instance_test,
  sblk_functor_test,
  sblk_functor_test_types
);
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
class dblk_functor_len_test : public testing::TestWithParam<mind::u> {};

TEST_P(dblk_functor_len_test, dblk_functor_len) {
  // Inputs
  auto size = GetParam();
  // Expectations
  auto exp_size = size;
  mind::dblk exp_rn{};
  // Providing inputs
  mind::rdrand rng;
  auto rn = rng(size);
  // Checking outputs
  EXPECT_EQ(exp_size, rn.size());
  if( size==0 )
    EXPECT_EQ(exp_rn, rn);
  else
    EXPECT_NE(exp_rn, rn);
}

// Input values
auto dblk_functor_len_test_values = testing::Values(
  mind::u(0),
  mind::u(10)
);

INSTANTIATE_TEST_SUITE_P(
  dblk_functor_len_test,
  dblk_functor_len_test,
  dblk_functor_len_test_values
);
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
class void_functor_in_len_test : public testing::TestWithParam<mind::u> {};

TEST_P(void_functor_in_len_test, void_functor_in_len) {
  // Inputs
  auto size = GetParam();
  mind::dblk rn(size);
  // Expectations
  auto exp_size = size;
  mind::dblk exp_rn(size);
  // Providing inputs
  mind::rdrand rng;
  rng(rn.begin(), size);
  // Checking outputs
  EXPECT_EQ(exp_size, rn.size());
  if( size==0 )
    EXPECT_EQ(exp_rn, rn);
  else
    EXPECT_NE(exp_rn, rn);
}

// Input values
auto void_functor_in_len_test_values = testing::Values(
  mind::u(0),
  mind::u(10)
);

INSTANTIATE_TEST_SUITE_P(
  void_functor_in_len_test,
  void_functor_in_len_test,
  void_functor_in_len_test_values
);
////////////////////////////////////////////////////////////////////////////////
