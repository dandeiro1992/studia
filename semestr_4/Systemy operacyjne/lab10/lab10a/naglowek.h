#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#ifndef _NAGLOWEK
#define _NAGLOWEK


#define ID_SEM_ODCZYTU1 876543219
#define ID_SEM_ODCZYTU2 875555555
#define ID_SEM_ZAPISU 	111111111
#define SIZE 8
#define klucz 123456789
#define WORDSIZE 70

struct PamiecDzielona
{
	char buff[SIZE][WORDSIZE];
	int indeks_odczytu;
	int indeks_zapisu;
	int ile_zajetych;
	int czyja_kolej;
};

void P_zapisu(int sem_zapisu)
{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_zapisu,&sb,1);
}

void P_odczytu(int sem_odczytu1,int sem_odczytu2,int czyja_kolej)
{
	if(czyja_kolej==2)
	{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_odczytu2,&sb,1);
	}
	else
	{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=-1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_odczytu1,&sb,1);
	}
}

void V_zapisu(int sem_zapisu)
{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_zapisu,&sb,1);
}

void V_odczytu(int sem_odczytu1,int sem_odczytu2,int czyja_kolej)
{
	if(czyja_kolej==2)
	{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_odczytu2,&sb,1);
	}
	else
	{
	struct sembuf sb;
	sb.sem_num=0;
	sb.sem_op=1;
	sb.sem_flg=SEM_UNDO;
	semop(sem_odczytu1,&sb,1);
	}
}

void inicjuj(struct PamiecDzielona *buff)
{
	int i=0;
	for (i=0;i<SIZE;i++)
	{
		strcpy(buff->buff[i],"-");
	}

	buff->indeks_odczytu=0;
	buff->indeks_zapisu=0;
	buff->ile_zajetych=0;
	buff->czyja_kolej=0;
}

void wypisz(struct PamiecDzielona *buff)
{
	int i=0;
	for (i=0;i<SIZE;i++)
	{
		printf("%d %s\n",i,buff->buff[i]);
	}
}

#endif
