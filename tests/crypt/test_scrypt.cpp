#include <string>
#include "gtest/gtest.h"
#include "mind/crypt/scrypt.h"

// Type wrapper
template <
  mind::u Size,
  mind::u Exp_size,
  mind::sblk<Size> Salt,
  mind::sblk<Size> Exp_hv>
class scrypt_sblk_functor_in_len_salt_test_wrapper {
public:
  static constexpr auto size = Size;
  static constexpr auto exp_size = Exp_size;
  static constexpr auto salt = Salt;
  static constexpr auto exp_hv = Exp_hv;
};

template <typename Input_type>
class scrypt_sblk_functor_in_len_salt_test : public testing::Test {};
TYPED_TEST_SUITE_P(scrypt_sblk_functor_in_len_salt_test);

TYPED_TEST_P(
  scrypt_sblk_functor_in_len_salt_test,
  scrypt_sblk_functor_in_len_salt
) {
  // Inputs
  constexpr auto size = TypeParam::size;
  std::string data = "The Fox and the Grapes";
  auto datav = mind::dblk(data.begin(), data.end());
  constexpr auto salt = TypeParam::salt;
  // Expectations
  constexpr auto exp_size = TypeParam::exp_size;
  constexpr auto exp_hv = TypeParam::exp_hv;
  // Providing inputs
  mind::scrypt<size> h;
  auto hv = h(datav.begin(), datav.size(), salt);
  // Checking outputs
  EXPECT_EQ(exp_size, hv.size());
  EXPECT_EQ(exp_hv, exp_hv);
}

REGISTER_TYPED_TEST_SUITE_P(
  scrypt_sblk_functor_in_len_salt_test,
  scrypt_sblk_functor_in_len_salt
);

// Input types
using scrypt_sblk_functor_in_len_salt_test_types =
testing::Types<
  scrypt_sblk_functor_in_len_salt_test_wrapper<
    mind::u(0),
    mind::u(0),
    mind::sblk<mind::u(0)>{},
    mind::sblk<mind::u(0)>{}>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<
    mind::u(16),
    mind::u(16),
    mind::sblk<mind::u(16)>{
      0xe3, 0xe8, 0x62, 0xe5, 0x77, 0xbc, 0xc1, 0x28,
      0x7a, 0xae, 0x01, 0xbb, 0x6d, 0x40, 0xdc, 0x2f
    },
    mind::sblk<mind::u(16)>{
      0xe3, 0x36, 0xdd, 0x66, 0xaf, 0x91, 0xdb, 0x14,
      0x99, 0xc9, 0x6a, 0x74, 0xf6, 0x9d, 0x58, 0x5f
    }
  >
>;

INSTANTIATE_TYPED_TEST_SUITE_P(
  scrypt_sblk_functor_in_len_salt_instance_test,
  scrypt_sblk_functor_in_len_salt_test,
  scrypt_sblk_functor_in_len_salt_test_types
);
