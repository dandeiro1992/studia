#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <cmath>
#include <bitset>
using namespace std;
struct tl { int znak; string kod; tl*next;}*head=NULL;

int Zadanie1(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt)
{
	
	string tekst;

	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str());

	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku odczytywanego w trybie tekstowym!" << endl;
		return -1;
	}


		tl*x;
		while (true)
	{
		
		plik_odczyt >> tekst;
	
	
		if (!plik_odczyt.good()) break;
		
	
		
x = new tl;
         x->znak=atoi(tekst.c_str());
        
		
		

		
			plik_odczyt >> tekst;
	
		 x->kod=tekst;
          x->next=NULL;
         
          if (head) {
                    x->next = head;
          }  head=x; 
		
		
	}
			

	plik_odczyt.close();
	cout << "Utworzono liste dynamiczna."<< endl;


	

	
	return 0;
}
 string szukaj (tl*head,int znak) {
          	while((head)&&(head->znak !=znak)){
          		head=head->next;
          	}
          	if (head) return head->kod; else return ""; 
          
          }
int Zadanie2(string nazwa_pliku_wejsciowego1, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	unsigned char bajt_8b;
	
	
	plik_odczyt.open(nazwa_pliku_wejsciowego1.c_str(), ios::binary);


	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku odczytywanego w trybie binarnym!" << endl;
		return -1;
	}
	

	size_t poz = nazwa_pliku_wejsciowego1.find(".");
string nazwa = nazwa_pliku_wejsciowego1.substr(0, poz)+".huff";
	plik_zapis.open(nazwa.c_str(), ios::binary);
	 

	if (!plik_zapis.is_open())
	{
		cout << "Blad otwierania pliku do zapisu w trybie binarnym!" << endl;
		return -1;
	}
string dat=""; int f,w=0,g;
plik_zapis.put(0);
	while (true)
	{ 
		   
		bajt_8b=plik_odczyt.get();
		
		
		if (!plik_odczyt.good()) break;
                                       
dat= dat+szukaj (head,int(bajt_8b));
while (dat.length()>7){
while (w*8+7<dat.length()){

f=strtol(dat.substr(w*8,8).c_str(), 0, 2);


plik_zapis.put(f);
w++;
dat=dat.substr(w*8);

}
w=0;


}
	}
	cout << "Przetworzono pliki wejsciowe."<< endl;
	 g=dat.length();
	if (g>0) {for (int i=0; i<8-g;i++){
	dat=dat+"0";
}
	f=strtol(dat.c_str(), 0, 2);
	plik_zapis.put(f);
	
}

  plik_zapis.seekp (0);
plik_zapis.put(g);


	plik_odczyt.close();

	plik_zapis.close();
	
}

int main(int argc, char *argv[])
{


	string nazwa_pliku_wejsciowego;
	string nazwa_pliku_wejsciowego1;
	
	ifstream plik_odczyt,plik_odczyt1;
	ofstream plik_zapis;
	
	int RetCode;
	
	if (argc<3)
	{
		cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
		return -1;
	}


	nazwa_pliku_wejsciowego = argv[1];
	nazwa_pliku_wejsciowego1 = argv[2];
	size_t position = nazwa_pliku_wejsciowego.find(".");

cout <<"Otwierane pliki: "<<nazwa_pliku_wejsciowego<<" oraz "<<nazwa_pliku_wejsciowego1<<endl;

	RetCode = Zadanie1(nazwa_pliku_wejsciowego, plik_odczyt);
 Zadanie2(nazwa_pliku_wejsciowego1, plik_odczyt1,plik_zapis);
	if (RetCode==-1)
		return -1;

	cout << "Zapisano plik wyjsciowy."<< endl;


		return 0;
}
