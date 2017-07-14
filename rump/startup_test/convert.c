#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main( int argc, char* argv[])
{
	if( argc < 2 )
	{
		printf("\n\n***NOT ENOUGH ARGS***\n\n");
	}

	uint64_t tsc = strtoull(argv[1], NULL, 10);
	int tsc_shift = atoi(argv[2]);
	uint64_t tsc_to_system_mul = strtoull(argv[3], NULL, 10);

	uint64_t shifted = 0;

	if( tsc_shift < 0 )
	{
		shifted = ( tsc >> -tsc_shift );
	}else
	{
		shifted = ( tsc << tsc_shift );
	}

	uint64_t converted = shifted * tsc_to_system_mul;

	printf("\n\n %llu \n\n", ( unsigned long long )converted );
	
	return 0;
}
