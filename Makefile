CC = g++
CCFLAGS = -std=c++11 -O3 -fopenmp -fargument-noalias-global
LDFLAGS =

all: simple psimple

# Compile all source files.
# %.o: %.cc
# 	$(CC) $(CCFLAGS) -o $@ -c $<

simple: driver.cc simple.cc
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)

psimple: driver.cc parallel_simple.cc
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)

clean: 
	rm -f *.o *~ simple psimple
