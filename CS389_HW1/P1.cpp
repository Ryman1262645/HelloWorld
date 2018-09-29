#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <cmath>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iostream>
#include <ratio>
#include <algorithm>
using namespace std;

int8_t * generate_random_list(int64_t size, int16_t bound)
{
	int8_t* list;
	list = new int8_t [size];
	if(!list){/*death*/}

	//srand(size);
	for(int64_t i = 0; i < size; i++)
	{
		list[i] = (rand() % bound);
	}
	return list;
}

bool isPrime(int x)
{
	if(x < 2) {return false;}
	else if(x == 2) {return true;}
	else if(x % 2 == 0) {return false;}
    
    for(int i = 3, max = sqrt(x); i < max; i += 2)
    {
        if(x % i == 0) {return false;}
    }
    return true;
}

//main takes argumeents size, iters, and loop_iters
//size is x in 2^x
//iters is the number of times the entire buffer will be strided through mod a particular prime
//loop_iters is the number of times the a new prime will be picked and the iters loop will be re-run.
//basically, the "iters" loop is nested in the "loop_iters" loop. so the number of actual iterations is (loop_iters * iters)
//i know that's a little overcomplicated, but I thought it would be interesting to see what different values for each iters variable would cause in runtime
int main (int argc, char **argv)
{
	//open file
	ofstream outfile;
	outfile.open("output.txt", std::ios_base::app);
	//take arguments
	int64_t size = atoi(argv[1]);
	size = pow(2,size);
	int64_t iters = atoi(argv[2]);
	int64_t loop_iters = atoi(argv[3]);
	//generate an array of 2^(N) random bytes
	int8_t *arrboy = generate_random_list(size, 256);

    //generate an array of random indexes==========================================================================
    //creating array of size 255
    int randarraysize = 255;
    int* shuffledindexarray;
    shuffledindexarray = (int*) malloc(sizeof(int) * randarraysize);
    if (!shuffledindexarray)
    {
        std::cout<< "There was an error allocating memory for this array" << std::endl;
        exit(-1);
    }
    //filling it with values 0 through 255
    for(int i = 0; i<randarraysize; i++)
    {
        shuffledindexarray[i] = i;
    }
    //shuffling the array
    std::random_shuffle ( shuffledindexarray, shuffledindexarray + randarraysize );
    //I free the array at the end of main ==============================================================================

	//LOOP
	double loop_avg = 0;
	for(int64_t l = 0; l < loop_iters; l++)
	{
		//randomly generate prime number greater than N
		int64_t stride = 4;
		int64_t reader;
		while (!isPrime(stride))
		{
			stride = rand();
			if (stride < 0) {stride = -1 * stride;}
			stride = stride % size;
		}
		printf("stride: %lld\n",stride);
		//read all the bytes once // THIS RESETS CAPS LOCK
		for(int64_t r = 0; r < size; r++) {reader = reader + arrboy[r];}
		int64_t saved_reader = reader;

		//start the clock
		struct timespec start, stop;
		clock_gettime(CLOCK_MONOTONIC_RAW, &start); //something something clock monotonic

		//read all the bytes (iters) times -- read them mod a prime number so that we can foil AMD/Intel
		for(int64_t ov = 0; ov < iters; ov++)
		{
			for(int64_t it = 0; it < size; it++)
			{
				reader = reader + arrboy[((it*stride) % size)];
				//printf("%d  ", reader[it]);
			}
		}
		//stop the clock
		clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
		long ss = (stop.tv_sec - start.tv_sec);
		long ns = (stop.tv_nsec - start.tv_nsec);
		cout << ss << endl;
		cout << ns << endl;
		cout << saved_reader << endl;
		cout << reader << endl;
		double time_elapsed = ((double)ss * 1000000000) + (double)ns;//something something clock monotonic

		//shuffle all of the bytes around, somehow?? -- optional step

		//compute N/time elapsed
		double avg_time = time_elapsed/(size * iters);
		//print it!
		printf("How many nanoseconds per access was it?\nWell, it was...... %fns/access!!\n", avg_time);
		//save the result to a json, somehow?? -- optional step
		cout << "Time: " << avg_time << "ns/access\tN: " << size << "\tIters: " << iters << "\tLoop_iters:" << loop_iters << "\n";
		//outfile << avg_time << "," << iters << "," << size << "," << loop_iters << "\n";
		loop_avg = loop_avg + avg_time;
	}
	loop_avg = loop_avg / loop_iters;
	outfile << loop_avg << "," << iters << "," << size << "," << loop_iters << "\n";
	delete [] arrboy;
    free(shuffledindexarray);
    outfile.close();
}
