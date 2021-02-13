#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void main()
  {
    // sigset_t - The set of signals
    sigset_t set, oset, pset;

    // Initialize to empty 
    sigemptyset( &set );

    // Add SIGINT to signal set
    sigaddset( &set, SIGINT );

    // Block SIGINT (as it was in "set"
    sigprocmask( SIG_BLOCK, &set, &oset );
    printf( "Old set was %ld\n", oset );

    sigpending( &pset ); // Set of signals pending
    printf( "Pending set is %ld\n", pset );

    kill( getpid(), SIGINT );

    sigpending( &pset );
    printf( "Pending set is %ld\n", pset );

    sigprocmask( SIG_UNBLOCK, &set, &oset );
    /* The program terminates with a SIGINT */
  }

/* sigprocmask( ) -> Used to block or unblock signals */
