#include <iostream>

#include "types.h"
#include "crypt/hash.h"
#include "crypt/rand.h"
#include "crypt/osrand.h"
#include "crypt/rdrand.h"
#include "crypt/scrypt.h"
#include "crypt/cipher.h"
#include "crypt/chacha20poly1305.h"
#include "crypt/xchacha20poly1305.h"

using namespace std;

template <mind::u L, class Slt>
using fdk = mind::hash<L, Slt, mind::scrypt<L, Slt>>;

int main(void) {
  mind::rand<16> rand;
  mind::sblk<16> salt = rand();
  mind::hash<32, mind::sblk<16>> hg(salt);
  mind::sblk<32> hashval = hg("halo");

  mind::cipher<fdk, mind::rdrand> cg(salt);
  auto enmsg = cg.enc("password", "🤪🤪🤪");

  for(auto ch : enmsg)
    printf("%02x", ch);
  cout<<endl;

  auto demsg = cg.dec("password", enmsg);
  cout<<"Message: " <<demsg<<endl;

  return 0;
}
