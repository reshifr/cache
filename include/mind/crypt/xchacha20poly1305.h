#ifndef MIND_CRYPT_XCHACHA20POLY1305_H
#define MIND_CRYPT_XCHACHA20POLY1305_H 1

#include <algorithm>
#include "mind/types.h"
#include "mind/crypt/rand.h"
#include "cryptopp/chachapoly.h"

namespace mind {

/**
 * \brief XChaCha20-Poly1305 configuration
 * Configuration parameters for the XChaCha20-Poly1305 algorithm are:
 * - `IV_LENGTH` (Initialization Vector Length) = 24 bytes
 * - `ADD_LENGTH` (Additional Data Length) = 12 bytes
 * - `KEY_LENGTH` (Key Length) = 32 bytes
 * - `MAC_LENGTH` (Message Authentication Code Length) = 16 bytes
 * - `SALT_LENGTH` (Salt Length) = 16 bytes
 * \note The salt length is not part of the algorithm configuration.
 */
class xchacha20poly1305_config {
public:
  static constexpr auto IV_LENGTH = 24;
  static constexpr auto ADD_LENGTH = 12;
  static constexpr auto KEY_LENGTH = 32;
  static constexpr auto MAC_LENGTH = 16;
  static constexpr auto SALT_LENGTH = 16;
};

/**
 * \brief XChaCha20-Poly1305 cipher
 * \tparam H The hash function used to derive the key from the secret
 * \tparam Rd The random number generator
 */
template <
  template <u L, class Slt> class H,
  template <u L> class Rd=rand>
class xchacha20poly1305 : public xchacha20poly1305_config {
public:
  using blk_t = dblk;
  using slt_t = sblk<SALT_LENGTH>;

  /**
   * \brief Initializes the cipher with a salt
   * \param salt The salt
   */
  xchacha20poly1305(const slt_t& salt) noexcept: m_salt(salt) {};

  /**
   * \brief Encrypts a message with a secret
   * \param sec The secret
   * \param msg The message
   * \return The ciphertext
   * \throws rand_error If the random number generator fails
   */
  blk_t enc(const blk_t& sec, const blk_t& msg) const {
    Rd<IV_LENGTH> ivg;
    Rd<ADD_LENGTH> addg;
    H<KEY_LENGTH, slt_t> keyg(m_salt);
    CryptoPP::XChaCha20Poly1305::Encryption en;

    sblk<IV_LENGTH> iv = ivg();
    sblk<ADD_LENGTH> add = addg();
    sblk<KEY_LENGTH> key = keyg(sec);
    sblk<MAC_LENGTH> mac;
    blk_t enmsg(msg.size());

    en.SetKeyWithIV(key.data(), KEY_LENGTH, iv.data(), IV_LENGTH);
    en.EncryptAndAuthenticate(enmsg.data(), mac.data(), MAC_LENGTH,
      iv.data(), IV_LENGTH, add.data(), ADD_LENGTH, msg.data(), msg.size());
    blk_t cpblk = serialize(enmsg, iv, add, mac);
    return cpblk;
  }

  /**
   * \brief Decrypts a ciphertext with a secret
   * \param sec The secret
   * \param cpblk The ciphertext
   * \return The message
   */
  blk_t dec(const blk_t& sec, const blk_t &cpblk) const noexcept {
    H<KEY_LENGTH, slt_t> keyg(m_salt);
    CryptoPP::XChaCha20Poly1305::Decryption de;

    sblk<IV_LENGTH> iv;
    sblk<ADD_LENGTH> add;
    sblk<MAC_LENGTH> mac;
    sblk<KEY_LENGTH> key = keyg(sec);
    deserialize(cpblk, iv, add, mac);
    constexpr auto metalen = IV_LENGTH+ADD_LENGTH+MAC_LENGTH;
    auto enmsglen = cpblk.size()-metalen;
    blk_t demsg(enmsglen);

    de.SetKeyWithIV(key.data(), KEY_LENGTH, iv.data(), IV_LENGTH);
    de.DecryptAndVerify(demsg.data(), mac.data(), MAC_LENGTH, iv.data(),
      IV_LENGTH, add.data(), ADD_LENGTH, cpblk.data()+metalen, enmsglen);
    return demsg;
  }

private:
  slt_t m_salt;

  /**
   * \brief Serializes a ciphertext
   * \param[in] enmsg The encrypted message
   * \param[in] iv The initialization vector
   * \param[in] add The additional data
   * \param[in] mac The message authentication code
   * \return The serialized ciphertext
   */
  blk_t serialize(
    blk_t& enmsg,
    const sblk<IV_LENGTH>& iv,
    const sblk<ADD_LENGTH>& add,
    const sblk<MAC_LENGTH>& mac
  ) const noexcept {
    blk_t cpblk;
    cpblk.insert(cpblk.end(), iv.begin(), iv.end());
    cpblk.insert(cpblk.end(), add.begin(), add.end());
    cpblk.insert(cpblk.end(), mac.begin(), mac.end());
    cpblk.insert(cpblk.end(), enmsg.begin(), enmsg.end());
    return cpblk;
  }

  /**
   * \brief Deserializes a ciphertext
   * \param[in] cpblk The serialized ciphertext
   * \param[out] iv The initialization vector
   * \param[out] add The additional data
   * \param[out] mac The message authentication code
   */
  void deserialize(
    const blk_t& cpblk,
    sblk<IV_LENGTH>& iv,
    sblk<ADD_LENGTH>& add,
    sblk<MAC_LENGTH>& mac
  ) const noexcept {
    auto ivi = cpblk.begin();
    std::copy_n(ivi, IV_LENGTH, iv.begin());    
    auto addi = ivi+IV_LENGTH;
    std::copy_n(addi, ADD_LENGTH, add.begin());
    auto maci = addi+ADD_LENGTH;
    std::copy_n(maci, MAC_LENGTH, mac.begin());
  }
};

} // namespace mind

#endif // MIND_CRYPT_XCHACHA20POLY1305_H
