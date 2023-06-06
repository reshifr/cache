#ifndef MIND_CRYPT_RAND_TYPES_H
#define MIND_CRYPT_RAND_TYPES_H 1

#include "mind/mind.h"

namespace mind {

/**
 * \brief Random number generator error
 */
class rand_error : public error {
public:
  static constexpr auto RAND_FAILED =
    "Mind Error: Failed to generate random number.";
  const char* what(void) const noexcept override { return RAND_FAILED; }
};

} /* namespace mind */

#endif /* MIND_CRYPT_RAND_TYPES_H */
