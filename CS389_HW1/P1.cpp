
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

uint8_t * generate_random_list(int64_t size, int16_t bound)
{
	uint8_t* list;
	list = new uint8_t [size];
	if(!list){/*death*/}

	srand(size);
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
	uint8_t *arrboy = generate_random_list(size, 256);
	//LOOP
	for(int64_t l = 0; l < loop_iters; l++)
	{
		//randomly generate prime number greater than N
		int64_t stride = 4;
		int64_t reader = 1;
		while (!isPrime(stride))
		{
			stride = rand();
			if (stride < 0) {stride = -1 * stride;}
			stride = stride % size;
		}
		printf("%d\n",stride);
		printf("%d\n",size);
		//read all the bytes once // THIS RESETS CAPS LOCK
		for(int64_t r = 0; r < size; r++) {reader = arrboy[r];}

		//start the clock
		float time_current = 0; //something something clock monotonic

		//read all the bytes (iters) times -- read them mod a prime number so that we can foil AMD/Intel
		for(int64_t ov = 0; ov < iters; ov++)
		{
			for(int64_t it = 0; it < size; it++)
			{
				reader = arrboy[((it*stride) % size)];
				printf("%d  ", reader);
			}
		}
		//stop the clock
		float time_elapsed = 0; //something something clock monotonic

		//shuffle all of the bytes around, somehow?? -- optional step

		//compute N/time elapsed
		float avg_time = time_elapsed/(size * iters);
		
		//print it!
		printf("The results are in, folks!! How many nanoseconds per access was it?\nWell, it was...... %fns/access!!\n", avg_time);
		//save the result to a json, somehow?? -- optional step
		outfile << "Time: " << avg_time << "ns/access\tN: " << size << "\tIters: " << iters << "\tLoop_iters:" << loop_iters << "\n";
	}
	delete [] arrboy;
	outfile.close();
}