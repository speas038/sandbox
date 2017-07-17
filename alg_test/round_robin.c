#include <stdio.h>
#include <unistd.h>

#define ARRAY_SIZE 15


int get_next_index_round_robin()
{
    static int i = 0;
    int ret = 0;

    i = i % ARRAY_SIZE;
    ret = i;

    i++;
    return ret;
}


int main()
{
    for( int i = 0; i < ( ARRAY_SIZE * 2 );  i++ )
    {
        printf( "Current index: %d\n", get_next_index_round_robin() );
    }
}
