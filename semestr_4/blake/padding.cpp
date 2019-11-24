#include "padding.h"
#include <iostream>
#include <string.h>
using namespace std;

Padding::Padding (char* msg0)
{
	this->msg0=msg0;
	
}
void Padding::wyswietl()
{
	cout<<"message after padding :\n";
	for (unsigned long long int i=0;i<strlen(msgpad);i++)
	{
		cout<<msgpad[i];
		if (i%8==7)
			cout<<" ";
	}
	cout<<"\n"<<msgpad<<endl;
	cout<<"msgpadsize= "<<msgpadsize<<endl;
}

char* Padding::getmsgpad()
{
	return msgpad;
}

Padding::~Padding()
{
	delete [] msgpad;
}

void Padding::padmsg()
{
	unsigned long long int len0=strlen(msg0)*4;//len0 w bitach
	unsigned long long int lastblocklen=len0%512;
	unsigned long long int dopelnienie;
	if ((lastblocklen+66<=512)&&(lastblocklen>0))
	{
		//zmiescie siê w tym bloku nie dodajemy nowego 
		dopelnienie =512-lastblocklen;	
		dodano_nowy_blok=false;
	}
	else
	{
		//dodajemy kolejny blok rozmairu 512
		if(lastblocklen>0)
			dopelnienie=512+512-lastblocklen;
		else
			dopelnienie=512;	
			
		dodano_nowy_blok=true;	
	}
	msgpadsize=len0+dopelnienie;
	//msgpadsize w bitach
	msgpad=new char[msgpadsize/4+1];
	unsigned long long int i;
	for (i=0;i<strlen(msg0);i++)
	{
		msgpad[i]=msg0[i];
	}
	unsigned long long int ilosczer=dopelnienie-66;
	//dodawanie 1 0000.. 1
	if (ilosczer==6)
	{
		//tworzy jedna liczbe
		msgpad[i]='8';
		i++;
		msgpad[i]='1';
		i++;
	}
	else
	{
		msgpad[i]='8';
		i++;
		msgpad[i]='0';
		i++;
		//srodkowe zera
		unsigned long long int srodkowezera=ilosczer-14;
		for (unsigned long long int j=0;j<(srodkowezera/4);j++)
		{
			msgpad[i]='0';
			i++;
		}
		msgpad[i]='0';
		i++;
		msgpad[i]='1';
		i++;
	}
	i=i+15;
	unsigned long long int a=len0;
	for (unsigned long long int m=0;m<16;m++)
	{
		int re=a%16;
		a=a/16;
		if (re<=9)
		{
			msgpad[i]='0'+re;
		}
		else
		{
			msgpad[i]='a'-10+re;	
		}
		i--;
	}
	msgpad[msgpadsize/4]='\0';
}


unsigned long long int Padding::getlen0()
{
	return strlen(msg0)*4;
}

bool Padding::get_dodano_nowy_blok()
{
	return dodano_nowy_blok;
}
