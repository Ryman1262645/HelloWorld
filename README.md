# HelloWorld
A project by Josh Reiss and Ryan Neumann

CS389_HW1 Contains our first homework assignment, described here (Reed login required to read): https://moodle.reed.edu/mod/assign/view.php?id=87847

Forward:
Essentially, when you use your computer your CPU attempts to predict what values you will need and preemptively stores them in the cache which allows for faster access time. In this program we succeeded in creating a program that called values from increasingly large arrays in an unpredictable way so that the computer was not able to precaching the values we called. This allowed us to observe accurate access times between values in the L1 cache, L2 cache, L3 cache, and DRAM.

Plots:
Each plot compares the array sized used in the program vs the Time per Access on the X and Y axes respectively.  In our experiment each computer had 3 layers of cache (L1, L2, L3) and then DRAM. A sudden increase in the slope of the graph indicates that the current cache was flooded which required the computer to start storing values in the next largest cache and eventually DRAM. 

Josh's Desktop:
In this plot the first noticeable slope increase is at 2^9 KB indicating the program breached the L1 cache when handling an array of size 512 Kb. The next increase of slope is at 2^11 KB indicating the computer had to move on from the L2 cache to the L3 cache when handling an array of 2048 KB. Finally there is a tremendous upward increase in the slope at 2^14 indicating the L3 cache was flooded with an array of size 16,384 resulting in calls from DRAM which is significantly slower to access then any of the previous caches.

When compared to Josh's Desktop Specs we are relieved to see a similar story.
CPU: Ryzen 1600x
L1: 576 KB
L2: 3,072 KB
L3: 16,384 KB
RAM: 16GB at 2400MHz

The cache sizes indicated by the graph are slightly smaller then the actual cache sizes but this is completely reasonable seeing as it is unlikely that the caches were dedicated entirely to our program.
