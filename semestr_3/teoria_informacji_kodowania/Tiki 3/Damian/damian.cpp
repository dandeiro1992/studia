#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

struct lista
{
	int symbol;
	string c;
	lista *next, *prev;
	
} *head=NULL, *x=NULL;

lista *szukanie (lista *head, char bajt_8)
{
	while(head)
	{
		if(head->symbol==(int)bajt_8) return head;
		else head=head->next;
	}
}

lista *dodaj (lista* head, int znak, string a)
{
	
	lista* nowy;
	nowy= new lista;
	if (head) head->prev=nowy;
	nowy->c=a;
	nowy->symbol=znak;
	nowy->next=head;

	head=nowy;
	
	return head;

}

void wypisz (lista *head)
{
	while(head) {
		cout << head->symbol << " " << head->c << endl;
		 head=head->next;
	}
}

int kompresja (string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	char bajt_8;
lista *szukany;
string pobierany="000";
string wycinany="";
long long int gotowy;
char *nieudany;
int licznik_zapis;
int dodany;
int dlugosc_stringa;

	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);
		plik_zapis.open((nazwa_pliku_wejsciowego+".huff").c_str(), ios::binary | ios::out);
		while (1)
	{
	bajt_8=plik_odczyt.get();
	if(!plik_odczyt.good()) break;
	szukany=szukanie (head, bajt_8);

	if (pobierany.size() <8)
	{
	pobierany=pobierany+szukany->c;
	}
	if (pobierany.size() >=8)
	{	
	pobierany=pobierany+szukany->c;
	wycinany=pobierany.substr(0,8);
	//konwersja na long long int
	gotowy=strtol(wycinany.c_str(), &nieudany, 2);
	plik_zapis.put(gotowy);
	
	pobierany=pobierany.substr(8);
			
	}	 
	}
	int k=0;
	dlugosc_stringa=pobierany.size();
	if(pobierany.size()==0) return 0;
	else while (!pobierany.size()==8) {
	pobierany=pobierany+"1";
	dodany++;
	k++;
	}
	
	gotowy=strtol(pobierany.c_str(), &nieudany, 2);
	pobierany="";
	
	unsigned char liczba;
	liczba= k*32;
	//string tmp;
	//tmp[0]=liczba;
		//pobierany=tmp+pobierany;
	
	
	plik_zapis.put(gotowy);
	plik_zapis<<dodany<<endl;
	plik_zapis.close();
	plik_odczyt.close();
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);
	unsigned char d=plik_odczyt.get();
	plik_odczyt.close();
	plik_zapis.open((nazwa_pliku_wejsciowego+".huff").c_str(),ios::binary| ios::app);
	plik_zapis.seekp(0, ios_base::beg);
	d=d+liczba;
	plik_zapis.put(d);
	plik_zapis.close();
	
	
	return 0;
	
	
} 



int main(int argc, char *argv[])
{
	string nazwa_code;
	string nazwa_pliku_wejsciowego;

	ifstream plik_odczyt;
	ofstream plik_zapis;

	nazwa_code=argv[1];
	nazwa_pliku_wejsciowego=argv[2];
	
	plik_odczyt.open(nazwa_code.c_str(), ios::in);
	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku odczytywanego w tabelki kodowej!" << endl;
		return -1;
	}
int symbol1;
string kod;
	while (1)
{
	
	plik_odczyt >> symbol1;
	if (!plik_odczyt.good()) break;
	plik_odczyt >> kod;
 	head=dodaj (head, symbol1, kod);
}

plik_odczyt.close();
kompresja (nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);


return 0;
	
		
}
