#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
pthread_t id_watek;
pid_t tid2;
int x = 1;
void syg(int sig)
{
	pid_t tid;
	tid = syscall(SYS_gettid);
	if(tid != tid2)
	{
		if( sig == SIGINT) exit(0);
		else
		{
			 printf("Otrzymalem sygnal INT (nr: %d)\n", sig);
			 printf("TID: %d\n", tid);
		}
	}
}
void* wyswietl2(void *k)
{	
signal(SIGINT,syg);
signal(SIGTSTP, syg);
signal(SIGABRT, syg);
signal(SIGHUP, syg);
signal(SIGQUIT, syg);
signal(SIGILL, syg);
signal(SIGTRAP, syg);
signal(SIGIOT, syg);
signal(SIGBUS, syg);
signal(SIGFPE, syg);
signal(SIGKILL, syg);
signal(SIGUSR1, syg);
signal(SIGUSR2, syg);
signal(SIGSEGV, syg);
signal(SIGPIPE, syg);
signal(SIGALRM, syg);
signal(SIGTERM, syg);
signal(SIGCHLD, syg);
signal(SIGSTOP, syg);
signal(SIGTTIN, syg);
signal(SIGTTOU, syg);
signal(SIGXCPU, syg);
signal(SIGXFSZ, syg);
signal(SIGVTALRM, syg);
signal(SIGPROF, syg);
signal(SIGWINCH, syg);
signal(SIGIO, syg);
signal(SIGPWR, syg);
	pthread_exit(k);
 }
void* wyswietl(void *z)
{
tid2 = syscall(SYS_gettid);
signal(SIGINT, SIG_IGN);
signal(SIGTSTP, SIG_IGN);
signal(SIGABRT, SIG_IGN);
signal(SIGHUP, SIG_IGN);
signal(SIGQUIT, SIG_IGN);
signal(SIGILL, SIG_IGN);
signal(SIGTRAP, SIG_IGN);
signal(SIGIOT, SIG_IGN);
signal(SIGBUS, SIG_IGN);
signal(SIGFPE, SIG_IGN);
signal(SIGKILL, SIG_IGN);
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
a:
x = 1;
do{
        printf(".\n");
        sleep(1);
    } while(x != 3);

pthread_exit(z);
}
int main (int argc, char **argv)
{ 
pthread_t id_watek2;
int e=200;
 pthread_create(&id_watek2, 0, &wyswietl2, (void *) e);
 int w=122;
 void * str;
pthread_create(&id_watek, 0, &wyswietl, (void *) w);
pthread_join(id_watek, NULL);
}
