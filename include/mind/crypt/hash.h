#ifndef MIND_CRYPT_HASH_H
#define MIND_CRYPT_HASH_H 1

#include "types.h"
#include "crypt/scrypt.h"

namespace mind {

template <u L, class Slt, class H=scrypt<L, Slt>>
class hash {
  static_assert(L>0, "Length must be greater than 0.");
public:
  hash(const Slt& salt): m_salt(salt) {};
  hash& operator()(const Slt& salt) {
    m_salt = salt;
    return *this;
  }

  sblk<L> operator()(const str& data) {
    H hg;
    return hg(data, m_salt);
  }

private:
  Slt m_salt;
};

} // namespace mind

#endif // MIND_CRYPT_HASH_H
