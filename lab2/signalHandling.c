#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void * signal_handler(int signumber)
{
   switch(signumber) {
	   case 2: //SIGINT
		   printf("\nProgram Interrupt Signal Handled\n\n");
		   exit(1);
	   case 3: //SIGQUIT
		   printf("\nQuit Signal Handled\n\n");
		   exit(1);
	   case 15: //SIGTERM
		   printf("\nTermination Signal Handled\n\n");
		   exit(1);
	   case 8: //SIGFPE
		   printf("\nArithmetic Error Signal Handled\n\n");
		   exit(1);
	   case 11: // SIGSEGV
		   printf("\nSegmentation Violation Signal Handled\n\n");
		   exit(1);
	   case 4: // SIGILL
		   printf("\nKill Signal Handled\n\n");
		   exit(1);
	   default:
		   break;
   }
}
int main()
{
   signal( SIGINT, (void *)  signal_handler );
   //signal( SIGINT, SIG_IGN);
   signal( SIGQUIT, (void *)  signal_handler );
   signal( SIGTERM, (void *)  signal_handler );
   signal( SIGFPE, (void *)  signal_handler );
   signal( SIGSEGV, (void *)  signal_handler );
   signal( SIGILL, (void *)  signal_handler );

   //int sigfpeError = 0 / 0;
   //char *a;
   //a[10] = "a";
   
   //raise(SIGILL);

   while(1) {
	printf("Doing Nothing...\n");
	sleep(1000);
   }

   return 0;
}
