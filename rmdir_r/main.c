#include <stdio.h>
#include "rmdir_r.h"

#define PROGNAME "rmdir_r"

static void usage(void)
{
	printf("Usage: %s filename\n", PROGNAME);	
}

int main(int argc, char **argv)
{
	if (argc != 2) 
	{
		usage();
		return -1;
	}

	rmdir_r(argv[1]);

	return 0;
}
