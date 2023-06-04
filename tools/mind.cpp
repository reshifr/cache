#include <array>
#include <string>
#include <iostream>

#include "mind/mind.h"
#include "mind/crypt/kdf.h"
#include "mind/crypt/pad.h"
#include "mind/crypt/rand.h"
#include "mind/crypt/cipher.h"

using namespace std;

int main(void) {
  mind::rand rand;
  mind::dblk salt = rand(16);

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

  auto padmsgv = msgv;
  mind::pad pd;

  pd.add(padmsgv);
  cout<<"Padded: ";
  for(auto ch : padmsgv)
    printf("%.2x", ch);
  cout<<endl;

  pd.del(padmsgv);
  cout<<"Unpadded: ";
  for(auto ch : padmsgv)
    printf("%c", ch);
  cout<<endl;

  // mind::cipher<mind::kdf> cg(salt);
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
