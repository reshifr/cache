#include "types.h"
#include "crypt/hash.h"
#include "crypt/rand.h"


#include "crypt/osrand.h"
#include "crypt/rdrand.h"


#include <iostream>
using namespace std;

// #include "crypt/chacha20poly1305.h"

int main(void) {
  mind::rand<16> rand;
  mind::sblk<16> salt = rand();
  mind::hash<32, mind::sblk<16>> hg(salt);
  mind::sblk<32> hashval = hg("halo", salt);

  
  // mind::chacha20poly1305<mind::rand, mind::hash> cg(salt);

  for(auto elm : hashval)
    printf("%02x", elm);
  cout<<endl;







  
  // // csprand<256> rand;
  // // auto salt = rand();
  // // hash<128, decltype(salt)> h(salt);

  // // auto m = h("halo");
  // // for (auto elm : m) {
  // //   printf("%02x", elm);
  // // }

  // // std::cout << std::endl;

  // csprand<64> rand;
  // auto salt = rand();
  // cipher<decltype(salt)> ciphergen(salt);

  // auto en = ciphergen.encrypt("pwd", "INI RAHASIA 😀");
  // for( auto elm : en ) {
  //   printf("%02x", elm);
  // }

  // auto de = ciphergen.decrypt("pwd", en);

  // std::cout<< std::endl << "Message = " << de << std::endl;

  // std::cout << " = " << std::size(m) << std::endl;

  return 0;
}
