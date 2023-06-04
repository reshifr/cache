#include <array>
#include <string>
#include <iostream>
#include "mind/types.h"
#include "mind/crypt/kdf.h"
#include "mind/crypt/rand.h"
#include "mind/crypt/osrand.h"
#include "mind/crypt/rdrand.h"
#include "mind/crypt/scrypt.h"
#include "mind/crypt/cipher.h"
#include "mind/crypt/chacha20poly1305.h"
#include "mind/crypt/xchacha20poly1305.h"

using namespace std;

int main(void) {
  mind::rand<16> rand;
  mind::sblk<16> salt = rand();

  std::string msg = "🤪🤪🤪";
  std::string password = "password";
  auto msgv = mind::dblk(msg.begin(), msg.end());
  auto passwordv = mind::dblk(password.begin(), password.end());

  mind::kdf<32> keyg;
  mind::sblk<32> key = keyg(msgv.begin(), msgv.size(), salt);

  cout<<"Key: ";
  for(auto ch : key)
    printf("%02x", ch);
  cout<<endl;

  // mind::cipher<kdf, mind::rdrand> cg(salt);
  // auto enmsgv = cg.enc(passwordv, msgv);

  // cout<<"Cipher: ";
  // for(auto ch : enmsgv)
  //   printf("%02x", ch);
  // cout<<endl;

  // auto demsgv = cg.dec(passwordv, enmsgv);
  // auto demsg = std::string(demsgv.begin(), demsgv.end());
  // cout<<"Message: "<<demsg<<endl;

  return 0;
}
