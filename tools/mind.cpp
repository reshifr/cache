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
