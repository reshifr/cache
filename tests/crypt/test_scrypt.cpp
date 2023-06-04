#include "gtest/gtest.h"
#include "mind/crypt/scrypt.h"

/**
 * \brief Type wrapper
 * \note ID 0: len == 0 && empty data && empty salt
 *       ID 1: len == 0 && non-empty data && non-empty salt
 *       ID 2: len == 16 && empty data && empty salt
 *       ID 3: len == 16 && non-empty data && non-empty salt
 */
template <int id, mind::u len, mind::u salt_len>
class scrypt_sblk_functor_in_len_salt_test_wrapper {
  static_assert(
    (id==0 && len==0 && salt_len==0 ) ||
    (id==1 && len==0 && salt_len==16) ||
    (id==2 && len==16 && salt_len==0) ||
    (id==3 && len==16 && salt_len==16)
  );
public:
  static constexpr auto L = len;
  static constexpr auto Sl = salt_len;

  static const mind::dblk data(void) noexcept {
    std::string data;
    if constexpr( id==0 )
      data = "";
    else if constexpr( id==1 )
      data = "The quick brown fox jumps over the lazy dog";
    else if constexpr( id==2 )
      data = "";
    else if constexpr( id==3 )
      data = "The quick brown fox jumps over the lazy dog";
    return mind::dblk(data.begin(), data.end());
  }

  static constexpr mind::sblk<Sl> salt(void) noexcept {
    mind::sblk<Sl> salt;
    if constexpr( id==0 )
      salt = mind::sblk<Sl>{};
    else if constexpr( id==1 )
      salt = mind::sblk<Sl>{
        0x5c, 0x6a, 0x18, 0x9f, 0x35, 0xe6, 0x16, 0x12,
        0x0c, 0x8b, 0x18, 0x5e, 0xda, 0x07, 0x01, 0xd8
      };
    else if constexpr( id==2 )
      salt = mind::sblk<Sl>{};
    else if constexpr( id==3 )
      salt = mind::sblk<Sl>{
        0x63, 0x62, 0x62, 0x65, 0x33, 0x63, 0x32, 0x31,
        0x39, 0x36, 0x66, 0x38, 0x30, 0x65, 0x63, 0x34
      };
    return salt;
  }

  static constexpr mind::sblk<L> exp_hv(void) noexcept {
    mind::sblk<L> exp_hv;
    if constexpr( id==0 )
      exp_hv = mind::sblk<L>{};
    else if constexpr( id==1 )
      exp_hv = mind::sblk<L>{};
    else if constexpr( id==2 )
      exp_hv = mind::sblk<L>{
        0x53, 0xb6, 0x59, 0xba, 0xff, 0x26, 0x9e, 0xad,
        0xd3, 0xee, 0xf2, 0xeb, 0xb3, 0x2f, 0x49, 0x26
      };
    else if constexpr( id==3 )
      exp_hv = mind::sblk<L>{
        0xfa, 0x6b, 0x9a, 0x52, 0x98, 0x4c, 0x46, 0x16,
        0x06, 0x7c, 0x2c, 0x72, 0x2d, 0x2d, 0x89, 0x04
      };
    return exp_hv;
  }
};

template <typename in_type>
class scrypt_sblk_functor_in_len_salt_test : public testing::Test {};
TYPED_TEST_SUITE_P(scrypt_sblk_functor_in_len_salt_test);

/**
 * \brief Test `scrypt<L>::operator()`
 */
TYPED_TEST_P(
  scrypt_sblk_functor_in_len_salt_test,
  scrypt_sblk_functor_in_len_salt
) {
  /**
   * \brief Inputs
   */
  const auto data = TypeParam::data();
  constexpr auto salt = TypeParam::salt();

  /**
   * \brief Expectations
   */
  constexpr auto exp_hv = TypeParam::exp_hv();

  /**
   * \brief Providing inputs
   */
  mind::scrypt<TypeParam::L> h;
  auto hv = h(data.begin(), data.size(), salt);

  /**
   * \brief Checking outputs
   */
  EXPECT_EQ(exp_hv, hv);
}

REGISTER_TYPED_TEST_SUITE_P(
  scrypt_sblk_functor_in_len_salt_test,
  scrypt_sblk_functor_in_len_salt
);

/**
 * \brief Input types
 */
using scrypt_sblk_functor_in_len_salt_test_types = testing::Types<
  scrypt_sblk_functor_in_len_salt_test_wrapper<0, 0, 0>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<1, 0, 16>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<2, 16, 0>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<3, 16, 16>>;

INSTANTIATE_TYPED_TEST_SUITE_P(
  scrypt_sblk_functor_in_len_salt_instance_test,
  scrypt_sblk_functor_in_len_salt_test,
  scrypt_sblk_functor_in_len_salt_test_types
);
