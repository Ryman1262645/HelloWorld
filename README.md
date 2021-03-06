# HelloWorld
A project by Josh Reiss and Ryan Neumann

CS389_HW1 Contains our first homework assignment, described here (Reed login required to read): https://moodle.reed.edu/mod/assign/view.php?id=87847

Abstract:
Essentially, when you use your computer your CPU attempts to predict what values you will need and preemptively stores them in the cache which allows for faster access time. In this project we succeed in creating a program that calls values from an increasingly large array in an unpredictable way so that the CPU is unable to precaching the values we call. This allows us to observe accurate access times between values in the L1 cache, L2 cache, L3 cache, and DRAM.


Plots:
Each plot compares the array size used in the program vs the Time per Access on the X and Y axes respectively.  In our experiment each computer had 3 layers of cache (L1, L2, L3) and then DRAM. A sudden increase in the slope of the graph indicates that the current cache was flooded which required the computer to start storing values in the next largest cache and eventually DRAM. 

Josh's Desktop:
In this plot the first noticeable slope increase is at 2^9 KB indicating the program breached the L1 cache when handling an array size of about 512 Kb. The next increase of slope is at 2^11 KB indicating the computer had to move on from the L2 cache to the L3 cache when handling an array size of about 2,048 KB. Finally there is a tremendous upward increase in the slope at 2^14 indicating the L3 cache was flooded with an array size of about 16,384 resulting in calls from DRAM which is significantly slower to access then any of the previous caches.

When compared to Josh's Desktop specs we are relieved to see a similar story.
CPU: AMD Ryzen 1600X
L1: 576 KB
L2: 3,072 KB
L3: 16,384 KB
RAM: 16GB DDR4 at 2400MHz

The cache sizes indicated by the graph are slightly smaller then the actual cache sizes but this is completely reasonable seeing as it is unlikely that the caches were dedicated entirely to our program.



Josh's Laptop:
This has very clear increases in slope similarly to the Desktop. The first slope increase occurs at 2^7 KB suggesting the L1 cache was breached when handling an array of size of about 128 KB. The next slope increase occurs at 2^10 KB suggesting the L2 cache was breached when handling an array size of about 1024 KB. The final slope increase occurs at 2^13 KB suggesting the L3 cache was breached when handling an array size of about 8,192 KB.

Josh's Laptop specs:
CPU: Intel Core i7 4720HQ
L1: 128 KB Data, 128 KB Instruction
L2: 1,024 KB
L3: 6,144 KB
RAM: 8GB DDR3 at 1600MHz

The cache sizes indicated by the graph almost perfectly match the actual cache sizes. The L3 cache size suggested by the graph is larger then the actual cache size but this is because the actual cache size is between 2^12 and 2^13 which is not a size we test, therefore the increase in access time is only recorded after the the L3 cache is flooded by an extra 2,000 KBs.



Ryan's Mac-book:
In this plot the slope increases are more gradual so it's harder to make accurate observations however the first slope increase in the graph could be argued to be around 2^8 KB. This indicates the program breached the L1 cache when handling an array size of about 256 KB. The next slope increase could be argued to occur around 2^10 KB indicating the L2 cache was breached when handling an array size of about 1024 KB. The final increase in slope occurs at 2^12 or 2^13 KB indicating the L3 cache was flooded when handling an array size of about 6000 KB.

Ryan's Macbook Pro specs:
CPU: Intel Core i7 4870HQ
L1: 128 KB Data, 128 KB Instruction
L2: 1,024 KB
L3: 6,144 KB
RAM: 16GB

Once again we are rewarded with a similar story as the cache sizes indicated by the graph closely match the actual cache sizes. I could not confirm the L1 cache size for the Mac-book though it's likely 256 KB. The L2 and L3 caches are very consistent with the graph.

Interestingly, Apple had a more gradual slope increase then Windows suggesting slightly different processes with regard to precaching, despite no significant change in CPU architecture between the 4720HQ and 4870HQ. Neither OS was significantly better in the extremes, but it made a difference in some of the intermediary array sizes.
