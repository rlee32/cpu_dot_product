// This is a testbed for dot product implementations.
// Main target is memory management.

// Currently, speedup figures converge to lower values after the first few 
// runs.

#include <iostream>
#include <streambuf>
#include <ostream>
#include <cstdlib>

#include "Timer.h"
#include "variant_dot_product.h"

using namespace std;

// A 'vanilla' / 'naive' version that is used for correctness checks.
// The answer is stored in c. 
void naive_dot_product(double* a, double *b, double* c, int size)
{
  for(int i = 0; i < size; ++i)
  {
    c[i] = a[i]*b[i];
  }
}

bool check(double* a, double* b, int size)
{
  for(int i = 0; i < size; ++i)
  {
    if(a[i] != b[i])
    {
      cout << "Check failed ( " << a[i] << " != " << b[i] << " )" << endl;
      return false;
    }
  }
  return true;
}

double random_double()
{
  double MIN = 0;
  double MAX = 10000;
  double normalized = (double)rand() / RAND_MAX;
  return MIN + normalized * (MAX - MIN);
}

void random_initialize(double* a, int size)
{
  for(int i = 0; i < size; ++i) a[i] = random_double();
}

// Copies a to b.
void copy(double* a, double* b, int size)
{
  for(int i = 0; i < size; ++i) b[i] = a[i];
}

int main(int argc, char** argv)
{
  // Size of vectors to dot.
  int size = 16777216;
  // Used for manipulate cache transfers in parallel implementaions.
  int stride = 256;

  // For reproducibility.
  srand(1);

  // Read in parameters.
  if(argc < 2)
  {
    cout << "Parameters: <size> <stride>" << endl;
  }
  else
  {
    size = atoi(argv[1]);
    if(argc > 2) stride = atoi(argv[2]);
    cout << "size: " << size << ", stride: " << stride << endl;
  }
  cout << "Vector length, stride (if applicable): " << size 
    << " (" << size*8.0/1000000.0 << " MB), " << stride << endl;

  // We will use different arrays for the naive and variant implementations
  // to prevent caching.
  double* a = new double[size];
  double* b = new double[size];
  double* c = new double[size];
  
  double* a_variant = new double[size];
  double* b_variant = new double[size];

  random_initialize(a, size);
  random_initialize(b, size);

  copy(a, a_variant, size);
  copy(b, b_variant, size);

  Timer timer;

  timer.start();
  naive_dot_product(a, b, c, size);
  double naive_time = timer.stop();

  timer.start();
  variant_dot_product(a_variant, b_variant, size);
  double variant_time = timer.stop();

  if(check(b_variant, c, size)) cout << "Arrays match!" << endl;

  cout << "Naive time:\t" << naive_time << " s" << endl;
  cout << "Variant time:\t" << variant_time << " s" << endl;
  cout << "Speedup:\t" << naive_time / variant_time << endl;

  delete[] a;
  delete[] b;
  delete[] c;
  delete[] a_variant;
  delete[] b_variant;

  return EXIT_SUCCESS;
}