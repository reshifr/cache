#include "gtest/gtest.h"
#include "mind/crypt/scrypt.h"

/**
 * \brief Type wrapper
 * \note ID 0: len == 0 && empty data && empty salt
 *       ID 1: len == 0 && empty data && non-empty salt
 *       ID 2: len == 0 && non-empty data && empty salt
 *       ID 3: len == 0 && non-empty data && non-empty salt
 *       ID 4: len == 8 && empty data && empty salt
 *       ID 5: len == 8 && empty data && non-empty salt
 *       ID 6: len == 8 && non-empty data && empty salt
 *       ID 7: len == 8 && non-empty data && non-empty salt
 */
template <int id, mind::u len, mind::u salt_len>
class scrypt_sblk_functor_in_len_salt_test_wrapper {
  static_assert(
    (id==0 && len==0 && salt_len==0) ||
    (id==1 && len==0 && salt_len==8) ||
    (id==2 && len==0 && salt_len==0) ||
    (id==3 && len==0 && salt_len==8) ||
    (id==4 && len==8 && salt_len==0) ||
    (id==5 && len==8 && salt_len==8) ||
    (id==6 && len==8 && salt_len==0) ||
    (id==7 && len==8 && salt_len==8)
  );
public:
  static constexpr auto L = len;
  static constexpr auto Sll = salt_len;

  static mind::dblk data(void) noexcept {
    std::string data("");
    if constexpr( id==2 || id==3 || id==6 || id==7 )
      data = "The quick brown fox";
    return mind::dblk(data.begin(), data.end());
  }

  static constexpr mind::sblk<Sll> salt(void) noexcept {
    mind::sblk<Sll> salt{};
    if constexpr( id==1 || id==3 || id==5 || id==7 )
      salt = mind::sblk<Sll>{0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68};
    return salt;
  }

  static constexpr mind::sblk<L> exp_hv(void) noexcept {
    mind::sblk<L> exp_hv{};
    if constexpr( id==4 )
      exp_hv = mind::sblk<L>{0x53, 0xb6, 0x59, 0xba, 0xff, 0x26, 0x9e, 0xad};
    else if constexpr( id==5 )
      exp_hv = mind::sblk<L>{0xa5, 0x9f, 0xd4, 0x02, 0x2e, 0xfc, 0x21, 0xbe};
    else if constexpr( id==6 )
      exp_hv = mind::sblk<L>{0xc3, 0x55, 0xb9, 0x04, 0x9c, 0x25, 0x54, 0x6f};
    else if constexpr( id==7 )
      exp_hv = mind::sblk<L>{0x1f, 0x61, 0x26, 0xc9, 0x29, 0xd3, 0xca, 0x6f};
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
  auto data = TypeParam::data();
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
  scrypt_sblk_functor_in_len_salt_test_wrapper<1, 0, 8>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<2, 0, 0>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<3, 0, 8>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<4, 8, 0>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<5, 8, 8>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<6, 8, 0>,
  scrypt_sblk_functor_in_len_salt_test_wrapper<7, 8, 8>>;

INSTANTIATE_TYPED_TEST_SUITE_P(
  scrypt_sblk_functor_in_len_salt_instance_test,
  scrypt_sblk_functor_in_len_salt_test,
  scrypt_sblk_functor_in_len_salt_test_types
);
