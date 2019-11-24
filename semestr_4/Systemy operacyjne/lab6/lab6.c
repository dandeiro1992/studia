#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void zamien(int liczba)
{
  if(liczba>0)
  { 
	zamien (liczba/2);
	printf("%d",liczba%2); 
  }
}

void* wyswietl(void *z)
{
	pid_t tid = (pid_t) syscall (SYS_gettid);
	printf ("\nliczba przed konwersja: %d , TID: %d \n", (int) z, 	tid);
	printf ("liczba po konwersji\n");
	zamien((int) z);
	pthread_exit(z);
}

int main (int argc, char *argv[])
{
 int ile = atoi(argv[1]);
 pthread_t id_watek[ile];
int m=0;
while (m<ile)
{
 int s = rand()%5;
pthread_create(&id_watek[m], 0, &wyswietl, (void *) atoi(argv[m+2]));
sleep(s);
m++;
 	
 }
}
