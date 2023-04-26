#include <algorithm>
#include <iterator>
#ifndef CRYPT_CHACHA20POLY1305_HPP
#define CRYPT_CHACHA20POLY1305_HPP 1

#include <crypt/crypt.hpp>
#include <crypt/csprand.hpp>
#include <crypt/hash.hpp>
#include <cryptopp/chachapoly.h>
#include <string>

template <class Salt> class chacha20poly1305 {
public:
  static constexpr auto KEY_LENGTH = 32;
  static constexpr auto MAC_LENGTH = 16;
  static constexpr auto IV_LENGTH = 12;
  static constexpr auto ADD_LENGTH = 12;

  chacha20poly1305(const Salt &salt) : m_salt(salt){};
  dynamic_block encrypt(const std::string &secret, const std::string &message) {
    csprand<IV_LENGTH> ivgen;
    csprand<ADD_LENGTH> addgen;
    hash<KEY_LENGTH, Salt> keygen(m_salt);
    CryptoPP::ChaCha20Poly1305::Encryption enc;

    static_block<IV_LENGTH> iv = ivgen();
    static_block<ADD_LENGTH> add = addgen();
    static_block<KEY_LENGTH> key = keygen(secret);
    static_block<MAC_LENGTH> mac;
    dynamic_block ciphertext(std::size(message));

    enc.SetKeyWithIV(std::data(key), KEY_LENGTH, std::data(iv), IV_LENGTH);
    enc.EncryptAndAuthenticate(
        std::data(ciphertext), std::data(mac), MAC_LENGTH, std::data(iv),
        IV_LENGTH, std::data(add), ADD_LENGTH,
        reinterpret_cast<const byte *>(std::data(message)), std::size(message));

    dynamic_block block = serialize(mac, iv, add, ciphertext);
    return block;
  }

  std::string decrypt(const std::string &secret,
                      const dynamic_block &cipherblock) {
    hash<KEY_LENGTH, Salt> keygen(m_salt);
    CryptoPP::ChaCha20Poly1305::Decryption dec;

    static_block<IV_LENGTH> iv;
    static_block<ADD_LENGTH> add;
    static_block<KEY_LENGTH> key = keygen(secret);
    static_block<MAC_LENGTH> mac;

    auto ciphertext_length =
        std::size(cipherblock) - MAC_LENGTH - IV_LENGTH - ADD_LENGTH;
    dynamic_block ciphertext(ciphertext_length);
    deserialize(mac, iv, add, ciphertext, cipherblock);

    dec.SetKeyWithIV(std::data(key), KEY_LENGTH, std::data(iv), IV_LENGTH);
    dec.DecryptAndVerify(std::data(ciphertext), std::data(mac), MAC_LENGTH,
                         std::data(iv), IV_LENGTH, std::data(add), ADD_LENGTH,
                         reinterpret_cast<const byte *>(std::data(ciphertext)),
                         ciphertext_length);

    std::string message(std::begin(ciphertext), std::end(ciphertext));
    return message;
  }

private:
  Salt m_salt;

  dynamic_block serialize(const static_block<MAC_LENGTH> &mac,
                          const static_block<IV_LENGTH> &iv,
                          const static_block<ADD_LENGTH> &add,
                          const dynamic_block &ciphertext) {
    dynamic_block block;
    std::copy_n(std::begin(mac), MAC_LENGTH, std::back_inserter(block));
    std::copy_n(std::begin(iv), IV_LENGTH, std::back_inserter(block));
    std::copy_n(std::begin(add), ADD_LENGTH, std::back_inserter(block));
    std::copy_n(std::begin(ciphertext), std::size(ciphertext),
                std::back_inserter(block));

    return block;
  }

  void deserialize(static_block<MAC_LENGTH> &mac, static_block<IV_LENGTH> &iv,
                   static_block<ADD_LENGTH> &add, dynamic_block &ciphertext,
                   const dynamic_block &cipherblock) {
    auto mac_begin = std::begin(cipherblock);
    std::copy_n(mac_begin, MAC_LENGTH, std::begin(mac));
    auto iv_begin = std::begin(cipherblock) + MAC_LENGTH;
    std::copy_n(iv_begin, IV_LENGTH, std::begin(iv));
    auto add_begin = iv_begin + IV_LENGTH;
    std::copy_n(add_begin, ADD_LENGTH, std::begin(add));
    auto ciphertext_begin = add_begin + ADD_LENGTH;
    std::copy_n(ciphertext_begin, std::size(ciphertext),
                std::begin(ciphertext));
  }
};

#endif // CRYPT_CHACHA20POLY1305_HPP