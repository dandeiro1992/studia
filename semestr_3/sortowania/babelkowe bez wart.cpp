#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <cmath>
#include <cstdlib>
const int n=100;
void babelbez(int *tab, int n);
int main ()
{
	int tablica1[n];
		srand(time(NULL));
	for(int i=0; i<n ; i++)
		tablica1[i]=rand() % 100;

	for(int i=0; i<n ; i++)
		printf("%d  ",tablica1[i]);
		printf("\n");

	babelbez(tablica1,n);
	printf("\n");
	for(int i=0; i<n ; i++)
		printf("%d  ",tablica1[i]);
		printf("\n");
		
	getche();
	return 0;
}

void babelbez(int *tab, int n)
{
	int c,p;
	for (int j=0;j<n;j++)
	for (int i=0;i<n;i++)
	{
		if (tab[i]>tab[i+1])
			{
					c=tab[i];
					tab[i]=tab[i+1];
					tab[i+1]=c;
					p=1;
			}		
	}
}
