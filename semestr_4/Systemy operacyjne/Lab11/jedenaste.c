#include <sys/syscall.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
void* pisanie (void* z);
void* czytanie (void* z);

#define BUFFSIZE 8

char buf [BUFFSIZE];

pthread_mutex_t lockprint;


pthread_mutex_t lock;
pthread_cond_t notempty;
pthread_cond_t notfull;	

void printbuf()
{	pthread_mutex_lock (&lockprint); 
	int i;
	for (i=0;i<BUFFSIZE;i++)
	{
		printf ("%d %s\n", i , buf[i]);
	}
	pthread_mutex_unlock (&lockprint); 
}

void* mainwatek (void* z)
{
	printf("utworzylem watek glowny\n");
	pthread_t watekczytajacy;
	pthread_t watekpiszacy;
	pthread_create (&watekczytajacy,NULL,czytanie,NULL);
	pthread_create (&watekpiszacy,NULL,pisanie,NULL);
	pthread_join(watekczytajacy,NULL);
	pthread_join(watekpiszacy,NULL);
	pthread_exit(NULL);
	
}

void* czytanie (void* z)
{

	printf("utworzylem watek czytajacy\n watekczytajacy rozpoczyna dzialanie\n");
	char linia[BUFFSIZE];
	while ((fgets(linia,LINESIZE,stdin)!=NULL)))
	{
		linia[strlen(linia)-1]='\0';
		printf("watek1 przeczytal z wejscia linie: %s\n", linia);
		wstaw_do_bufora(linia);
	}
	printf("watek czytajacy konczy dzialanie\n);
	//pthread_exit(NULL);


}

void* pisanie (void* z) 
{

	printf("utworzylem watek piszacy\n");
	char linia[BUFFSIZE];
	while(koniec2==0)
	{
		pobierz_z_bufora(linia);
		printf("watek piszacy przeczytal z bufora linie : %s\n", linia);
	}
	printf("watek piszacy konczy dzialanie\n");
	//pthread_exit(NULL);


}

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

}
int main (void)
{
	init();
	pthread_t watekglowny;
	pthread_create(&watekglowny,NULL,mainwatek,NULL);
	pthread_join(watekglowny,NULL);

	printf("watek glowny zakonczyl swoje dzialanie\n");
	return 0;

pthread_create( &watek1, NULL, funkcja_watek1, NULL);
pthread_create( &watek2, NULL, funkcja_watek2, NULL);



}
