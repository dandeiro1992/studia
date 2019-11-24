#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define BUFFSIZE 5
#define LINESIZE 100
#define BUFFSIZE2 3
#define KONCZ 1
#define PAUZA 2
#define WZNOW 3

int pauza1, pauza2, pauza3; 
int koniec1, koniec2, koniec3;

char buf [BUFFSIZE][LINESIZE];

pthread_mutex_t lockprint;


pthread_mutex_t lock;
pthread_cond_t notempty;
pthread_cond_t notfull;	

int readposition, writeposition;

int itemCount; //ile jest linii w buforze

void printbuf()
{	pthread_mutex_lock (&lockprint); 
	int i;
	for (i=0;i<BUFFSIZE;i++)
	{
		printf ("%d %s\n", i , buf[i]);
	}
	pthread_mutex_unlock (&lockprint); 
}


void wstaw_do_bufora(char* linia)
{
	pthread_mutex_lock (&lock); //blokuje bufor zeby wstawiac
	while(itemCount==BUFFSIZE)
	{
		pthread_cond_wait(&notfull,&lock);	
	}

	strcpy(buf[writeposition],linia);
	printf("watek1 wstawil kolejna linie do bufora na pozycji: %d\n" , writeposition);

	printbuf();
	writeposition++;	
	if(writeposition==BUFFSIZE)
		writeposition=0;

	itemCount++;
	pthread_cond_signal (&notempty);

	pthread_mutex_unlock (&lock);	//odblokowuje buffor
}


void pobierz_z_bufora(char* linia)
{
	pthread_mutex_lock (&lock); //blokuje bufor zeby wstawiac
	while(itemCount==0)
	{
		pthread_cond_wait(&notempty,&lock);	
	}

	strcpy(linia,buf[readposition]);
	strcpy(buf[readposition],"-");
	printf("watek2 zabral kolejna linie z bufora z pozycji: %d\n" , readposition);
	printbuf();
	readposition++;	
	if(readposition==BUFFSIZE)
		readposition=0;

	itemCount--;
	pthread_cond_signal (&notfull);

	pthread_mutex_unlock (&lock);	//odblokowuje buffor
}

////////////////////////////////////////////////////////////////////////////////////

int buf2 [BUFFSIZE2];

pthread_mutex_t lock2;
pthread_cond_t notempty2;
pthread_cond_t notfull2;	

int readposition2, writeposition2;

int itemCount2; //ile jest linii w buforze

void printbuf2()
{	
	pthread_mutex_lock (&lockprint); 
	int i;
	for (i=0;i<BUFFSIZE2;i++)
	{
		printf ("%d %d\n", i , buf2[i]);
	}
	pthread_mutex_unlock (&lockprint); 
}


void wstaw_do_bufora2(int liczba)
{
	pthread_mutex_lock (&lock2); //blokuje bufor zeby wstawiac
	while(itemCount2==BUFFSIZE2)
	{
		pthread_cond_wait(&notfull2,&lock2);	
	}

	buf2[writeposition2]=liczba;
	printf("watek2 wstawil kolejna liczbe do bufora na pozycji: %d\n" , writeposition2);

	printbuf2();
	writeposition2++;	
	if(writeposition2==BUFFSIZE2)
		writeposition2=0;

	itemCount2++;
	pthread_cond_signal (&notempty2);

	pthread_mutex_unlock (&lock2);	//odblokowuje buffor
}


int pobierz_z_bufora2()
{
	int liczba;
	pthread_mutex_lock (&lock2); //blokuje bufor zeby wstawiac
	while(itemCount2==0)
	{
		pthread_cond_wait(&notempty2,&lock2);	
	}

	liczba=buf2[readposition2];
	buf2[readposition2]=-1;
	printf("watek3 zabral kolejna liczbe z bufora z pozycji: %d\n" , readposition2);
	printbuf2();
	readposition2++;	
	if(readposition2==BUFFSIZE2)
		readposition2=0;

	itemCount2--;
	pthread_cond_signal (&notfull2);

	pthread_mutex_unlock (&lock2);	//odblokowuje buffor
	return liczba;
}


//////////////////////////////////////////////////////////////////////////////////////////

void syg1(int sig)
{
		if(sig == SIGINT) //proces konczy dzialanie 
		{
			printf("watek1 odebral proces SIGINT i zaraz skonczy dzialanie\n");
			koniec1=1;
			kill(0,SIGUSR2);
		}
		if(sig == SIGCONT) //PROCES WZNAWIA DZIALANIE	
		{
			printf("watek1 odebral proces SIGCONT i wznawia dzialanie\n");
			pauza1=0;	
			kill(0,SIGUSR2);
		}
		if(sig == SIGUSR1) // proces pause
		{
			printf("watek1 odebral proces SIGUSR1 i pauzuje\n");
			pauza1=1;
			kill(0,SIGUSR2);
		}
		if(sig == SIGUSR2) //S4
		{
			printf("watek3 odebral sygnal SIGUSR2 i czyta pipe\n");
		}

}

void syg2(int sig)
{
		if(sig == SIGINT) //proces konczy dzialanie 
		{
			printf("watek2 odebral proces SIGINT i zaraz skonczy dzialanie\n");
			koniec2=1;
			kill(0,SIGUSR2);
		}
		if(sig == SIGCONT) //PROCES WZNAWIA DZIALANIE	
		{
			printf("watek2 odebral proces SIGCONT i wznawia dzialanie\n");
			pauza2=0;	
			kill(0,SIGUSR2);
		}
		if(sig == SIGUSR1) // proces pause
		{
			printf("watek2 odebral proces SIGUSR1 i pauzuje\n");
			pauza2=1;
			kill(0,SIGUSR2);
		}
		if(sig == SIGUSR2) //S4
		{
			printf("watek2 odebral sygnal SIGUSR2 i czyta pipe\n");
		}

}
void syg3(int sig)
{
		if(sig == SIGINT) //proces konczy dzialanie 
		{
			printf("watek3 odebral proces SIGINT i zaraz skonczy dzialanie\n");
			koniec3=1;
			kill(0,SIGUSR2);
		}
		if(sig == SIGCONT) //PROCES WZNAWIA DZIALANIE	
		{
			printf("watek3 odebral proces SIGCONT i wznawia dzialanie\n");
			pauza3=0;	
			kill(0,SIGUSR2);
		}
		if(sig == SIGUSR1) // proces pause
		{
			printf("watek3 odebral proces SIGUSR1 i pauzuje\n");
			pauza3=1;
			kill(0,SIGUSR2);
		}
		if(sig == SIGUSR2) //S4
		{
			printf("watek3 odebral sygnal SIGUSR2 i czyta pipe\n");
		}

}

void podmiensygnaly1()
{
	signal(SIGINT, syg1);
	signal(SIGCONT,syg1);
	signal(SIGUSR1,syg1);
	signal(SIGUSR2,syg1);
}


void podmiensygnaly2()
{
	signal(SIGINT, syg2);
	signal(SIGCONT,syg2);
	signal(SIGUSR1,syg2);
	signal(SIGUSR2,syg2);
}


void podmiensygnaly3()
{
	signal(SIGINT, syg3);
	signal(SIGCONT,syg3);
	signal(SIGUSR1,syg3);
	signal(SIGUSR2,syg3);
}











void init()
{	
	int i;
	for (i=0;i<BUFFSIZE;i++)
	{
		strcpy(buf[i], "-");
	}
	pthread_mutex_init(&lock,0); //ustawiam na otawrty
	pthread_cond_init(&notempty,0);
	pthread_cond_init(&notfull,0);
	itemCount=0;
	readposition=0;
	writeposition=0;
/////////////////////////////////////////////////////////////////////
	for (i=0;i<BUFFSIZE2;i++)
	{
		buf2[i]=-1;
	}
	pthread_mutex_init(&lock2,0); //ustawiam na otawrty
	pthread_cond_init(&notempty2,0);
	pthread_cond_init(&notfull2,0);
	itemCount2=0;
	readposition2=0;
	writeposition2=0;
//////////////////////////////////////////////////
	pthread_mutex_init(&lockprint,0);
//////////////////////////////////////////////////////////////////
	pauza1=0;
	pauza2=0;
	pauza3=0;
	koniec1=0;
	koniec2=0;
	koniec3=0;
}


void* funkcja_watek1(void* dane)
{
	pid_t tid = (pid_t) syscall (SYS_gettid);
	pid_t pid=getpid();
	pid_t ppid=getppid();
	printf ("watek 1 rozpoczyna dzialanie TID: PID: PPID: %d %d %d \n",tid,pid,ppid);
	podmiensygnaly1();
	char linia[LINESIZE];
	while ((fgets(linia,LINESIZE,stdin)!=NULL)&&(koniec1==0))
	{
		linia[strlen(linia)-1]='\0';
		printf("watek1 przeczytal z wejscia linie: %s\n", linia);
		wstaw_do_bufora(linia);
		while (pauza1==1) {}
	}
	
	

	printf("watek 1 konczy dzialanie\n");
}

void* funkcja_watek2(void* dane)
{
	pid_t tid = (pid_t) syscall (SYS_gettid);
	pid_t pid=getpid();
	pid_t ppid=getppid();
	printf ("watek 2 rozpoczyna dzialanie TID: PID: PPID: %d %d %d \n",tid,pid,ppid);
	podmiensygnaly2();
	char linia[LINESIZE];
	while (koniec2==0)
	{
		pobierz_z_bufora(linia);
		int d;
		d=strlen(linia);
		printf("watek2 przeczytal z bufora linie o dlugosci: %d\n", d);
		wstaw_do_bufora2(d);
		while(pauza2==1) {}	
	}
	printf("watek 2 konczy dzialanie\n");
}

void* funkcja_watek3(void* dane)
{
	pid_t tid = (pid_t) syscall (SYS_gettid);
	pid_t pid=getpid();
	pid_t ppid=getppid();
	printf ("watek 3 rozpoczyna dzialanie TID: PID: PPID: %d %d %d \n",tid,pid,ppid);
	podmiensygnaly3();
	while (koniec3==0)
	{
		int d;
		d=pobierz_z_bufora2();
		printf("watek3 przeczytal z bufora liczbe: %d\n", d);
		while(pauza3==1) {}
	}
	
	printf("watek 3 konczy dzialanie\n");
}
int main(int argc, char *argv[])
{
init ();
pthread_t watek1;
pthread_t watek2;
pthread_t watek3;

pthread_create( &watek1, NULL, funkcja_watek1, NULL);
pthread_create( &watek2, NULL, funkcja_watek2, NULL);
pthread_create( &watek3, NULL, funkcja_watek3, NULL);
pthread_join(watek1,NULL);
pthread_join(watek2,NULL);
pthread_join(watek3,NULL);
printf("zakonczono proces glowny\n");
}
