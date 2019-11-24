#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <cmath>
#include <cstdlib>
const int n=100;
void shell(int *tab, int n);
void shellmal(int *tab, int n);
int main ()
{
	int h;
	int tablica1[n];
		srand(time(NULL));
	for(int i=0; i<n ; i++)
		tablica1[i]=rand() % 100;

	for(int i=0; i<n ; i++)
		printf("%d  ",tablica1[i]);
		printf("\n");
		
	
		shellmal(tablica1,n);
		
	printf("\n");
	for(int i=0; i<n ; i++)
		printf("%d  ",tablica1[i]);
		printf("\n");
		
		
	getche();
	return 0;
}
void shell(int *tab, int n)
{
	int h;
	for (h=1;h<n;h=3*h+1);
		h/=9;
		if (!h) h++;
	while (h)
	{
		for (int j=n-h-1;j>=0;j--)
		{
			int x=tab[j];
			int i=j+h;
			while (i<n && x>tab[i])
			{
				tab[i-h]=tab[i];
				i+=h;
			}
			tab[i-h]=x;
		}
		h/=3;
	}	
}

void shellmal(int *tab, int n)
{
	int h;
	for (h=1;h<n;h=3*h+1);
		h/=9;
		if (!h) h++;
	while (h)
	{
		for (int j=n-h-1;j>=0;j--)
		{
			int x=tab[j];
			int i=j+h;
			while (i<n && x<tab[i])
			{
				tab[i-h]=tab[i];
				i+=h;
			}
			tab[i-h]=x;
		}
		h/=3;
	}	
}
