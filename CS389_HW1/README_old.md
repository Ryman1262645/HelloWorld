/* Josh Reiss and Ryan Neumann, Reed College CS 389, 2018
We essentially test the memory access times for our various caches and our DRAM, then compare the results in a nice graph.
We do this by randomly reading increasingly large arrays full of random bytes.

Let us explain:
When the size of the array is less than the size of L1 Cache, timing accesses to the array should be timing accesses to L1 cache.
When the size of the array is more than the size of L1 Cache, but less than that of L2, timing accesses to the array should be timing accesses to L2 cache.
When the size 			  ... more than ...		... L2 Cache, but less than that of L3 ... 												   ... to L3 cache.
When the size 			  ... more than ... 	... L3 Cache, but less than that of DRAM ...											   ... to DRAM.
So we determine the time/access for each array size, then graph it. You can see huge jumps in time/access whenever we step from one cache to the next.

Full writeup can be found in "plotanalysis.txt".