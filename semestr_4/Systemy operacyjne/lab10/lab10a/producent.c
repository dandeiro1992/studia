#include <stdio.h>
#include <ctype.h> 
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include "semun.h"
#include "naglowek.h"

static int sem_odczytu1,sem_odczytu2,sem_zapisu;


void producent

 (struct PamiecDzielona* buff)
{
	char slowo[WORDSIZE];
	char znak;
	int indeks=0;
	FILE *f;
	f=fopen("/home/damian/Pulpit/lab10/text.txt","r");
	while( EOF !=  znak )
	{
	indeks=0;
	int i;
	
	for(i=0; i<WORDSIZE; i++) slowo[i]='\0';
	 while((znak=fgetc(f))!=32 && znak!=EOF && indeks<WORDSIZE)
		{
			slowo[indeks] = znak;
			indeks++;
         	}
		slowo[indeks]='\0';

		strcpy(buff->buff[buff->indeks_zapisu],slowo);
		printf("wyprodukowalem slowo: %s\n" ,slowo);
		wypisz(buff);
		buff->indeks_zapisu=(buff->indeks_zapisu+1)%SIZE;
		buff->ile_zajetych=buff->ile_zajetych+1;
		if(buff->ile_zajetych==1)
		{
		V_odczytu(sem_odczytu1, sem_odczytu2,buff->czyja_kolej);
		}
	sleep(3);
	}
  fclose(f); 
}


int main()
{
if ((sem_odczytu1=semget(ID_SEM_ODCZYTU1,1,IPC_EXCL)) < 0) {
printf("blad");
return 1; }
if ((sem_odczytu2=semget(ID_SEM_ODCZYTU2,1,IPC_EXCL)) < 0) {
printf("blad");
return 1; }
if ((sem_zapisu=semget(ID_SEM_ZAPISU,1,IPC_EXCL)) < 0) {
printf("blad");
return 1; }
	printf("jestesmy w procesie potomnym (producent) po funkcji execl: PID:%d, PPID:%d\n", getpid(), getppid());	
	int id = shmget (klucz, SIZE, 0666|IPC_EXCL);
	struct PamiecDzielona* buff = shmat (id, 0, 0);
	wypisz(buff);
	producent(buff);
	
}
	
