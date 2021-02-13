include <signal.h>
#include <stdio.h>

void handler(int sig)
{ 
  printf("Caught signal: %d",sig);
}

int main()
{
  struct sigaction sa;
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask); // No signals are masked

  if (sigaction(SIGINT, &sa, NULL) == -1)
     perror("Sigaction");

  kill(0, SIGINT); // 0 means signal sent to every process in process-group
                   // You can also mention a PID to deliver to specific process
}

/* Members of sigaction are:
   sa.sa_handler ==> Pointer to signal catching function with one arg (sig no)
   sa.sa_mask ==> Additional set of signals to be blocked during execution of signal-catching function. Type is sigset_t (Set of signals)
   sa.sa_sigaction => Pointer to signal catching function with multiple args.
                 void(*) (int, siginfo_t *, void *)
                 
   sigaction(SIGNAL_NUMBER, &sa_new, &sa_old) => If the last argument is not NULL, it stores the current signal actions in this set.

   https://pubs.opengroup.org/onlinepubs/007904875/functions/sigaction.html
*/
