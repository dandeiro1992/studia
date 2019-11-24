#include "counter.h"
#include <stdio.h>

Counter::Counter(unsigned long long  int len0,bool dodano_nowy_blok)
{
	unsigned long long int ileblokow0=len0/512;
	if(len0%512!=0)
		ileblokow0++;
	
	if (dodano_nowy_blok)
		ileblokow=ileblokow0+1;
	else
		ileblokow=ileblokow0;
	
	L=new unsigned long  long int [ileblokow];
	unsigned long  long int i;
	for (i=0;i<(len0/512);i++)
		L[i]=512*(i+1);
	if(len0%512==0)
	L[i]=0;
	else
	L[i]=len0;
	i++;
	if (i<ileblokow)
	L[i]=0;
	
	printf("tablica L: \n");
	
	for (i=0;i<ileblokow;i++)
	printf("%lld ",L[i]);
	printf("\n ");
	
}

Counter::~Counter()
{
	//delete [] L;
}

unsigned int* Counter::operator[] (unsigned long long int indeks)
{ 
	 unsigned long long int c64 = L[indeks];
	 unsigned int* t = new unsigned int [2];
	 t[0]=(unsigned int)((c64<<32)>>32);
	 t[1]=(unsigned int)(c64>>32);
	 
	printf("operator [] zwraca %d, 	%d\n",t[0], t[1]);
	 	
	return t;
}
