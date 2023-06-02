#include <array>
#include <string>
#include <iostream>
#include "mind/types.h"
#include "mind/crypt/hash.h"
#include "mind/crypt/rand.h"
#include "mind/crypt/osrand.h"
#include "mind/crypt/rdrand.h"
#include "mind/crypt/scrypt.h"
#include "mind/crypt/cipher.h"
#include "mind/crypt/chacha20poly1305.h"
#include "mind/crypt/xchacha20poly1305.h"

using namespace std;

template <mind::u L, class Slt>
using kdf = mind::hash<L, Slt, mind::scrypt<L, Slt>>;

int main(void) {
  mind::rand<16> rand;
  mind::rand<16>::blk_t salt = rand();
  mind::hash<48, decltype(salt)> hg(salt);

  std::string msg = "🤪🤪🤪";
  std::string password = "password";
  auto msgv = mind::dblk(msg.begin(), msg.end());
  auto passwordv = mind::dblk(password.begin(), password.end());

  auto hashval = hg(msgv);
  mind::cipher<kdf, mind::rdrand> cg(salt);

  cout<<"Hash: ";
  for(auto ch : hashval)
    printf("%02x", ch);
  cout<<endl;

  auto enmsgv = cg.enc(passwordv, msgv);

  cout<<"Cipher: ";
  for(auto ch : enmsgv)
    printf("%02x", ch);
  cout<<endl;

  auto demsgv = cg.dec(passwordv, enmsgv);
  auto demsg = std::string(demsgv.begin(), demsgv.end());
  cout<<"Message: "<<demsg<<endl;

  return 0;
}
