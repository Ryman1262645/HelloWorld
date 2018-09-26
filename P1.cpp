#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//now we can print like "cout <<"Hello World!"<< endl;"
int main ()
{
	uint8_t* list;
	list = malloc(sizeof(uint8_t) * size);
	if(!list){/*death*/}

	srand(size);
	for(int64_t i = 0; i < size; i++)
	{
		list[i] = (rand() % bound);
	}
	return list;
}

int main (int argc, char **argv)
{
	//take arguments
	int64_t size = atoi(argv[1]);
	int64_t iters = atoi(argv[2]);

	//generate an array of 2^(N) random byte
	uint8_t *arrboy = generate_random_list(size, 255);

	//LOOP
		//start the clock
		//read all the bytes (iters) times
			//read them mod a prime number so that we can foil AMD/Intel
				//hahahahaha
		//stop the clock
		//shuffle all of the bytes around, somehow
		//compute N/time elapsed
		//print it!
		//back to the top!
	return
}

//doesn't our timer need to be outside the loop like how we discussed in class?
