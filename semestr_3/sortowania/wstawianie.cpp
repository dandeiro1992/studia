#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <cmath>
#include <cstdlib>
const int n=100;
void wstawianie(int *tab, int n);
void wstawianiemal(int *tab, int n);
int main ()
{
	int tablica1[n];
		srand(time(NULL));
	for(int i=0; i<n ; i++)
		tablica1[i]=rand() % 100;

	for(int i=0; i<n ; i++)
		printf("%d  ",tablica1[i]);
		printf("\n");

	wstawianiemal(tablica1,n);
	printf("\n");
	for(int i=0; i<n ; i++)
		printf("%d  ",tablica1[i]);
		printf("\n");
		
		wstawianie(tablica1,n);
	printf("\n");
	for(int i=0; i<n ; i++)
		printf("%d  ",tablica1[i]);
		printf("\n");
		
		
	getche();
	return 0;
}

void wstawianie(int *tab, int n)
{
	for (int j=n-2;j>=0;j--)
	{
		int x=tab[j];
		int i=j+1;
		while (i<n && x>tab[i])
		{
			tab[i-1]=tab[i];
			i++;
		}
		tab[i-1]=x;
	}
}
void wstawianiemal(int *tab, int n)
{
	for (int j=1;j<=n-1;j++)
	{
		int x=tab[j];
		int i=j-1;
		while (i>=0 && x>tab[i])
		{
			tab[i+1]=tab[i];
			i--;
		}
		tab[i+1]=x;
	}
}
