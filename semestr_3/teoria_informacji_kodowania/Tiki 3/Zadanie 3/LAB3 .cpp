#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>


using namespace std;

struct model{
	short znak;
	string zastepczy;
}tab[256];


char* nazwa(char* tekst, string temp)
{
    int i=0;
    bool usun=false;
    while(tekst[i])
    {
        if(usun) tekst[i]=0;
        if(tekst[i]=='.') usun=true;
        i++;
    }
    char* rozszerzenie = strdup(temp.c_str());
    strcat(tekst,rozszerzenie);
    return tekst;
}


void odczyt_code(char* plik)
{
fstream odczyt;
odczyt.open(plik, ios::in);
int i=0;
while(odczyt.good())
{
short znak=-1;
string zastepczy;
odczyt>>znak;
odczyt>>zastepczy;
if(znak==-1) break;
tab[i].znak=znak;
tab[i].zastepczy=zastepczy;
i++;
}
cout<<"Odczytano code"<<endl;
odczyt.close();
}


unsigned char huff(char* plik)
{
fstream odczyt;
odczyt.open(plik, ios::in | ios::binary);
string bufor="";
fstream zapis;
zapis.open(nazwa(plik,"huff"),ios::out | ios::binary);
zapis.put(0);
cout<<"Rozpoczynam odzytywanie pliku...."<<endl;
while(odczyt.good())
{
	int z=-1;
	short k=odczyt.get();
	if(k==-1)break;
	while(tab[++z].znak!=k);
	bufor=bufor+tab[z].zastepczy;
	if(bufor.length()>=8)

	{
		string nowy=bufor.substr(0,8);
		bufor.erase(0,8);
		unsigned char bajt=strtol(nowy.c_str(),NULL,2);
		zapis.put(bajt);
    }


}
cout<<"Odczytano caly plik"<<endl;
short ostatni=bufor.length();
while(bufor.length()<8) bufor=bufor+"0";
unsigned char bajt=strtol(bufor.c_str(),NULL,2);
zapis.put(bajt);
zapis.seekg(0,ios::beg);
zapis.put(ostatni);
odczyt.close();
zapis.close();
cout<<"Utworzono huff"<<endl;
}

int main(int argc, char *argv[])
{

if (argc<3)
{
	cout << "Nie podano nazwy 2 plików jako parametru wejsciowego!" << endl;
	return -1;
}

for(int i=1;i<=2;i++)
{
fstream file;
file.open(argv[i],ios::in);
if (!file.good())
{
	cout<<"Podano zla nazwe "<<i<<" pliku!"<<endl;
	return -1;
}
file.close();
}

odczyt_code(argv[1]);

huff(argv[2]);


    return EXIT_SUCCESS;
}

