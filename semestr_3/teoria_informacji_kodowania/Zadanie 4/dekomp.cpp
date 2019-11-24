#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;
struct tl { int znak; string kod; tl *next;}*head=NULL;

string nabir(int liczba){
	string bin=""; int c=128;
	while (c>0) {if ((liczba/c)==0) bin=bin+"0"; else bin=bin+"1"; liczba=liczba%c; c=c/2;
		
	} return bin;
}
tl *dod (tl *head, int s, string k){
	tl*x = new tl; tl*z=head;
x->next=NULL;
         x->znak=s; x->kod=k; if (head){while (z->next)z=z->next;
         
   z->next=x; } else head=x;
		
		return head;}
		void przeg (tl*head,ifstream &plik_odczyt,string nazwa_pliku_wejsciowego1,ofstream &plik_zapis){
			plik_odczyt.open(nazwa_pliku_wejsciowego1.c_str(), ios::binary);
				size_t position = nazwa_pliku_wejsciowego1.find(".");
	string extractName="x";
if (position< nazwa_pliku_wejsciowego1.length())extractName = nazwa_pliku_wejsciowego1.substr(0,position);

plik_zapis.open((extractName+".dhuff").c_str(), ios::binary);
	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku odczytywanego w trybie tekstowym!" << endl;
	
	}
	string dat="",x="",y="";
	int as=(int)plik_odczyt.get();
	
		
		x=nabir((int)plik_odczyt.get());

	
	dat+=x;
	
		tl*z=head; 
	string f=dat; int s=0,w=0,q=0;
	while (f.length()>0){
	while ((s==0)&&(z)){
	
if (f.length()<=z->kod.length()){
dat=y; y=nabir((int)plik_odczyt.get());  
if ( plik_odczyt.good())f+=dat; 
else
{
if (w==0){ w++;if (as!=0)f+=dat.substr(0,as);else f+=dat;break;}
} 
}	 
if ((f.substr(0,z->kod.length())== z->kod))
{ s=1; f=f.substr(z->kod.length()); 
plik_zapis.put(z->znak); }
else 
z=z->next;
} z=head; s=0;
if (plik_odczyt.good()){
dat=y; y=nabir((int)plik_odczyt.get()); 
if ( plik_odczyt.good())f+=dat; 
else
{
if (w==0){ w++;
if (as!=0)f+=dat.substr(0,as);
else f+=dat;}
}
}
}
	plik_odczyt.close(); plik_zapis.close();} 
	

int Zadanie1(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt,string nazwa_pliku_wejsciowego1,ifstream &plik_odczyt1,ofstream &plik_zapis)
{
	
	string tekst,tekst1;

	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str());

	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku odczytywanego w trybie tekstowym!" << endl;
		return -1;
	}


		
	
		while (true)
	{
		
	
	
		plik_odczyt>>tekst; 	plik_odczyt>>tekst1;
		if (!plik_odczyt.good()) break;
		
        
	head=	dod(head,atoi(tekst.c_str()),tekst1);
		
	}
	plik_odczyt.close();		
		cout << "Utworzono liste dynamiczna."<< endl;
przeg(head,plik_odczyt1,nazwa_pliku_wejsciowego1,plik_zapis);
	
	cout<<"Zdekompresowano plik i zapisano plik z rozszerzeniem .dhuff"<<endl;



	

	
	return 0;
}
int szukaj (string h)
{int s=0;

}




int main(int argc, char *argv[])
{


	string nazwa_pliku_wejsciowego;

	
	ifstream plik_odczyt;
	ifstream plik_odczyt1;
	ofstream plik_zapis;
	
	int RetCode;
	
	if (argc<3)
	{
		cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
		return -1;
	}


	nazwa_pliku_wejsciowego = argv[1];
string  nazwa_pliku_wejsciowego1 = argv[2];
	size_t position = nazwa_pliku_wejsciowego.find(".");
	string extractName="x";
if (position< nazwa_pliku_wejsciowego.length())extractName = nazwa_pliku_wejsciowego.substr(position);

cout <<"Otwierany plik: "<<nazwa_pliku_wejsciowego<<endl;

	RetCode = Zadanie1(nazwa_pliku_wejsciowego, plik_odczyt,nazwa_pliku_wejsciowego1, plik_odczyt1,plik_zapis);

	if (RetCode==-1)
		return -1;

	cout << "Zapisano pliki wyjsciowe."<< endl;


		return 0;
}
