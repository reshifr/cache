#include "gtest/gtest.h"
#include "mind/crypt/osrand.h"

// Type wrapper
template <
  mind::u Size,
  mind::sblk<Size> Exp_rn>
class osrand_sblk_functor_test_wrapper {
public:
  static constexpr auto size = Size;
  static constexpr auto exp_rn = Exp_rn;
};

template <typename Input_type>
class osrand_sblk_functor_test : public testing::Test {};
TYPED_TEST_SUITE_P(osrand_sblk_functor_test);

/**
 * \brief Test `osrand<L>::operator()`
 */
TYPED_TEST_P(osrand_sblk_functor_test, osrand_sblk_functor) {
  // Inputs
  constexpr auto size = TypeParam::size;
  // Expectations
  constexpr auto exp_size = size;
  constexpr auto exp_rn = TypeParam::exp_rn;
  // Providing inputs
  mind::osrand<size> rng;
  auto rn = rng();
  // Checking outputs
  EXPECT_EQ(exp_size, rn.size());
  EXPECT_NE(exp_rn, rn);
}

REGISTER_TYPED_TEST_SUITE_P(
  osrand_sblk_functor_test,
  osrand_sblk_functor
);

// Input types
using osrand_sblk_functor_test_types =
testing::Types<
  osrand_sblk_functor_test_wrapper<
    mind::u(1),
    mind::sblk<mind::u(1)>{}
  >,
  osrand_sblk_functor_test_wrapper<
    mind::u(16),
    mind::sblk<mind::u(16)>{
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }
  >
>;

INSTANTIATE_TYPED_TEST_SUITE_P(
  osrand_sblk_functor_instance_test,
  osrand_sblk_functor_test,
  osrand_sblk_functor_test_types
);

// Value wrapper
class osrand_dblk_functor_len_test_wrapper {
public:
  mind::u size;
  mind::dblk exp_rn;
};

class osrand_dblk_functor_len_test :
  public testing::TestWithParam<osrand_dblk_functor_len_test_wrapper> {};

/**
 * \brief Test `osrand<0>::operator(len)`
 */
TEST_P(osrand_dblk_functor_len_test, osrand_dblk_functor_len) {
  // Inputs
  auto size = GetParam().size;
  // Expectations
  auto exp_size = size;
  auto exp_rn = GetParam().exp_rn;
  // Providing inputs
  mind::osrand rng;
  auto rn = rng(size);
  // Checking outputs
  EXPECT_EQ(exp_size, rn.size());
  if( size==0 )
    EXPECT_EQ(exp_rn, rn);
  else
    EXPECT_NE(exp_rn, rn);
}

// Input values
auto osrand_dblk_functor_len_test_values =
testing::Values(
  osrand_dblk_functor_len_test_wrapper{
    mind::u(0),
    mind::dblk{}
  },
  osrand_dblk_functor_len_test_wrapper{
    mind::u(16),
    mind::dblk{
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }
  }
);

INSTANTIATE_TEST_SUITE_P(
  osrand_dblk_functor_len_test,
  osrand_dblk_functor_len_test,
  osrand_dblk_functor_len_test_values
);

// Value wrapper
class osrand_void_functor_in_len_test_wrapper {
public:
  mind::u size;
  mind::dblk exp_rn;
};

class osrand_void_functor_in_len_test :
  public testing::TestWithParam<osrand_void_functor_in_len_test_wrapper> {};

/**
 * \brief Test `osrand<0>::operator()(in, len)`
 */
TEST_P(osrand_void_functor_in_len_test, osrand_void_functor_in_len) {
  // Inputs
  auto size = GetParam().size;
  mind::dblk rn(size);
  // Expectations
  auto exp_size = size;
  auto exp_rn = GetParam().exp_rn;
  // Providing inputs
  mind::osrand rng;
  rng(rn.begin(), size);
  // Checking outputs
  EXPECT_EQ(exp_size, rn.size());
  if( size==0 )
    EXPECT_EQ(exp_rn, rn);
  else
    EXPECT_NE(exp_rn, rn);
}

// Input values
auto osrand_void_functor_in_len_test_values = testing::Values(
  osrand_void_functor_in_len_test_wrapper{
    mind::u(0),
    mind::dblk{}
  },
  osrand_void_functor_in_len_test_wrapper{
    mind::u(16),
    mind::dblk{
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    }
  }
);

INSTANTIATE_TEST_SUITE_P(
  osrand_void_functor_in_len_test,
  osrand_void_functor_in_len_test,
  osrand_void_functor_in_len_test_values
);
