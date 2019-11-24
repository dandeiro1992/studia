#include <conio.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <ostream>
#include<iomanip>
using namespace std;

string tabk[256];	
	ifstream plik_odczyt;
	ofstream plik_zapis;
	
	string binarnie (long long int liczba)
{
	int i=0, tab[32];
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
	while (bin.length()<32) bin="0" + bin;
	return bin;
}

// *********** Zadanie 5 - obliczamy CRC *********** //

void view (long long int result){
      
	//crc w systemie binarnym (4bajty 8bitowe)
	plik_zapis<<(dec)<<(char)strtol((binarnie(result).substr(0,8)).c_str(),0,2)<<(char)strtol((binarnie(result).substr(8,8)).c_str(),0,2)<<(char)strtol((binarnie(result).substr(16,8)).c_str(),0,2)<<(char)strtol((binarnie(result).substr(24,8)).c_str(),0,2);
 
}

long long int obliczcrc (){
	string tekst;
	int a,h=0;	
		
	long long int	pos=1<<30, pos1=1<<30;
	pos=pos<<2; pos1=pos1<<3;

	long long int result=0;
	long long unsigned int d=4374732215LL;//wielomian
	long long int buffer=0,k=0,w=d,wynik,i=0,z;	
	
	cout<< "Rozpoczynam obliczanie CRC!"<<endl;

while (plik_odczyt.good()){
	a= plik_odczyt.get();
	if (!plik_odczyt.good()) {result=result<<8;h=4; } else {
	result=result<<8;	
	result+=a;}


do {if ((result>d)||(h==1)){

	while(result >=pos){
	buffer =result;
	while (buffer >=pos1){
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

return result;
}


// -------------------------------------------- KOMPRESJA ----------------------------------------------- //

// *********** Zadanie 1 i 2 - tworzymy model Ÿród³ówy oraz tabele kodowa *********** //

const int k=256;

struct zrodlo{
        int czestosc,znak;
        string kod;
        };
struct zrodlo t[k];

int compare (const void * a, const void * b)
{
	 zrodlo* arg1 = (zrodlo*) a;
     zrodlo* arg2 = (zrodlo*) b;
     if( arg1->czestosc < arg2->czestosc ) return 1;
     else if(( arg1->czestosc == arg2->czestosc )&&(arg1->znak > arg2->znak))return 1;
     else return -1;
     
 
}
 
 
int rpw=0; int iterator1;
int ile_bajtow(void)
{
	unsigned char bajt_8b;
	int iterator=0;
	cout << "Zaczynam tworzenie modelu zrodlowego informacji."<<endl;

	while (true)
	{
	
		//pobranie jednego bajta 8b z pliku odczytywanego
		bajt_8b=plik_odczyt.get();
	
		if (plik_odczyt.eof()) break; rpw++;	
		
		if ((	t[bajt_8b].znak!=bajt_8b) ||(t[bajt_8b].czestosc<1)){	t[bajt_8b].znak=bajt_8b; iterator++;}
		t[bajt_8b].czestosc++;
	}
	
	if (iterator<0 || iterator>256) {cout << "Wystapil blad w tworzeniu modelu zdrodlowego informacji." <<endl; return -1;}
	
	cout << "Alfabet wejsciowy liczy "<< iterator <<" symboli." <<endl;	
	iterator1=iterator;
	plik_zapis.put(iterator-1);

qsort (t, k, sizeof(zrodlo), compare);

}


struct listodrzewo
{
	int symbol;
	int czestosc;
	string kod;
	listodrzewo *next, *prev;
	listodrzewo *lewy, *prawy;
	
	
} *head=NULL, *x=NULL;
listodrzewo *dodaj (listodrzewo* head, int freq, int znak)
{
	
	listodrzewo* nowy;
	nowy=new listodrzewo;
	if (head) head->prev=nowy;
	nowy->czestosc=freq;
	nowy->symbol=znak;
	nowy->next=head;
	nowy->lewy=nowy->prawy=NULL;
	head=nowy;
	
	return head;

}

listodrzewo *sswitch(listodrzewo *l1, listodrzewo *l2 )
{

	l2->prev=l1->prev;
	l1->next=l2->next;
	l2->next=l1;
	l1->prev=l2;
    
    return l2;
}
listodrzewo *bublesort (listodrzewo * head)
{
    if( head == NULL ) return NULL;

    if( head->next !=NULL && head->czestosc > head->next->czestosc )
        head = sswitch( head, head->next );

    head->next = bublesort(head->next);

    return head;
}


int rower=0;
void liscieplik (listodrzewo *head, string aa)   {   
     string fs; int r=0;
       if(head != NULL)  {    
             //head->kod=aa; 
             	    
				if (head->symbol>-1){ rower++; plik_zapis.put(aa.length()); plik_zapis.put((char)head->symbol);  fs=aa;while(fs.length()>0){while (fs.length()<8)fs=fs+"0";
				
			r=strtol(fs.substr(0,8).c_str(),NULL,2); 	plik_zapis.put(r); 
			fs.erase(0,8);
			tabk[head->symbol]=aa;   
         }} liscieplik (head->lewy, aa+"0");
			   liscieplik (head->prawy, aa+"1");  
         }
         
      } 


int zastep=-1;
listodrzewo* tworzeniedrzewa (listodrzewo* head)
{
	
	listodrzewo* kolejny;
	kolejny=new listodrzewo;
	kolejny->symbol=zastep;
	zastep--;
	kolejny->czestosc=head->czestosc + head->next->czestosc;
	
	kolejny->lewy=head;
	kolejny->prawy=head->next;
	kolejny->next=head->next->next;
	if (head->next->next) head->next->next->prev=kolejny;
	head->next->prev=head->next->next=NULL;	
	head->next=NULL;
	

	
	head=kolejny;
	head=bublesort (head);
	
	return head;
}

listodrzewo* wypiszliste (listodrzewo *head)
{
	while (head)
	{
		cout<<head->symbol<<" "<<head->czestosc<<endl;
		head=head->next;
	}
}
string nabir (int liczba)
{
	int i=0, tab[8];
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

int Zadanie1()
{



for (int a=0;a<256;a++)
	{ 
		//pobranie tekstu z pliku odczytywanego
	if (t[a].czestosc>0){


		//funkcja good() sprawdza m.in. czy wewnêtrzny znacznik aktualnej pozycji w pliku nie wskazuje na koniec tego pliku
		//je¿eli tak (zwracana jest wtedy wartoœæ false) to nie nastêpuje zapis i odczytywanie zostaje zakoñczone
		
		head=dodaj (head, t[a].czestosc, t[a].znak);
		//zapisanie tekstu do pliku do zapisu wraz z modyfikatorem przejœcia do nastêpnej linii
	
		
		//wyœwietlenie pobranego tekstu w oknie konsoli tekstowej
	
	}
	}
	//zamkniêcie pliku odczytywanego


	//zamkniêcie pliku do zapisu
//	plik_zapis.close();
	
		cout << "Zaczynam tworzenie drzewa kodowego." <<endl;

    while(head->next)
	head=tworzeniedrzewa (head);
	
	if ((zastep*(-1)-1 )<0 ) {cout << "Wystapil blad! Istnieje za malo symboli zastepczych."<<endl; return -1; }
	else 
	cout << "Istnieje " << zastep*(-1)-1 << " symboli zastepczych." << endl;
	
	cout << "Rozpoczynam trworzenie tabeli kodowej." <<endl;	
	liscieplik (head, "");
	if (rower<0 || rower>iterator1) { cout << "Wystapil blad! Tabela kodowa jest zbyt duza lub za mala." <<endl; return -1;}
	else cout << "Tabela kodowa liczy "<< rower << " elementow."<<endl;
	
	return 0;
}




// *********** Zadanie 3 - kompresujemy plik *********** //

unsigned char huff(void)
{

string bufor="";
int liczbabajtow=0;
	cout << "Rozpoczynam kompresje pliku. " <<endl;
while(plik_odczyt.good())
{
	int z=-1;

	short k=plik_odczyt.get();
	if(k==-1)break;
	while(++z!=k);
	bufor=bufor+tabk[z];
if(bufor.length()>=8)

	{
		string nowy=bufor.substr(0,8);
		bufor.erase(0,8);
		unsigned char bajt=strtol(nowy.c_str(),NULL,2);
		plik_zapis.put(bajt); liczbabajtow++;
    }


}
//cout<<"Odczytano caly plik"<<endl;
if(bufor.length()>=8)

	{
		string nowy=bufor.substr(0,8);
		bufor.erase(0,8);
		unsigned char bajt=strtol(nowy.c_str(),NULL,2);
		plik_zapis.put(bajt); liczbabajtow++;
    }
short ostatni=bufor.length(); cout<<"Ostatni"<<ostatni;

while(bufor.length()<8) bufor=bufor+"0";
unsigned char bajt=strtol(bufor.c_str(),NULL,2);
plik_zapis.put(bajt);

plik_zapis.put(ostatni);
if (liczbabajtow==0) {cout <<"Wystapil blad. Nie zapisano nic do pliku wynikowego!" <<endl; return -1;}
else cout << "Blok zakodowanych danych ma rozmiar: " << liczbabajtow << " bajtow. "<<endl;

//cout<<"Kompresja zakonczona pomyslnie"<<endl;
}


// -------------------------------------------- DEKOMPRESJA ----------------------------------------------- //


int ada=5;

	void przeg (){
		
		cout << "Rozpoczynam dekompresje" << endl;
		
	string dat="",x="",y=""; int poz= plik_odczyt.tellg(),pos1;
	plik_odczyt.seekg(-1, ios::end);
	int as=(int)plik_odczyt.get();

	pos1=plik_odczyt.tellg();
pos1--;		plik_odczyt.seekg(poz);
int yy=0;	
	
		x=nabir((int)plik_odczyt.get());

	
	dat+=x;
	
		
	string f=dat; int s=0,w=0,q=0; 
	while (plik_odczyt.tellg()<pos1){
			while ((s==0)&&(yy<=ada)){

if (f.length()<=t[yy].kod.length()){ y=nabir((int)plik_odczyt.get());  if ( plik_odczyt.tellg()>0){dat=y;f+=dat;} }	 if ((f.substr(0,t[yy].kod.length())== t[yy].kod)){ s=1; f=f.substr(t[yy].kod.length()); plik_zapis.put(t[yy].znak);  }else yy++;
} yy=0; s=0;



	} 
	f.erase(f.size()-as,8-as);

		while ((s==0)&&(yy<=ada)){

	 if ((f.substr(0,t[yy].kod.length())== t[yy].kod)){ s=1; f=f.substr(t[yy].kod.length()); plik_zapis.put(t[yy].znak);  }else yy++;
} 
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//	while (f.length()>0){
//
//if (plik_odczyt.tellg()>0){dat=y; y=nabir((int)plik_odczyt.get());  if ( plik_odczyt.tellg()>0)f+=dat; else{if (w==0){ w++;if (as!=0)f+=dat.substr(0,as);else f+=dat;}} }else break;}
} 
	long long unsigned int starycrc=0;

int dekomp() { 

	int odczytcrc[4];
	cout << "Zaczynam odczytywac CRC z pliku wejsciowego." <<endl;
	
 for (int us=0;us<4;us++){odczytcrc[us]=plik_odczyt.get(); } 
string  crcek = nabir(odczytcrc[0])+nabir(odczytcrc[1])+nabir(odczytcrc[2])+nabir(odczytcrc[3]);
	 
	 starycrc=strtol(crcek.c_str(),NULL,2);
	 if (starycrc==0) { cout << "Blednie odczytany kod CRC-32!" <<endl; return -1; }
	 else cout << "Odczytany CRC-32 to: "<<(hex) << starycrc<<endl;
	 
 ada= plik_odczyt.get(); int dl; //cout<<"Ilosc symboli wynosi: "<<ada<<endl;
 
 cout << "Rozpoczynam odczytywanie tabeli kodowej. " <<endl;
 int fd=0;
for (fd;fd<=ada;fd++){
	dl=plik_odczyt.get();
t[fd].znak = plik_odczyt.get();

while (dl>0){
	if (dl<=8){
t[fd].kod+=nabir(plik_odczyt.get()).substr(0,dl); dl=0;}
else{
t[fd].kod+=nabir(plik_odczyt.get()).substr(0,8);
dl=dl-8;}
} 
}
cout << "Jej rozmiar to: " <<fd << "."<<endl;
if (fd<0) { cout << "Blad w odczytywaniu tabeli kodowej!" << endl; return -1;} else cout << "Liczba symboli alfabetu wejsciowego wynosi: "<< fd << "."<<endl;

przeg();



return 0;




}








int main (int argc, char *argv[]){
	
	string nazwa_pliku_wejsciowego;

	string tryb;
	if (argc<2)
	{
		cout << "Nie podales parametru wejsciowego!" << endl;
		return -1;
	}
	tryb = argv[1];
	nazwa_pliku_wejsciowego = argv[2];
	long long int result;
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(),ios::binary);
	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku!" << endl;                           
		
	}
	else cout << "Plik otworzono poprawnie." << endl;
	

	
	size_t position = nazwa_pliku_wejsciowego.find(".");
	string nowaNazwa = nazwa_pliku_wejsciowego.substr(0, position);
	
	
if (tryb== "/K"){
	cout<< "Wybrales kompresje!" <<endl;	
	cout << "Plik, ktory chcesz skompresowac to:" << nazwa_pliku_wejsciowego << endl;
	plik_zapis.open((nowaNazwa+".huff").c_str(), ios::binary);
	result =obliczcrc();
	if (result<0) {cout << "Obliczono bledny kod CRC-32" <<endl; return -1;};
	view (result);
	cout << "Odczytano nastepujacy kod CRC: "<<(hex)<< result<<(dec) << endl;

	plik_odczyt.close();
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(),ios::binary);

	ile_bajtow();
	Zadanie1();
	plik_odczyt.close();
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(),ios::binary);
	huff();
	int wsp =plik_zapis.tellp();
	cout << "Plik skompresowany to : "<< nowaNazwa+".huff" << "." <<endl;
	cout << "Rozmiar pliku wejsciowego: " << rpw << " bajtow." <<endl;
	cout<< "Rozmiar pliku wyjsciowego: " <<wsp << " bajtow." <<endl;
	
	wsp = wsp*100/rpw;
	
	cout << "Wspolczynniki kompresji wynosi: "<< wsp << " %." <<endl;

	cout<< "Koniec dzialania programu! Zadanie wykonane! Do pliku o rozszerzeniu *.huff wypisana kolejno: kod CRC-32, rozmiar tabeli kodowej, tabele kodowa, blok zakodowanych danych, liczbe bitow znaczacych ostatniego bajtu."<<endl;


} else if (tryb=="/D"){
	
		cout << "Wybrales dekompresje!"<<endl;
		cout << "Plik, ktory chcesz zdekompresowac to:" << nazwa_pliku_wejsciowego << endl;
		plik_zapis.open((nowaNazwa+".dhuff").c_str(), ios::binary);
		dekomp();  int duzy =plik_zapis.tellp();
		plik_odczyt.close();
			plik_zapis.close();
	plik_odczyt.open((nowaNazwa+".dhuff").c_str(), ios::binary); 
	if (duzy==0) cout << "Do pliku wynikowego nie zostalo nic zapisane."<<endl; else cout << "Rozmiar pliku wynikowego to: "<< duzy << " bajtow, czyli tyle bajtow rozkodowano." <<endl;
	cout << "Plik zdekompresowany to : "<< nowaNazwa+".dhuff" << "." <<endl;
	int sresult =obliczcrc(); cout<<"Nowy CRC-32 "<<(hex)<<sresult<<" Stary CRC-32 "<<starycrc<<(dec)<<endl;
	
	if (sresult==starycrc) cout << " Nowy i stary CRC-32 s¹ takie same " <<endl; else cout << "Nowy i stary CRC-32 sa rozne." <<endl;


	

	
	cout << "Plik zostal pomyslnie zdekompresowany." << endl;
}
else {cout<<"Bledny Tryb - wybierz /D, jesli chcesz zdekompresowac plik, a /K jesli chcesz go skompresowac";return -1;
}



	plik_odczyt.close();
	plik_zapis.close();
	
	return 0;
}


