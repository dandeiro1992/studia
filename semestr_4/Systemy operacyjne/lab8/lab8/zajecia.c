#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define ROZM 10

void producent();
void konsument();

void Wypisz(char *str)
	{
		write(STDOUT_FILENO, str, strlen(str));
	}
int main ()
{
char wiad[ROZM];
		int do_producenta[2];
		int do_konsumenta[2];

		if(pipe(do_producenta)<0) return(1);
		if(pipe(do_konsumenta)<0) return(1);

	close(do_producenta[1]);
	close(do_konsumenta[0]);


