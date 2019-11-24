#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define BUFFSIZE 1
#define BUFFSIZE2 1
#define LINESIZE 8

pid_t tid1;
pid_t tid2;
pthread_t watek1;
pthread_t watek2;

int pauza1, pauza2;
int koniec1, koniec2;

char buf [BUFFSIZE][LINESIZE];

pthread_mutex_t lockprint;


pthread_mutex_t lock;
pthread_cond_t notempty;
pthread_cond_t notfull;	

int readposition, writeposition;

int itemCount; //ile jest linii w buforze
void* funkcja_watek1(void* dane);
void* funkcja_watek2(void* dane);


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
	printf("watek1 wstawil kolejna linie do bufora \n");

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
	printf("watek2 zabral kolejna linie z bufora \n");
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

void init()
{	
	int i;
	for (i=0;i<BUFFSIZE;i++)
	{
		strcpy(buf[i], "-");
	}
	pthread_mutex_init(&lock,0); //ustawiam na otwarty
	pthread_cond_init(&notempty,0);
	pthread_cond_init(&notfull,0);
	itemCount=0;
	readposition=0;
	writeposition=0;

	pthread_mutex_init(&lockprint,0);
	pauza1=0;
	pauza2=0;
	koniec1=0;
	koniec2=0;
}

void* mainwatek (void* z)
{
	printf("utworzylem watek glowny\n");
	pthread_t watekczytajacy;
	pthread_t watekpiszacy;
	pthread_create( &watek1, NULL, funkcja_watek1, NULL);
	pthread_create( &watek2, NULL, funkcja_watek2, NULL);
	pthread_join(watek1,NULL);
	pthread_join(watek2,NULL);
	
}

void* funkcja_watek1(void* dane)
{
	tid1 = (pid_t) syscall (SYS_gettid);
	pid_t pid=getpid();
	pid_t ppid=getppid();
	printf ("watek 1 rozpoczyna dzialanie TID: PID: PPID: %d %d %d \n",tid1,pid,ppid);
	char linia[LINESIZE];
	while ((fgets(linia,LINESIZE,stdin)!=NULL)&&(koniec1==0))
	{	
		if (pauza1==0)
		{

		linia[strlen(linia)-1]='\0';
		printf("watek1 przeczytal z wejscia linie: %s\n", linia);
			wstaw_do_bufora(linia);
		}
	}
	
	printf("watek 1 konczy dzialanie\n");
}

void* funkcja_watek2(void* dane)
{
	tid2 = (pid_t) syscall (SYS_gettid);
	pid_t pid=getpid();
	pid_t ppid=getppid();
	printf ("watek 2 rozpoczyna dzialanie TID: PID: PPID: %d %d %d \n",tid2,pid,ppid);
	char linia[LINESIZE];
	while (koniec2==0)
	{
		pobierz_z_bufora(linia);
		printf("watek2 przeczytal z bufora linie: %s\n", linia);;
		while(pauza2==1) {}	
	}
	printf("watek 2 konczy dzialanie\n");
}


int main(void)
{
init ();
pthread_t watekglowny;
pthread_create(&watekglowny,NULL,mainwatek,NULL);
pthread_join (watekglowny,NULL);
pthread_join(watek1,NULL);
pthread_join(watek2,NULL);
printf("zakonczono proces glowny\n");
}
