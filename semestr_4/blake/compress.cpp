#include <iostream>
#include "constants.h"
#include <conio.h>
#include "operacje_podstawowe.h"
#include <stdio.h>
#include <string.h>
#include "padding.h"
#include "counter.h"
#include "compress.h"
using namespace std;

void Compress::init( unsigned int v[][4],unsigned int t[], unsigned int* hi)
{
	for (int i=0;i<2;i++)
	{
		for (int j=0;j<4;j++)
		{
			v[i][j]=hi[i*4+j];
		}
	}
	for(int j=0;j<4;j++)
	v[2][j]=salt[j]^tablica_const[j];
	v[3][0]=t[0]^tablica_const[4];
	v[3][1]=t[0]^tablica_const[5];
	v[3][2]=t[1]^tablica_const[6];
	v[3][3]=t[1]^tablica_const[7];
	
}

void Compress::wypisz_v (unsigned int v[][4])
{
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
			printf("%x ",v[i][j]);
		printf("\n");
	}
		
	printf("\n");
		
}

void Compress::funkcjaG(int i, unsigned int v[][4], unsigned int m[], int r) //pobiera numer indeksy 
{
	int i1, i2, i3, i4, i5, i6, i7, i8;
	switch(i)
	{
		case 0:
			i1=0; i2=0; i3=1; i4=0; i5=2; i6=0; i7=3; i8=0;
			break;
		case 1:
			i1=0; i2=1; i3=1; i4=1; i5=2; i6=1; i7=3; i8=1;
			break;
		case 2:
			i1=0; i2=2; i3=1; i4=2; i5=2; i6=2; i7=3; i8=2;
			break;
		case 3:
			i1=0; i2=3; i3=1; i4=3; i5=2; i6=3; i7=3; i8=3;
			break;
		case 4:
			i1=0; i2=0; i3=1; i4=1; i5=2; i6=2; i7=3; i8=3;
			break;
		case 5:
			i1=0; i2=1; i3=1; i4=2; i5=2; i6=3; i7=3; i8=0;
			break;
		case 6:
			i1=0; i2=2; i3=1; i4=3; i5=2; i6=0; i7=3; i8=1;
			break;
		case 7:
			i1=0; i2=3; i3=1; i4=0; i5=2; i6=1; i7=3; i8=2;
			break;
	}
		
	Operacje_podstawowe op;
	v[i1][i2]=v[i1][i2]+v[i3][i4]+(m[tablica_sigma[r%10][2*i]]^tablica_const[tablica_sigma[r%10][2*i+1]]);
	v[i7][i8]=op.rotright(v[i7][i8]^v[i1][i2], 16);
	v[i5][i6]=v[i5][i6]+v[i7][i8];
	v[i3][i4]=op.rotright(v[i3][i4]^v[i5][i6], 12);
	v[i1][i2]=v[i1][i2]+v[i3][i4]+(m[tablica_sigma[r%10][2*i+1]]^tablica_const[tablica_sigma[r%10][2*i]]);
	v[i7][i8]=op.rotright(v[i7][i8]^v[i1][i2], 8);
	v[i5][i6]=v[i5][i6]+v[i7][i8];
	v[i3][i4]=op.rotright(v[i3][i4]^v[i5][i6], 7);
}

void Compress::finalisation(unsigned int v[][4] ,unsigned int hi[], unsigned int hi1[])
{
	for (int i=0; i<8; i++)
	{
		hi1[i]=hi[i]^salt[i%4]^v[i/4][i%4]^v[(i/4)+2][i%4];
	}
}


unsigned int * Compress::compress( unsigned int m[], unsigned int *hi, unsigned int *t)
{
	
	unsigned int v[4][4];
	printf ("t0 =%d, t1= %d\n", t[0],t[1]);
	init(v, t, hi);
	wypisz_v(v);
	for (int r=0;r<14;r++)
	{
		funkcjaG(0,v,m,r);
		//wypisz_v(v);
		funkcjaG(1,v,m,r);
		//wypisz_v(v);
		funkcjaG(2,v,m,r);
		//wypisz_v(v);
		funkcjaG(3,v,m,r);
		funkcjaG(4,v,m,r);
		funkcjaG(5,v,m,r);
		funkcjaG(6,v,m,r);
		funkcjaG(7,v,m,r);
		cout<<"po rundzie nr "<<r<<":"<<endl;
		wypisz_v(v);
	}
	//nowa tablica
	unsigned int *hi1 = new unsigned int [8];
	
	finalisation(v,hi,hi1);
	wypiszhi1(hi1);
	return hi1;

}

void Compress::wypiszhi1(unsigned int hi1[])
{
	printf ("h(i+1) wynosi: \n");
	for (int i=0;i<8;i++)
		printf("%08x ", hi1[i]);
	printf("\n");
}

