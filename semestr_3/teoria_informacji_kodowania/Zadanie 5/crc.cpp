#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
string nabir(long long int liczba){
	string bin=""; long long int c=2147483648LL;
	while (c>0) {if ((liczba/c)==0) bin=bin+"0"; else bin=bin+"1"; liczba=liczba%c; c=c/2;
		
	} return bin;
}
void wypisz (long long int s,ofstream &plik_zapis,string nazwa_pliku_wejsciowego){
     	plik_zapis.open((nazwa_pliku_wejsciowego+".crc32").c_str());
     plik_zapis<<(char)strtol((nabir(s).substr(0,8)).c_str(),0,2)<<(char)strtol((nabir(s).substr(8,8)).c_str(),0,2)<<(char)strtol((nabir(s).substr(16,8)).c_str(),0,2)<<(char)strtol((nabir(s).substr(24,8)).c_str(),0,2)<<endl<<nabir(s)<<endl<<(hex)<<s<<endl<<(dec)<<s;

	plik_zapis.close();
     
     }
long long int oblcrc (string nazwa_pliku_wejsciowego, ifstream &plik_odczyt,string nazwa_pliku_wejsciowego1){
	
	
		string tekst;

	plik_odczyt.open(nazwa_pliku_wejsciowego1.c_str(),ios::binary);

	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku odczytywanego w trybie tekstowym!" << endl;
		return -1;
	}

long long int s=0;
int x,h=0;
long long unsigned int d=4374732215LL,bufor=0,k=0,w=d,wynik,i=0,z;
while (plik_odczyt.good()){
	x= plik_odczyt.get();
	if (!plik_odczyt.good()) {s=s<<8;h=4; } else {
	s=s<<8;	
	s+=x;}
do {if ((s>d)||(h==1)){

	while(s>4294967295LL){
bufor =s;
while (bufor>8589934591LL){
	i++;
bufor = bufor>>1;

}

z=bufor<<i;
s=z^s;
wynik= bufor^d;
wynik=wynik<<i;
wynik=wynik|s;
s=wynik; i=0;

}
}if (h>1){s=s<<8;} h--;}while(h>0);
}

	plik_odczyt.close();




return s;
}
int main (int argc, char *argv[]){
	string nazwa_pliku_wejsciowego;
	
	ifstream plik_odczyt;
	ofstream plik_zapis;
	
	long long int s;
	
	if (argc<2)
	{
		cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
		return -1;
	}


	nazwa_pliku_wejsciowego = argv[1];

	size_t position = nazwa_pliku_wejsciowego.find(".");

cout <<"Otwierane pliki: "<<nazwa_pliku_wejsciowego<<" oraz "<<endl;

	s =oblcrc(nazwa_pliku_wejsciowego, plik_odczyt,nazwa_pliku_wejsciowego);
	wypisz (s,plik_zapis,nazwa_pliku_wejsciowego);

	return 0;
}
