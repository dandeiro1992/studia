include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//autor: Adrian Żywluk
#define ROZM 10
void producent();
void konsument();
void Wypisz(char *str)
	{
		write(STDOUT_FILENO, str, strlen(str));
	}

int main(int argc[3],char *argv[])
	{
		int f;
		char wiad[ROZM];
		int do_producenta[2];
		int do_konsumenta[2];

		if(pipe(do_producenta)<0) return(1);
		if(pipe(do_konsumenta)<0) return(1);

	
		if((f=fork())==0)	
		//producent
		{
			close(do_producenta[1]); //zamknięty do pisania, tylko odczyt z [0]
			close(do_konsumenta[0]); //zamknięty do odczytu, tylko zapis do [1]
			
			Wypisz("Zacznij cos podawac\n");
			read(STDIN_FILENO,wiad,ROZM);
			write(do_konsumenta[1],wiad,ROZM);
		}
		//konsument
		close(do_konsumenta[1]); //zamknięty do pisania
		close(do_producenta[0]); //zamknięty do odczytu 

		read(do_konsumenta[0],wiad,strlen(wiad));
		waitpid(f,0,NULL);
		write(STDOUT_FILENO,wiad,strlen(wiad));
		printf("\n");

		return 0;
	}
