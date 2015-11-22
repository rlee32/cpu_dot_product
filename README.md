# cpu_dot_product
CPU performance tests on simple dot product of two vectors.

Since we expect dot products to be memory-bound, we will experiment here with 
memory arrangements and memory profiling tools.

We have a default, 'naive' version that is used for correctness checks. All 
other performance versions are in-place.

Variants (all in-place):  
1. Simple in-place  
2. Parallel strided  
3. NUMA-aware  

Profiling tools:  
1. LIKWID  
2. ScaAnalyzer  