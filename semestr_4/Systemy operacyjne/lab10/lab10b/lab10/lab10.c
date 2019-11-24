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

int main(void)

{
/*
static union semun arg;


if ((sem_odczytu1=semget(ID_SEM_ODCZYTU1,1,IPC_CREAT | 0666)) < 0) {
printf("blad");
return 1; }
if ((sem_odczytu2=semget(ID_SEM_ODCZYTU2,1,IPC_CREAT | 0666)) < 0) {
printf("blad");
return 1; }
if ((sem_zapisu=semget(ID_SEM_ZAPISU,1,IPC_CREAT | 0666)) < 0) {
printf("blad");
return 1; }

arg.val = SIZE;
if (semctl(sem_zapisu,0,SETVAL,arg) <0) {
printf("blad");
return 1; }
arg.val = 0;
if (semctl(sem_odczytu1,0,SETVAL,arg) <0) {
printf("blad");
return 1; }
arg.val = 0;
if (semctl(sem_odczytu2,0,SETVAL,arg) <0) {
printf("blad");
return 1; }
*/
//// tworzenie pamieci dzielonej 

	int id = shmget (klucz, SIZE, 0666|IPC_CREAT);
	id = shmget (klucz, SIZE, 0666|IPC_EXCL);
	struct PamiecDzielona* buff = shmat (id, 0, 0);
	inicjuj(buff);
	wypisz(buff);
	
	int potpid = fork();

	if (potpid==0)
	{
	printf("jestesmy w procesie potomnym (producent): PID:%d,PPID:%d\n", getpid(), getppid());	
	execl("producent","producent",NULL);
	}



	int potpid2 = fork();
	if (potpid2==0)
	{
	printf("jestesmy w procesie potomnym (komsument1): PID:%d,PPID:%d\n", getpid(), getppid());	
	execl("konsument1","konsument1",NULL);
	}
	


	int potpid3 = fork();
	if (potpid3==0)
	{
	printf("jestesmy w procesie potomnym (komsument2): PID:%d,PPID:%d\n", getpid(), getppid());	
	execl("konsument2","konsument2",NULL);
	}


	printf("proces glowny czeka na zakonczenie potomkow\n");


	wait(0);

	wait(0);

	wait(0);

	
}
