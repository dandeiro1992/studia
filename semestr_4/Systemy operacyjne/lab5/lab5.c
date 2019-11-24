#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void)
{
	printf("Macierzysty >PID: %d\n",getpid());
	if(fork()==0) //P2
	{
		printf("P2: PID:%d, PPID:%d\n", getpid(), getppid());
		if(fork()==0) //P3
		{
			printf("P3: PID:%d, PPID:%d\n", getpid(), getppid());

			if(fork()==0) //P5
			{
				printf("P5: PID:%d, PPID:%d\n", getpid(), getppid());
				pause();
				return 0;
			}
			if(fork()==0) //P6
			{
				printf("P6: PID:%d, PPID:%d\n", getpid(), getppid());

				if(fork()==0) //P10
				{
					printf("P10: PID:%d, PPID:%d\n", getpid(), getppid());
					pause();
					return 0;
				}
				pause();
				return 0;
			}
			if(fork()==0) //P7
			{
				printf("P7: PID:%d, PPID:%d\n", getpid(), getppid());
				pause();
				return 0;
			}

			pause();
			return 0;
		}


		if(fork()==0) //P4
		{
			printf("P4: PID:%d, PPID:%d\n", getpid(), getppid());

			if(fork()==0) //P8
			{
				printf("P8: PID:%d, PPID:%d\n", getpid(), getppid());
				pause();
				return 0;
			}
			if(fork()==0) //P9
			{
				printf("P9: PID:%d, PPID:%d\n", getpid(), getppid());
				pause();
				return 0;
			}

			pause();
			return 0;
		}


		pause();
		return 0;
	}





}
