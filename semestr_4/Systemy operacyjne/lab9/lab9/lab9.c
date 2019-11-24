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
#define ID_SEM_ZAPISU 987654321
#define ID_SEM_ODCZYTU 876543219
#define SIZE 8
#define klucz 123456789

static int sem_odczytu,sem_zapisu;
//static struct sembuf buf1[1],buf2[1]; /* czy to jest potrzebne ? */
static union semun arg;

//char buff[SIZE];
int wejscie=0;
int wyjscie=0;

void P_zapisu()
{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_zapisu,&sb,1);
}

void P_odczytu()
{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_odczytu,&sb,1);
}

void V_zapisu()
{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_zapisu,&sb,1);
}

void V_odczytu()
{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_odczytu,&sb,1);
}
void initbuffor(char*buff)
{
int i;
	for(i=0;i<8;i++)
		buff[i]='-';
}

void wypiszbuffor(char* buff)
{
int i;
	printf("buffor: ");
	for(i=0;i<8;i++)
		printf("%c ", buff[i]);
	printf("\n");
}

void producent (char* buff)
{
char litera;
	for (litera='a'; litera<='z';litera++)
	{
		P_zapisu ();
		buff[wejscie]=litera;
		printf("wyprdukowalem litere: %c " ,litera);
		wypiszbuffor(buff);
		V_odczytu();
		wejscie=(wejscie+1)%SIZE;
		sleep(5);
	}
}

void konsument (char* buff)
{
int m;
	for (m=0;m<26;m++)
	{
		P_odczytu();
		char litera=buff[wyjscie];
		buff[wyjscie]='-';
		printf("zjadlem litere: %c " ,litera);
		wypiszbuffor(buff);
		V_zapisu();
		wyjscie=(wyjscie+1)%SIZE;
		
		sleep(10);
		
	}
}


int main(void)

{
/* utworzenie zbiorow semaforow */
if ((sem_zapisu=semget(ID_SEM_ZAPISU,1,IPC_CREAT | 0666)) < 0) {
printf("blad");
return 1; }
if ((sem_odczytu=semget(ID_SEM_ODCZYTU,1,IPC_CREAT | 0666)) < 0) {
printf("blad");
return 1; }
/* ustawienie wartosci poczatkowych semaforow */
arg.val = 8;
if (semctl(sem_zapisu,0,SETVAL,arg) <0) {
printf("blad");
return 1; }
arg.val = 0;
if (semctl(sem_odczytu,0,SETVAL,arg) <0) {
printf("blad");
return 1; }


	int id = shmget (klucz, SIZE, 0666|IPC_CREAT);
	
	int potpid = fork();
	if (potpid==0)
	{
		printf("jestesmy w procesie potomnym (producent): PID:%d, PPID:%d\n", getpid(), getppid());
		id = shmget (klucz, SIZE, 0666|IPC_EXCL);
		char* buff = shmat (id, 0, 0);
		initbuffor(buff);
		producent(buff);
	}
	else
	{
		printf("jestesmy w procesie macierzystym(konsument): PID:%d, PPID:%d\n", getpid(), getppid());
		char* buff = shmat (id, 0, 0);
		konsument(buff);
	}

}
