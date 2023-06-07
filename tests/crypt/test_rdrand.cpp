#include <algorithm>
#include <exception>
#include "gtest/gtest.h"
#include "mind/crypt/rdrand.h"

/**
 * \brief Mock class for `Rng`
 * - `Rng()` success
 * - `Rng::GenerateBlock()` success
 */
class rdrand_rng_mock {
public:
  void GenerateBlock(CryptoPP::byte* output, size_t size)
    { std::fill_n(output, size, 0xff); }
};

/**
 * \brief Mock class for `Rng`
 * - `Rng()` throw
 * - `Rng::GenerateBlock()` success
 */
class rdrand_rng_mock_ctor_throw {
public:
  rdrand_rng_mock_ctor_throw() { throw std::exception(); }
  void GenerateBlock(CryptoPP::byte* output, size_t size) {}
};

/**
 * \brief Mock class for `Rng`
 * - `Rng()` success
 * - `Rng::GenerateBlock()` throw
 */
class rdrand_rng_mock_generate_block_throw {
public:
  void GenerateBlock(CryptoPP::byte* output, size_t size)
    { throw std::exception(); }
};

template <typename input_type>
class rdrand_sblk_functor_test : public testing::Test {};
TYPED_TEST_SUITE_P(rdrand_sblk_functor_test);

/**
 * \brief Test `rdrand<0>::operator()`
 */
TYPED_TEST_P(rdrand_sblk_functor_test, rdrand_sblk_functor) {
  /**
   * \brief Inputs
   */
  mind::u len = 4;
  /**
   * \brief Expectations
   */
  auto exp_rn = mind::dblk{0xff, 0xff, 0xff, 0xff};
  /**
   * \brief Providing inputs and checking outputs
   */
  mind::dblk rn;
  try {
    mind::rdrand<0, TypeParam> rng;
    rn = rng(len);
  } catch(const mind::rdrand_error& e) {
    EXPECT_NE(exp_rn, rn);
    return;
  }
  EXPECT_EQ(exp_rn, rn);
}

REGISTER_TYPED_TEST_SUITE_P(
  rdrand_sblk_functor_test,
  rdrand_sblk_functor
);

/**
 * \brief Input types
 */
using rdrand_sblk_functor_test_types =
testing::Types<
  rdrand_rng_mock,
  rdrand_rng_mock_ctor_throw,
  rdrand_rng_mock_generate_block_throw>;

INSTANTIATE_TYPED_TEST_SUITE_P(
  rdrand_sblk_functor_instance_test,
  rdrand_sblk_functor_test,
  rdrand_sblk_functor_test_types
);


// /**
//  * \brief Test `rdrand<0>::operator(len)`
//  */
// TEST_P(rdrand_dblk_functor_len_test, rdrand_dblk_functor_len) {
//   // Inputs
//   auto size = GetParam().size;
//   // Expectations
//   auto exp_size = size;
//   auto exp_rn = GetParam().exp_rn;
//   // Providing inputs
//   mind::rdrand rng;
//   auto rn = rng(size);
//   // Checking outputs
//   EXPECT_EQ(exp_size, rn.size());
//   if( size==0 )
//     EXPECT_EQ(exp_rn, rn);
//   else
//     EXPECT_NE(exp_rn, rn);
// }

// // Input values
// auto rdrand_dblk_functor_len_test_values =
// testing::Values(
//   rdrand_dblk_functor_len_test_wrapper{
//     mind::u(0),
//     mind::dblk{}
//   },
//   rdrand_dblk_functor_len_test_wrapper{
//     mind::u(16),
//     mind::dblk{
//       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     }
//   }
// );

// INSTANTIATE_TEST_SUITE_P(
//   rdrand_dblk_functor_len_test,
//   rdrand_dblk_functor_len_test,
//   rdrand_dblk_functor_len_test_values
// );

// // Value wrapper
// class rdrand_void_functor_in_len_test_wrapper {
// public:
//   mind::u size;
//   mind::dblk exp_rn;
// };

// class rdrand_void_functor_in_len_test :
//   public testing::TestWithParam<rdrand_void_functor_in_len_test_wrapper> {};

// /**
//  * \brief Test `rdrand<0>::operator()(in, len)`
//  */
// TEST_P(rdrand_void_functor_in_len_test, rdrand_void_functor_in_len) {
//   // Inputs
//   auto size = GetParam().size;
//   mind::dblk rn(size);
//   // Expectations
//   auto exp_size = size;
//   auto exp_rn = GetParam().exp_rn;
//   // Providing inputs
//   mind::rdrand rng;
//   rng(rn.begin(), size);
//   // Checking outputs
//   EXPECT_EQ(exp_size, rn.size());
//   if( size==0 )
//     EXPECT_EQ(exp_rn, rn);
//   else
//     EXPECT_NE(exp_rn, rn);
// }

// // Input values
// auto rdrand_void_functor_in_len_test_values = testing::Values(
//   rdrand_void_functor_in_len_test_wrapper{
//     mind::u(0),
//     mind::dblk{}
//   },
//   rdrand_void_functor_in_len_test_wrapper{
//     mind::u(16),
//     mind::dblk{
//       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//     }
//   }
// );

// INSTANTIATE_TEST_SUITE_P(
//   rdrand_void_functor_in_len_test,
//   rdrand_void_functor_in_len_test,
//   rdrand_void_functor_in_len_test_values
// );
