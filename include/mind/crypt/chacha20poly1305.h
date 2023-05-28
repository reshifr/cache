#ifndef MIND_CRYPT_CHACHA20POLY1305_H
#define MIND_CRYPT_CHACHA20POLY1305_H 1

#include <string>
#include <iterator>
#include <algorithm>

#include "types.h"
#include "crypt/rand.h"
#include "crypt/scrypt.h"
#include "cryptopp/chachapoly.h"

namespace mind {

class chacha20poly1305_conf {
public:
  static constexpr auto IV_LENGTH = 12;
  static constexpr auto ADD_LENGTH = 12;
  static constexpr auto KEY_LENGTH = 32;
  static constexpr auto MAC_LENGTH = 16;
  static constexpr auto SALT_LENGTH = 16;
};

template <
  class H=scrypt,
  template <u L> class Rd=rand>
class chacha20poly1305 : public chacha20poly1305_conf {
public:
  chacha20poly1305(const sblk<SALT_LENGTH>& salt): m_salt(salt) {};
  dblk enc(const str& secret, const str& message) {
    Rd<IV_LENGTH> ivg;
    Rd<ADD_LENGTH> addg;
    H<KEY_LENGTH, sblk<SALT_LENGTH>> keyg(m_salt);
    CryptoPP::ChaCha20Poly1305::Encryption en;

    sblk<IV_LENGTH> iv = ivg();
    sblk<ADD_LENGTH> add = addg();
    sblk<KEY_LENGTH> key = keyg(secret);
    sblk<MAC_LENGTH> mac;
    dblk cipher(message.size());

    en.SetKeyWithIV(key.data(), KEY_LENGTH, iv.data(), IV_LENGTH);
    en.EncryptAndAuthenticate(
      cipher.data(), mac.data(), MAC_LENGTH,
      iv.data(), IV_LENGTH, add.data(), ADD_LENGTH,
      reinterpret_cast<const b*>(message.data()), message.size());

    dblk mcipher = serialize(cipher, iv, add, mac);
    return mcipher;
  }

//   std::string decrypt(const std::string &secret,
//                       const dynamic_block &cipherblock) {
//     hash<KEY_LENGTH, Salt> keygen(m_salt);
//     CryptoPP::ChaCha20Poly1305::Decryption dec;

//     static_block<IV_LENGTH> iv;
//     static_block<ADD_LENGTH> add;
//     static_block<KEY_LENGTH> key = keygen(secret);
//     static_block<MAC_LENGTH> mac;

//     auto ciphertext_length =
//         std::size(cipherblock) - MAC_LENGTH - IV_LENGTH - ADD_LENGTH;
//     dynamic_block ciphertext(ciphertext_length);
//     deserialize(mac, iv, add, ciphertext, cipherblock);

//     dec.SetKeyWithIV(std::data(key), KEY_LENGTH, std::data(iv), IV_LENGTH);
//     dec.DecryptAndVerify(std::data(ciphertext), std::data(mac), MAC_LENGTH,
//                          std::data(iv), IV_LENGTH, std::data(add), ADD_LENGTH,
//                          reinterpret_cast<const byte *>(std::data(ciphertext)),
//                          ciphertext_length);

//     std::string message(std::begin(ciphertext), std::end(ciphertext));
//     return message;
//   }

private:
  sblk<SALT_LENGTH> m_salt;

  dblk serialize(
    const dblk& cipher,
    const sblk<IV_LENGTH>& iv,
    const sblk<ADD_LENGTH>& add,
    const sblk<MAC_LENGTH>& mac
  ) {
    dblk mcipher;
    // std::copy_n(std::begin(mac), MAC_LENGTH, std::back_inserter(block));
    // std::copy_n(std::begin(iv), IV_LENGTH, std::back_inserter(block));
    // std::copy_n(std::begin(add), ADD_LENGTH, std::back_inserter(block));
    // std::copy_n(std::begin(ciphertext), std::size(ciphertext),
    //             std::back_inserter(block));

    return mcipher;
  }

//   void deserialize(static_block<MAC_LENGTH> &mac, static_block<IV_LENGTH> &iv,
//                    static_block<ADD_LENGTH> &add, dynamic_block &ciphertext,
//                    const dynamic_block &cipherblock) {
//     auto mac_begin = std::begin(cipherblock);
//     std::copy_n(mac_begin, MAC_LENGTH, std::begin(mac));
//     auto iv_begin = std::begin(cipherblock) + MAC_LENGTH;
//     std::copy_n(iv_begin, IV_LENGTH, std::begin(iv));
//     auto add_begin = iv_begin + IV_LENGTH;
//     std::copy_n(add_begin, ADD_LENGTH, std::begin(add));
//     auto ciphertext_begin = add_begin + ADD_LENGTH;
//     std::copy_n(ciphertext_begin, std::size(ciphertext),
//                 std::begin(ciphertext));
//   }
};


} // namespace mind

#endif // MIND_CRYPT_CHACHA20POLY1305_H
