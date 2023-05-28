#ifndef MIND_CRYPT_CHACHA20POLY1305_H
#define MIND_CRYPT_CHACHA20POLY1305_H 1

#include <algorithm>

#include "types.h"
#include "crypt/hash.h"
#include "crypt/rand.h"
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
  template <u L, class Slt> class H,
  template <u L> class Rd=rand>
class chacha20poly1305 : public chacha20poly1305_conf {
public:
  chacha20poly1305(const sblk<SALT_LENGTH>& salt): m_salt(salt) {};
  dblk enc(const str& sec, const str& msg) {
    Rd<IV_LENGTH> ivg;
    Rd<ADD_LENGTH> addg;
    H<KEY_LENGTH, sblk<SALT_LENGTH>> keyg(m_salt);
    CryptoPP::ChaCha20Poly1305::Encryption en;

    sblk<IV_LENGTH> iv = ivg();
    sblk<ADD_LENGTH> add = addg();
    sblk<KEY_LENGTH> key = keyg(sec);
    sblk<MAC_LENGTH> mac;
    dblk enmsg(msg.size());

    en.SetKeyWithIV(key.data(), KEY_LENGTH, iv.data(), IV_LENGTH);
    en.EncryptAndAuthenticate(
      enmsg.data(), mac.data(), MAC_LENGTH,
      iv.data(), IV_LENGTH, add.data(), ADD_LENGTH,
      reinterpret_cast<const b*>(msg.data()), msg.size());
    dblk cipblk = serialize(enmsg, iv, add, mac);
    return cipblk;
  }

  str dec(const str& sec, const dblk &cipblk) {
    H<KEY_LENGTH, sblk<SALT_LENGTH>> keyg(m_salt);
    CryptoPP::ChaCha20Poly1305::Decryption de;

    sblk<IV_LENGTH> iv;
    sblk<ADD_LENGTH> add;
    sblk<MAC_LENGTH> mac;
    sblk<KEY_LENGTH> key = keyg(sec);
    deserialize(cipblk, iv, add, mac);
    constexpr auto metalen = IV_LENGTH+ADD_LENGTH+MAC_LENGTH;
    auto enmsglen = cipblk.size()-metalen;
    dblk demsg(enmsglen);

    de.SetKeyWithIV(key.data(), KEY_LENGTH, iv.data(), IV_LENGTH);
    de.DecryptAndVerify(
      demsg.data(), mac.data(), MAC_LENGTH, iv.data(),
      IV_LENGTH, add.data(), ADD_LENGTH, cipblk.data()+metalen, enmsglen);
    str msg(demsg.begin(), demsg.end());
    return msg;
  }

private:
  sblk<SALT_LENGTH> m_salt;

  dblk serialize(
    dblk& enmsg,
    const sblk<IV_LENGTH>& iv,
    const sblk<ADD_LENGTH>& add,
    const sblk<MAC_LENGTH>& mac
  ) {
    dblk cipblk;
    cipblk.insert(cipblk.end(), iv.begin(), iv.end());
    cipblk.insert(cipblk.end(), add.begin(), add.end());
    cipblk.insert(cipblk.end(), mac.begin(), mac.end());
    cipblk.insert(cipblk.end(), enmsg.begin(), enmsg.end());
    return cipblk;
  }

  void deserialize(
    const dblk& cipblk,
    sblk<IV_LENGTH>& iv,
    sblk<ADD_LENGTH>& add,
    sblk<MAC_LENGTH>& mac
  ) {
    auto ivi = cipblk.begin();
    std::copy_n(ivi, IV_LENGTH, iv.begin());    
    auto addi = ivi+IV_LENGTH;
    std::copy_n(addi, ADD_LENGTH, add.begin());
    auto maci = addi+ADD_LENGTH;
    std::copy_n(maci, MAC_LENGTH, mac.begin());
  }
};

} // namespace mind

#endif // MIND_CRYPT_CHACHA20POLY1305_H
