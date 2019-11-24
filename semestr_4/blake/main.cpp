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


int chartohex(char znak)
{
	if ((znak<='9')&&(znak>='0'))
	return znak-48;
	else if ((znak<='Z')&&(znak>='A'))
	return znak-65+10;
	else 
	return znak-97+10;
}
void bloki_msg(char* msg, Counter licznik)
{
	unsigned int h0[8]={0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A, 0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19};
	unsigned int* hi = h0;
	unsigned long long int ilem=0;
	for (unsigned long long int b=0;b<strlen(msg);b+=128)//b oznacza iloœæ wpisanych znaków
	{
		unsigned int m[16];
		for (int i=0;i<16;i++)
		{
				int poczmi=b+8*i;
				//tworz¹ liczbê v 
				int z=poczmi;
				unsigned int lit1=(chartohex(msg[z]))*16+(chartohex(msg[z+1]));
				lit1=lit1<<3*8;
				unsigned int lit2=(chartohex(msg[z+2]))*16+(chartohex(msg[z+3]));
				lit2=lit2<<2*8;
				unsigned int lit3=(chartohex(msg[z+4]))*16+(chartohex(msg[z+5]));
				lit3=lit3<<1*8;
				unsigned int lit4=(chartohex(msg[z+6]))*16+(chartohex(msg[z+7]));
				unsigned int v=lit1|lit2|lit3|lit4;
				m[i]=v;
				cout<<"b="<<b<<" i="<<i<<" m[i]="<<m[i]<<endl;
		}
		
		//unsigned int m2[16]={0x00800000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000001,0x00000000,0x00000008};
		Compress comp;
		hi = comp.compress (m, hi, licznik[ilem]); 
		//delete [] hi;
		ilem++;
	}
	cout<<"message length= "<<ilem*512<<endl;
}


int main(int argc, char** argv) {
	char* msg0=argv[1];
	Padding pad(msg0);
	pad.padmsg();
	pad.wyswietl();
	Counter licznik (pad.getlen0(),pad.get_dodano_nowy_blok());
	bloki_msg (pad.getmsgpad() , licznik);
	
	return 0;
}


