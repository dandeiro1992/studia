#include <stdio.h>
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



void konsument1

 (struct PamiecDzielona* buff)
{
	char slowo[WORDSIZE];
	while(1)
	{
		P_odczytu (sem_odczytu1,sem_odczytu2,0);
		strcpy(slowo,buff->buff[buff->indeks_odczytu]);
		strcpy(buff->buff[buff->indeks_odczytu],"-");
		printf("konsument1: zjadlem slowo: %s\n" ,slowo);
		wypisz(buff);
		buff->indeks_odczytu=(buff->indeks_odczytu+1)%SIZE;
		buff->ile_zajetych=buff->ile_zajetych-1;
		buff->czyja_kolej=(buff->czyja_kolej+1)%3;
		if(buff->ile_zajetych==0)
		{
		}
		else if(buff->czyja_kolej==2)
		{
		V_odczytu(sem_odczytu1, sem_odczytu2,2);
		}
		else
		{
		V_odczytu(sem_odczytu1, sem_odczytu2,1);
		}

		V_zapisu(sem_zapisu);
	}
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
	printf("jestesmy w procesie potomnym (konsument1) po funkcji execl: PID:%d, PPID:%d\n", getpid(), getppid());	
	int id = shmget (klucz, SIZE, 0666|IPC_EXCL);
	struct PamiecDzielona* buff = shmat (id, 0, 0);
	wypisz(buff);
	konsument1(buff);
	
}
	
