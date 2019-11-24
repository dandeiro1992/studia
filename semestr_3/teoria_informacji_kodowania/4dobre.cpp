#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
int const rozmiar=256;

struct tk
{
	int symbol;
	string kod;
};

int dodaj(string nazwa_code, tk tablica[], int rozmiar, ifstream &plik_odczyt);
void czyszczenie (tk tablica[], int rozmiar);
int szukaj (tk tablica[], int rozmiar2, string liczba_binarna);
string binarnie (int liczba);
void dekompresja (tk tablica[], int rozmiar2, string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis);

int main(int argc, char *argv[])
{
	int rozmiar2;
	tk tablica[rozmiar];
	string nazwa_code;
	string nazwa_pliku_wejsciowego;

	ifstream plik_odczyt;
	ofstream plik_zapis;

	nazwa_code=argv[1];
	nazwa_pliku_wejsciowego=argv[2];
	
	if (argc<3)
	{
		cout<<"Nieprawidlowa liczba parametrow wejsciowych"<<endl;
		return -1;
	}
	
	rozmiar2=dodaj (nazwa_code, tablica, rozmiar, plik_odczyt);
	dekompresja (tablica, rozmiar2, nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);
	cout<<"Koniec dzialania programu! Plik zdekompresowany! "<< endl;

	return 0;
}

int dodaj(string nazwa_code, tk tablica[], int rozmiar, ifstream &plik_odczyt)
{
	
	int bajt_8;
	string k;
	plik_odczyt.open(nazwa_code.c_str(), ios::in);
	int i=0;
	czyszczenie (tablica, rozmiar);
	while (1)
	{
	
	plik_odczyt>>bajt_8;	
	if(!plik_odczyt.good()) break;
	plik_odczyt>>k;
	tablica[i].symbol=bajt_8;
	tablica[i].kod=k;
	i++	;
	}
	
	cout<<"Stworzono tablice kodowa na podstawie pliku o rozszerzeniu .code" << endl;	
	
	plik_odczyt.close();
	return i++;
}

int szukaj (tk tablica[], int rozmiar2, string liczba_binarna)
{
	for (int i=0; i<rozmiar2; i++)
	{
		if(tablica[i].kod==liczba_binarna) return tablica[i].symbol;
	}
	return -1;
}

void czyszczenie (tk tablica[], int rozmiar)
{
	for (int i=0; i<rozmiar; i++)
	{
		tablica[i].symbol=0;
		tablica[i].kod="";
	}
}

string binarnie (int liczba)
{
	int i=0, tab[31];
	string bin="";
	while(liczba)
	{
		tab[i++]=liczba%2;
		liczba/=2;
	}
	
	//tablica char->string
	for (int j=i-1; j>=0; j--)
	{
		if (tab[j]==1) bin +="1";
		else bin+="0";
	}
	while (bin.length()<8) bin="0" + bin;
	return bin;
}

void dekompresja (tk tablica[], int rozmiar2, string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	cout<< "Trwa dekompresja!" << endl;
	char c;
	int temp,temp1;
	string bajt_8b;
	string kodowo="";
	int dlugosc;
	int wyciecie;
	int znaleziony;
	
	plik_zapis.open((nazwa_pliku_wejsciowego+".dhuff").c_str());
	
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str());
	
	temp1=plik_odczyt.get();
	int i=0,j=0;
	while (plik_odczyt.get(c)) i++;
	plik_odczyt.close();
	
	temp1=plik_odczyt.get();
	
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str());
	temp1=plik_odczyt.get();
	while (plik_odczyt.get(c))
	{
		bajt_8b=binarnie((unsigned char)c);
		if(j==i-1) bajt_8b.erase(bajt_8b.length()-temp1-6, 14-temp1);
		bajt_8b=kodowo+bajt_8b;
		dlugosc=bajt_8b.size();
		wyciecie=1;
		while(wyciecie<=dlugosc)
		{
			kodowo=bajt_8b.substr(0,wyciecie);
			znaleziony=szukaj(tablica, rozmiar2, kodowo);
			if(znaleziony>=0)
			{
				plik_zapis<< (unsigned char)znaleziony;
				bajt_8b.erase(0, wyciecie);
				wyciecie=0;
			}
			wyciecie++;
		}
		kodowo=bajt_8b;
		j++;
	}
	
	cout<< "Dekompresja zakoñczona!" << endl;
	plik_zapis.close();
}
