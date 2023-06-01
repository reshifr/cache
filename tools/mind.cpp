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
using fdk = mind::hash<L, Slt, mind::scrypt<L, Slt>>;

int main(void) {
  mind::rand<16> rand;
  mind::sblk<16> salt = rand();
  mind::hash<32, mind::sblk<16>> hg(salt);

  mind::str msg = "🤪🤪🤪";
  mind::str password = "password";
  auto msgv = mind::dblk(msg.begin(), msg.end());
  auto passwordv = mind::dblk(password.begin(), password.end());

  mind::sblk<32> hashval = hg(msgv);
  mind::cipher<fdk, mind::rdrand> cg(salt);

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
  auto demsg = mind::str(demsgv.begin(), demsgv.end());
  cout<<"Message: "<<demsg<<endl;

  return 0;
}
