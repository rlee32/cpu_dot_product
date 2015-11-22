#include "variant_dot_product.h"

// The answer is stored in b.
void variant_dot_product(double* a, double *b, int size)
{
  for(int i = 0; i < size; ++i) b[i] *= a[i];
}