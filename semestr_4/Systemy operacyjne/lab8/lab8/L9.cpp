#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO "fifoFile"

void konsument();
void producent();

int main(int argc, const char *argv[]){
	/*if(argc == 3) {
                if(strcmp(argv[2],"CLIENT")) { 
                        konsument(); 
                } else { 
                        producent(); 
                }
                exit(0);
        }*/
        //umask(0);
        mknod(FIFO, S_IFIFO|0666, 0);
        if(fork()) {
               // execl(argv[0], argv[0], FIFO, "SERVER", NULL);
		producent();
        } else {
                //execl(argv[0], argv[0], FIFO, "CLIENT", NULL);
		konsument();
        }
        return 0;
}

void konsument() {
        FILE *f;
        char paczka[200];       
        while(true){
                f = fopen(FIFO, "r");       
                fgets(paczka, 200, f);
                printf("Odebrano : %s\n\n", paczka);
                fclose(f);
        }
}

void producent() {
        FILE *f;
        char paczka[200], *wskaznik;
        wskaznik = paczka;

        while(true){
                f = fopen(FIFO, "w");
                fprintf(stdout, "Podaj dane do wysłania : ");
                fscanf(stdin, "%s", wskaznik);
                fputs(wskaznik, f);
                fclose(f);
		sleep(1);
        }
// fclose(f);
}
