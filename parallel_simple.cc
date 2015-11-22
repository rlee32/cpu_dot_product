#include <iostream>
#include <omp.h>

#include "variant_dot_product.h"

// The answer is stored in b.
void variant_dot_product(double* a, double *b, int size)
{
  #pragma omp parallel for
  for(int i = 0; i < size; ++i)
  {
    // if(i == 0) std::cout << omp_get_max_threads() << std::endl;
    b[i] *= a[i];
  }
}