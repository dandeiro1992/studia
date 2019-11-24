#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

        main()
        {
                int     fd[2];
                pid_t   potomek;

                pipe(fd);
        
                if((potomek = fork()) == -1)
                {
                        perror("fork");
                        exit(1);
                }

                if(potomek == 0)
                {
                        close(fd[0]);
                }
                else
                {
                        close(fd[1]);
                }
               
        }
