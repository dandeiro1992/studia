#include <pthread.h>
#include <stdio.h>
#include <signal.h>
   #define _GNU_SOURCE
   #include <unistd.h>
   #include <sys/syscall.h>
   #include <sys/types.h>


//autor: Arkadiusz Orzeł
void syg(int sig)
{
pid_t tid;

       tid = syscall(SYS_gettid);
    printf("Otrzymalem sygnal INT (nr: %d)\n", sig);
	  printf("TID: %d\n", tid);
//signal(SIGINT, SIG_DFL);
}
void* wyswietl2(void *k)
{	signal(SIGINT, syg);
	signal(SIGTSTP, syg);
	signal(SIGABRT, syg);

	//podmiana domyslnej obslugi signalu INT
    	/*signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGABRT, SIG_IGN);*/

	pthread_exit(k);

}

void* wyswietl(void *z)
{
	printf ("\nWartosc przekazana do watku: %d ", (int) z);
	//podmiana domyslnej obslugi signalu INT
    	//signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
    	signal(SIGQUIT, SIG_IGN);
	signal(SIGILL, SIG_IGN);
	signal(SIGTRAP, SIG_IGN);
	signal(SIGIOT, SIG_IGN);
	signal(SIGBUS, SIG_IGN);
signal(SIGFPE, SIG_IGN);
//signal(SIGKILL, SIG_IGN);
signal(SIGUSR1, SIG_IGN);
signal(SIGUSR2, SIG_IGN);
signal(SIGSEGV, SIG_IGN);
signal(SIGPIPE, SIG_IGN);
signal(SIGALRM, SIG_IGN);
signal(SIGTERM, SIG_IGN);
signal(SIGCHLD, SIG_IGN);
signal(SIGSTOP, SIG_IGN);
signal(SIGTTIN, SIG_IGN);
signal(SIGTTOU, SIG_IGN);
signal(SIGXCPU, SIG_IGN);
signal(SIGXFSZ, SIG_IGN);
signal(SIGVTALRM, SIG_IGN);
signal(SIGPROF, SIG_IGN);
signal(SIGWINCH, SIG_IGN);
signal(SIGIO, SIG_IGN);
signal(SIGPWR, SIG_IGN);

while(1) {
        printf(".\n");
        sleep(1);
    }

	pthread_exit(z);


}
int main (int argc, char **argv)
{ 

pthread_t id_watek;
pthread_t id_watek2;


 int w=122;
 void * str;
pthread_create(&id_watek, 0, &wyswietl, (void *) w);
pthread_join(id_watek, &str);
int e=200;
 void * str2;
 pthread_create(&id_watek2, 0, &wyswietl2, (void *) e);
 pthread_join(id_watek2, NULL);


}
