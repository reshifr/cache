#include "gtest/gtest.h"
#include "mind/crypt/rdrand.h"

// Type wrapper
template <
  mind::u Size,
  mind::sblk<Size> Exp_rn>
class rdrand_sblk_functor_test_wrapper {
public:
  static constexpr auto size = Size;
  static constexpr auto exp_rn = Exp_rn;
};

template <typename Input_type>
class rdrand_sblk_functor_test : public testing::Test {};
TYPED_TEST_SUITE_P(rdrand_sblk_functor_test);

/**
 * \brief Test `rdrand<L>::operator()`
 */
TYPED_TEST_P(rdrand_sblk_functor_test, rdrand_sblk_functor) {
  // Inputs
  constexpr auto size = TypeParam::size;
  // Expectations
  constexpr auto exp_size = size;
  constexpr auto exp_rn = TypeParam::exp_rn;
  // Providing inputs
  mind::rdrand<size> rng;
  auto rn = rng();
  // Checking outputs
  EXPECT_EQ(exp_size, rn.size());
  EXPECT_NE(exp_rn, rn);
}

REGISTER_TYPED_TEST_SUITE_P(
  rdrand_sblk_functor_test,
  rdrand_sblk_functor
);

// Input types
using rdrand_sblk_functor_test_types =
testing::Types<
  rdrand_sblk_functor_test_wrapper<
    mind::u(1),
    mind::sblk<mind::u(1)>{}
  >,
  rdrand_sblk_functor_test_wrapper<
    mind::u(16),
    mind::sblk<mind::u(16)>{
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }
  >
>;

INSTANTIATE_TYPED_TEST_SUITE_P(
  rdrand_sblk_functor_instance_test,
  rdrand_sblk_functor_test,
  rdrand_sblk_functor_test_types
);

// Value wrapper
class rdrand_dblk_functor_len_test_wrapper {
public:
  mind::u size;
  mind::dblk exp_rn;
};

class rdrand_dblk_functor_len_test :
  public testing::TestWithParam<rdrand_dblk_functor_len_test_wrapper> {};

/**
 * \brief Test `rdrand<0>::operator(len)`
 */
TEST_P(rdrand_dblk_functor_len_test, rdrand_dblk_functor_len) {
  // Inputs
  auto size = GetParam().size;
  // Expectations
  auto exp_size = size;
  auto exp_rn = GetParam().exp_rn;
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
auto rdrand_dblk_functor_len_test_values =
testing::Values(
  rdrand_dblk_functor_len_test_wrapper{
    mind::u(0),
    mind::dblk{}
  },
  rdrand_dblk_functor_len_test_wrapper{
    mind::u(16),
    mind::dblk{
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }
  }
);

INSTANTIATE_TEST_SUITE_P(
  rdrand_dblk_functor_len_test,
  rdrand_dblk_functor_len_test,
  rdrand_dblk_functor_len_test_values
);

// Value wrapper
class rdrand_void_functor_in_len_test_wrapper {
public:
  mind::u size;
  mind::dblk exp_rn;
};

class rdrand_void_functor_in_len_test :
  public testing::TestWithParam<rdrand_void_functor_in_len_test_wrapper> {};

/**
 * \brief Test `rdrand<0>::operator()(in, len)`
 */
TEST_P(rdrand_void_functor_in_len_test, rdrand_void_functor_in_len) {
  // Inputs
  auto size = GetParam().size;
  mind::dblk rn(size);
  // Expectations
  auto exp_size = size;
  auto exp_rn = GetParam().exp_rn;
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
auto rdrand_void_functor_in_len_test_values = testing::Values(
  rdrand_void_functor_in_len_test_wrapper{
    mind::u(0),
    mind::dblk{}
  },
  rdrand_void_functor_in_len_test_wrapper{
    mind::u(16),
    mind::dblk{
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }
  }
);

INSTANTIATE_TEST_SUITE_P(
  rdrand_void_functor_in_len_test,
  rdrand_void_functor_in_len_test,
  rdrand_void_functor_in_len_test_values
);
