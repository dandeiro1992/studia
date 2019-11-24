#include <math.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


string binarnie(long long int liczba);
long long int obliczcrc (string nazwa_pliku_wejsciowego, ifstream &plik_odczyt,string nazwa_pliku_wejsciowego1);
void view (long long int result, ofstream &plik_zapis, string nazwa_pliku_wejsciowego);

int main (int argc, char *argv[]){
	
	string nazwa_pliku_wejsciowego;
	
	ifstream plik_odczyt;
	ofstream plik_zapis;
	
	if (argc<2)
	{
		cout << "Nie podales parametru wejsciowego!" << endl;
		return -1;
	}

	nazwa_pliku_wejsciowego = argv[1];
	long long int result;
	
	result =obliczcrc(nazwa_pliku_wejsciowego, plik_odczyt,nazwa_pliku_wejsciowego);
	view (result,plik_zapis,nazwa_pliku_wejsciowego);
	cout<< "Koniec dzialania programu! CRC obliczone."<<endl;

	return 0;
}

//przedstawmy liczbe w postaci dwójkowej
string binarnie(long long int liczba){
	string bin="";
	long long int c=2147483648LL; //=2^31
	while (c>0) 
	{
		if ((liczba/c)==0) bin=bin+"0";
			else bin=bin+"1";
			
		liczba=liczba%c;
		c=c/2;
		
	} return bin;
}

void view (long long int result, ofstream &plik_zapis, string nazwa_pliku_wejsciowego){
    plik_zapis.open((nazwa_pliku_wejsciowego+".crc32").c_str());
    //crc w systemie binarnym (4bajty 8bitowe)
	plik_zapis<<(dec)<<(char)strtol((binarnie(result).substr(0,8)).c_str(),0,2)<<(char)strtol((binarnie(result).substr(8,8)).c_str(),0,2)<<(char)strtol((binarnie(result).substr(16,8)).c_str(),0,2)<<(char)strtol((binarnie(result).substr(24,8)).c_str(),0,2)<<endl;
   	//crc w systemie dwójkowym;
	plik_zapis<<binarnie(result)<<endl;
    //crc w systemie heksadecymalnym
	plik_zapis<<(hex)<<result<<endl;
	//crc w systemie dziesietnym
    plik_zapis<<(dec)<<result<<endl;

	plik_zapis.close();
     
     }

long long int obliczcrc (string nazwa_pliku_wejsciowego, ifstream &plik_odczyt,string nazwa_pliku_wejsciowego1){
	string tekst;
	int a,h=0;	
	long long int result=0;
	long long unsigned int d=4374732215LL;
	long long int buffer=0,k=0,w=d,wynik,i=0,z;	
	
	plik_odczyt.open(nazwa_pliku_wejsciowego1.c_str(),ios::binary);
	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku!" << endl;
		return -1;
	}
	
	cout<< "Obliczam CRC!"<<endl;

while (plik_odczyt.good()){
	a= plik_odczyt.get();
	if (!plik_odczyt.good()) {result=result<<8;h=4; } else {
	result=result<<8;	
	result+=a;}
	
do {if ((result>d)||(h==1)){

	while(result>4294967295LL){
	buffer =result;
	while (buffer>8589934591LL){
		i++;
		buffer = buffer>>1;

		}

	z=buffer<<i;
	result=z^result;
	wynik= buffer^d;
	wynik=wynik<<i;
	wynik=wynik|result;
	result=wynik; i=0;

	}
}

	if (h>1){result=result<<8;} h--;}while(h>0);
}

	plik_odczyt.close();

return result;
}

