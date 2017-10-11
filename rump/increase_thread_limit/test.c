#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <stdlib.h>
#include <errno.h>

#define NUM_THREADS 8000

typedef struct thread_info_t {

    pthread_t thread_id;
    int t_num;
    sem_t sem;

} thread_info;



static void *
thread_func( void *arg )
{
    thread_info *t_info = ( thread_info *) arg;
    
    printf("Thread %d started\n", t_info->t_num );
    fflush(stdout);
	
	if(t_info->t_num == 256)
    {
//		asm("int3");
	}

    sem_wait( &t_info->sem );

    printf("Thread %d Exiting\n", t_info->t_num );


ErrorExit:
    
    return NULL;
}


static int
setlimit( void )
{
    int rc = 0;
    struct rlimit lim = { 0 };


//    //Default max is 2048
//    rc = getrlimit( RLIMIT_NTHR, &lim );
//    if ( rc )
//    {
//        perror( "setrlimit" );
//    }
//
	lim.rlim_max = 8000;
    lim.rlim_cur = lim.rlim_max;
    rc = setrlimit( RLIMIT_NTHR, &lim );
    if ( rc )
    {
        perror( "setrlimit" );
    }


//    //Default max is 532
//    rc = getrlimit( RLIMIT_NPROC, &lim );
//    if ( rc )
//    {
//        perror( "setrlimit" );
//    }
//    
//    lim.rlim_cur = lim.rlim_max;
//    rc = setrlimit( RLIMIT_NPROC, &lim );
//    if ( rc )
//    {
//        perror( "setrlimit" );
//    }
//
//    
//    //Default max is 1772
//    rc = getrlimit( RLIMIT_NOFILE, &lim );
//    if ( rc )
//    {
//        perror( "setrlimit" );
//    }
//   
	lim.rlim_max = 8003; 
    lim.rlim_cur = lim.rlim_max;
    rc = setrlimit( RLIMIT_NOFILE, &lim );
    if ( rc )
    {
        perror( "setrlimit" );
    }


    return 0;
}

int
sysctl_test_write()
{

	//******NOT TESTED******
    struct sysctlnode node;
    int mib[2];
    size_t len;

    mib[0] = CTL_CREATE;            /* create at top-level */
    len = sizeof(node);
    memset(&node, 0, len);
    node.sysctl_flags = SYSCTL_VERSION|CTLFLAG_READWRITE|CTLTYPE_NODE;
    snprintf(node.sysctl_name, sizeof(node.sysctl_name), "local");
    node.sysctl_num = CTL_CREATE;   /* request dynamic MIB number */
    sysctl(&mib[0], 1, &node, &len, &node, len);

    mib[0] = node.sysctl_num;       /* use new MIB number */
    mib[1] = CTL_CREATESYM;         /* create at second level */
    len = sizeof(node);
    memset(&node, 0, len);
    node.sysctl_flags = SYSCTL_VERSION|CTLFLAG_READWRITE|CTLTYPE_INT;
    snprintf(node.sysctl_name, sizeof(node.sysctl_name), "audiodebug");
    node.sysctl_num = CTL_CREATE;
    node.sysctl_data = "audiodebug"; /* kernel symbol to be used */
    sysctl(&mib[0], 2, NULL, NULL, &node, len);
}


int
sysctl_test_read()
{

	//********NOT TESTED**********//
    int mib[2];
    struct sysctlnode node;
    size_t len;

    len = sizeof(node);
    memset(&node, 0, len);
    node.sysctl_flags = SYSCTL_VERSION;

    mib[0] = 3214;                  /* assumed number for "local" */
    mib[1] = CTL_DESTROY;
    node.sysctl_num = 3215;         /* assumed number for "audiodebug" */
    sysctl(&mib[0], 2, NULL, NULL, &node, len);

    mib[0] = CTL_DESTROY;
    node.sysctl_num = 3214;         /* now deleting "local" */
    sysctl(&mib[0], 1, NULL, NULL, &node, len);

}


int
test_kern_maxproc()
{
	
	int mib[2], maxproc;
	size_t len;
	mib[0] = CTL_KERN;
	mib[1] = KERN_SYSVIPC;
	len = sizeof(maxproc);
	sysctl(mib, 2, &maxproc, &len, NULL, 0);
	
	printf("Getting kern maxproc \n");
}


int
test_path_stuff()
{
	int mib[2] = {0};
	size_t len = 0;
	int *p;
    int rc = -1;

	mib[0] = CTL_USER;
	mib[1] = USER_CS_PATH;

	rc = sysctlbyname( "kern.ipc.semmns", NULL, &len, NULL, 0);
    if ( rc ) 
    { 
        printf("Error\n"); 
    }
    p = malloc(len);

	sysctlbyname( "kern.ipc.semmns", p, &len, NULL, 0);

	return 0;
}

int
test_read_from_proc_fs()
{
    FILE *fp = NULL;
    char buff[255] = {0};
    
    fp = fopen( "/proc/sys/kernel/sem", "r" );
    if( NULL == fp )
    {
        printf("ERROR \n");
    }

    fgets( buff, 255, (FILE*)fp );
    printf( "%s \n",buff );

    fclose( fp );

    return 0;
}

int query_sysctl()
{

    struct sysctlnode query = {0};
	struct sysctlnode vfs[128] = {0};
    int mib[2] = {0};
    size_t len = 0;

//    mib[0] = CTL_KERN;
//    mib[0] = KERN_SYSVIPC;
    mib[0] = KERN_HOSTNAME;
    mib[1] = CTL_QUERY;
    memset(&query, 0, sizeof(query));
    query.sysctl_flags = SYSCTL_VERSION;
    len = sizeof(vfs);
    sysctl(mib, 2, &vfs[0], &len, &query, sizeof(query));

	for( int i = 0; i < 128; i++ )
	{
		printf( "%s \n", vfs[i].sysctl_name);
		fflush(stdout);
		sleep(1);
	}
	printf("Done\n");
}

int
get_semaphore_limit()
{

	long limit = sysconf( _SC_SEM_NSEMS_MAX );
	printf("Limit: %ld\nerrno: %d\n\n", limit, errno );
	
	return 0;

}

int
main()
{

	setlimit();

//	test_kern_maxproc();

//	test_path_stuff();

//    test_read_from_proc_fs();

//    query_sysctl();

//	get_semaphore_limit();


    thread_info t_info [ NUM_THREADS ] = {0};
	int rc = 0;
    printf("Listening on multiple ports to test multi-ins functinality\n\n");

    for( int i = 0; i < NUM_THREADS; i++ )
    {
		rc = sem_init( &t_info[i].sem, 8, 0 ); 
		if( rc )
		{
			printf("Semaphore %d initialization failed\n", i );
		}

		if( i == 1769 )
		{
//			asm("int3");
		}

    }
    
    for( int i = 0; i < NUM_THREADS; i++ )
    {
        t_info[i].t_num = i;
        pthread_create( &t_info[i].thread_id, NULL,
                        &thread_func, (void *) &t_info[i] );
    }

    for( int i = 0; i < NUM_THREADS; i++ )
    {
        pthread_join( t_info[i].thread_id, NULL );
    }

    printf("Program finished\n");

}


