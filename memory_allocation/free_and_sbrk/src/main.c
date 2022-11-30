// main file

#include <tlpi/tlpi_hdr.h>

#define MAX_ALLOCS 1000000

int main(int argc, char **argv)
{
	char *ptr[MAX_ALLOCS];
	puts("");

	if(argc < 3 || strncmp(argv[1], "--help", 6) == 0)
		usageErr("%s num-allocs block-size [step [min [max]]]\n");

	int num_allocs = getInt(argv[1], GN_GT_0, "num_allocs");
	if(num_allocs > MAX_ALLOCS)
		cmdLineErr("num_allocs > %d\n", MAX_ALLOCS);

	int block_size = getInt(argv[2], GN_GT_0 | GN_ANY_BASE, "block_size");

	int free_step = (argc > 3) ? getInt(argv[3], GN_GT_0, "step") : 1;
	int free_min = (argc > 4) ? getInt(argv[4], GN_GT_0, "min") : 1;
	int free_max = (argc > 5) ? getInt(argv[5], GN_GT_0, "max") : num_allocs;

	if(free_max > num_allocs)
		cmdLineErr("free_max > num_allocs\n");

	printf("Initial program break:          %10p\n", sbrk(0));

	printf("Allocating %d*%d bytes\n", num_allocs, block_size);

	for(int j = 0; j < num_allocs; j++)
	{
		ptr[j] = malloc(block_size);
		if(ptr[j] == NULL)
			errExit("malloc");
	}

	printf("Program break is now:           %10p\n", sbrk(0));

	printf("Freeing blocks from %d to %d in steps of %d\n",
			free_min, free_max, free_step);
	for(int j = free_min - 1; j < free_max; j+=free_step)
		free(ptr[j]);

	printf("After free(), program break is: %10p\n", sbrk(0));

	exit(EXIT_SUCCESS);
}

/** TODO:
  * 1. save the program break(pointer position) in a variable(what data type to use)
  * 2. can you compare two pointer positions ?
  * 3. print every time program break moves ?
  * 4. while using free() check out what is the meaning of free_step there ?
  */