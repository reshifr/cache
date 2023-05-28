#include "types.h"
#include "crypt/hash.h"
#include "crypt/rand.h"


#include "crypt/osrand.h"
#include "crypt/rdrand.h"


#include <iostream>
using namespace std;

#include "crypt/chacha20poly1305.h"
#include "crypt/scrypt.h"

template <mind::u L, class Slt>
using fdk = mind::hash<L, Slt, mind::scrypt<L, Slt>>;

int main(void) {
  mind::rand<16> rand;
  mind::sblk<16> salt = rand();
  mind::hash<32, mind::sblk<16>> hg(salt);
  mind::sblk<32> hashval = hg("halo");

  mind::chacha20poly1305<fdk> cg(salt);
  auto enmsg = cg.enc("pwd", "INI RAHASIA 😀");

  // for(auto c : enmsg)
  //   printf("%02x", c);
  // cout<<endl;

  auto demsg = cg.dec("pwd", enmsg);
  cout<<"Message = " <<demsg<<endl;

  return 0;
}
