//projekt sortowanie

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


const int n=100000;
const int m=100;
void babelkowe(int n,int *tab);
void babelkowep3(int n,int *tab);
void babelkowep4(int n,int *tab);

int main ()
{
	int tablica1[n];
		srand(time(NULL));
	for(int i=0; i<n ; i++)
		tablica1[i]=rand() % 100;

//	for(int i=0; i<n ; i++)
//		printf("%d  ",tablica1[i]);
//		printf("\n");
		
	clock_t start=clock();
	babelkowe(n,tablica1);
	printf("czas wykonywania: %lu s\n",(clock()-start)/CLOCKS_PER_SEC);
	
	
//	printf("\n");
//	for(int i=0; i<n ; i++)
//	printf("%d  ",tablica1[i]);
		
	
	
	
	clock_t drugie=clock();
	int tablica2[m];
		srand(time(NULL));
	for(int i=0; i<m ; i++)
		tablica2[i]=rand() % 100;
		
		for(int i=0; i<m ; i++)
		printf("%d  ",tablica2[i]);
		printf("\n");
		
	babelkowe(m,tablica2);
	
	printf("\n");
	for(int i=0; i<m ; i++)
	printf("%d  ",tablica2[i]);
	printf("czas wykonywania: %lu ms\n",clock()-drugie);
	
	babelkowep3(m,tablica2);
	printf("\n");
	for(int i=0; i<m ; i++)
	printf("%d  ",tablica2[i]);
	printf("\n");
	babelkowep4(m,tablica2);
	printf("\n");
	for(int i=0; i<m ; i++)
	printf("%d  ",tablica2[i]);
		getche ();
		return 0;
		
}
void babelkowe(int n,int *tab)
     {
		int p=0;
		int c=0;
		do
		{
			p=0;
			int i;
			for(i=0;i<n-1;i++)
			{
				if(tab[i]>tab[i+1])
				{
					c=tab[i];
					tab[i]=tab[i+1];
					tab[i+1]=c;
					p=1;
				}
				else{;}
			}
 		}
		while(p!=0);
     }
 void babelkowep3(int n,int *tab)
     {
		int p=0;
		int c=0;
		do
		{
			p=0;
			int i;
			for(i=0;i<n-1;i++)
			{
				if(tab[i]<tab[i+1])
				{
					c=tab[i];
					tab[i]=tab[i+1];
					tab[i+1]=c;
					p=1;
				}
				else{;}
			}
 		}
		while(p!=0);
     }
 void babelkowep4(int n,int *tab)
     {
     	int p=0;
		int c=0;
     	c=tab[17];
		tab[17]=tab[0];
		tab[0]=c;
		p=0;
		c=0;
		do
		{
			p=0;
			int i;
			for(i=1;i<n-1;i++)
			{
				if(tab[i]>tab[i+1])
				{
					c=tab[i];
					tab[i]=tab[i+1];
					tab[i+1]=c;
					p=1;
				}
				else{;}
			}
 		}
		while(p!=0);
     }
