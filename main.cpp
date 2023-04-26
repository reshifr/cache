#include <crypt/csprand.hpp>
#include <crypt/hash.hpp>
#include <iostream>
#include <vector>

#include <crypt/cipher.hpp>

int main(int argc, char **argv) {
  // csprand<256> rand;
  // auto salt = rand();
  // hash<128, decltype(salt)> h(salt);

  // auto m = h("halo");
  // for (auto elm : m) {
  //   printf("%02x", elm);
  // }

  // std::cout << std::endl;

  csprand<64> rand;
  auto salt = rand();
  cipher<decltype(salt)> ciphergen(salt);

  auto en = ciphergen.encrypt("pwd", "INI RAHASIA 😀");
  for (auto elm : en) {
    printf("%02x", elm);
  }

  auto de = ciphergen.decrypt("pwd", en);

  std::cout << std::endl << "Message = " << de << std::endl;

  // std::cout << " = " << std::size(m) << std::endl;

  return 0;
}