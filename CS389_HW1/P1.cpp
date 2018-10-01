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
#include <random>
#include <algorithm>
using namespace std;

//generates a list of length size with integers of values between 0 and bound
int8_t * generate_random_list(int64_t size, int16_t bound)
{
	int8_t* list;
	list = new int8_t [size];
	if(!list){/*death*/}

	//srand(size);
	for(int64_t i = 0; i < size; i++)
	{
		list[i] = rand();
		if(list[i] < 0) {list[i] = list[i] * -1;}
		list[i] = list[i]%bound;
	}
	return list;
}

//returns a random integer smaller than sz/10
int64_t make_stride(int64_t sz)
{
	int64_t stride = 0;
	stride = rand();
	if (stride < 0) {stride = -1 * stride;}
	stride = stride % (sz/10); //the 10 is totally arbitrary, we just don't want stride to be huge
	return stride;
}

//main takes argumeents size, iters, and loop_iters
//size is x in 2^x
//iters is the number of times the entire buffer will be strided through mod a particular prime
//loop_iters is the number of times the a new prime will be picked and the iters loop will be re-run.
//basically, the "iters" loop is nested in the "loop_iters" loop. so the number of actual iterations is (loop_iters * iters)
int main (int argc, char **argv)
{

	if(argc != 4) {printf("Wrong # of arguments!! Need buffer size, #iterations, #loop_iterations.\n"); return 0;}

	ofstream outfile; //open file
	outfile.open("output.txt", std::ios_base::app);

	//take arguments
	int64_t size = atoi(argv[1]);
	int64_t iters = atoi(argv[2]);
	int64_t loop_iters = atoi(argv[3]);
	srand(size); //seed random with size
	size = pow(2,size);

	int8_t *arrboy = generate_random_list(size, 256); //generate an array of 2^(N) random bytes

	//LOOP
	double loop_avg = 0;
	for(int64_t l = 0; l < loop_iters; l++)
	{
		int64_t stride = make_stride(size); //randomly generate stride in N
		int64_t reader;

		for(int64_t r = 0; r < size; r++) {reader = reader + arrboy[r];} //read all the bytes once - try to give the cache a chance.
		int64_t saved_reader = reader; //save the sum of all read bytes so compiler doesn't just skip this step
		reader = 0;

		struct timespec start, stop;
		int64_t proportion = (size / 256);
		clock_gettime(CLOCK_MONOTONIC_RAW, &start); //start the clock
		//read all the bytes (iters) times -- read them weirdly so that we can foil AMD/Intel
		for(int64_t ov = 0; ov < iters; ov++)
		{
			for(int64_t it = 0; it < size; it++) //explanation at bottom of file
			{
				reader = reader + arrboy[reader]; //(1)
				if(reader > size) {reader = reader - size;}
				if(reader < 1) {reader = 256;}
				reader = reader * proportion; //(2)
				reader = reader + stride; //(3)
				while(reader > size) {reader = reader - size;}
			}
		}
		clock_gettime(CLOCK_MONOTONIC_RAW, &stop); //stop the clock
		long ss = (stop.tv_sec - start.tv_sec);
		long ns = (stop.tv_nsec - start.tv_nsec);
		cout << saved_reader << endl;
		cout << reader << endl;
		double time_elapsed = ((double)ss * 1000000000) + (double)ns;
		double avg_time = time_elapsed/(size * iters); //compute N/time elapsed
		printf("How many nanoseconds per access was it?\nWell, it was...... %fns/access!!\n", avg_time); //print it!
		cout << "Time: " << avg_time << "ns/access\tN: " << size << "\tIters: " << iters << "\tLoop_iters:" << loop_iters << "\n";
		loop_avg = loop_avg + avg_time;
	}
	loop_avg = loop_avg / loop_iters;
	outfile << loop_avg << "," << iters << "," << size << "," << loop_iters << "\n"; //save the result to a text file
	delete [] arrboy;
    outfile.close();
}

//how does the block at line 79 work? well -
	//every value in arrboy is 0-255, because it's a byte. proportion is (size/256). (1)
	//If we read a (value * proportion), we pick 256 random points along arrboy. (2)
	//But, the cache will just save those 256 items.
	//So we add stride to reader, and keep reader as a running sum. (3)
	//That way, on each loop, we break into 256 new possible indices.
	//Therefore, to prefetch just one loop ahead, the cache would neet to store (256^2) possible indices.
	//Josh&Ryan: 1, Intel/AMD: 0
