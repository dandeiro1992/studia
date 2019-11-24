#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO "fifoFile"

void konsument();
void producent();

int main()
{
        //umask(0);
        mknod(FIFO, S_IFIFO|0666, 0);
        if(fork()) 

			{
				producent();
			} 

	else 
			{
				konsument();
			}
        return 0;
}

void konsument() {
        FILE *f;
        char bufor[200];       
        while(true){
                f = fopen(FIFO, "r");       
                fgets(bufor, 200, f);
                printf("Odebrano : %s\n\n", bufor);
                fclose(f);
        }
}

void producent() {
        FILE *f;
        char bufor[200], *wskaznik;
        wskaznik = bufor;

        while(true){
                f = fopen(FIFO, "w");
                fprintf(stdout, "Podaj dane do wysłania : ");
                fscanf(stdin, "%s", wskaznik);
                fputs(wskaznik, f);
                fclose(f);
		sleep(2);
        }
}
