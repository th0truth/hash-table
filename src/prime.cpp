#include <cmath>
#include "prime.h"

/*
 * Return whether x is prime or not
 *
 * Returns:
 *   1  - prime
 *   0  - not prime
 *   -1 - undefined (i.e. x < 2)
 */
int32_t is_prime(const int32_t x)
{
  if (x < 2) { return -1; };
  if (x < 4) { return 1; };
  if ((x % 2) == 0) { return 0; };
  for (int i = 3; i <= floor(sqrt((double)x)); i += 2) {
    if ((x % i) == 0) {
      return 0;
    }
  }
  return 1;
}
