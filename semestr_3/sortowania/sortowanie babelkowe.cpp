#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// sortowanie babelkowe 
 
void wyswietl(int n,int a[])
     {
        int i;
		for(i=0;i<n;i++)
		{
			printf("%i",a[i]);
			printf("\n");
 		}
     }  
      getche()
      return 0;
}
void sort(int n,int a[])
     {
		int p=0;
		int c=0;
		do
		{
			p=0;
			int i;
			for(i=0;i<n-1;i++)
			{
				if(a[i]>a[i+1])
				{
					c=a[i];
					a[i]=a[i+1];
					a[i+1]=c;
					p=1;
				}
				else{;}
			}
 		}
		while(p!=0);
     }
 
