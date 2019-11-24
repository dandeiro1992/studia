//-----------------------------------------------------//
//	          Teoria informacji i kodowania            //
//                   Zadanie nr 1                      //
//               Aleksandra KUD£A I3X2S1               //
//-----------------------------------------------------//


#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

const int k=256;

struct zrodlo{
        int czestosc,znak;
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
 

int ile_bajtow(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	unsigned char bajt_8b;
	
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);
	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku odczytywanego w trybie binarnym!" << endl;
		return -1;
	}

	plik_zapis.open((nazwa_pliku_wejsciowego+".ile").c_str());

	

	if (!plik_zapis.is_open())
	{
		cout << "Blad otwierania pliku do zapisu w trybie binarnym!" << endl;
		return -1;
	}

int i=0;

	while (true)
	{
	
		//pobranie jednego bajta 8b z pliku odczytywanego
		bajt_8b=plik_odczyt.get();
		
		//funkcja good() sprawdza m.in. czy wewnêtrzny znacznik aktualnej pozycji w pliku nie wskazuje na koniec tego pliku
		//je¿eli tak (zwracana jest wtedy wartoœæ false) to nie nastêpuje zapis i odczytywanie zostaje zakoñczone
		if (!plik_odczyt.good()) break;	
		i++;	
		if (	t[bajt_8b].znak!=bajt_8b)	t[bajt_8b].znak=bajt_8b;
		t[bajt_8b].czestosc++;
		//zapisanie bajta 8 biotwego do listy;
		

	}
	
		plik_zapis<<i<<endl;

	//zamkniêcie pliku odczytywanego
	plik_odczyt.close();
	//zamkniêcie pliku do zapisu
	plik_zapis.close();	
	plik_zapis.open((nazwa_pliku_wejsciowego+".model").c_str());
	for (int j=0;j<256;j++)
	if (t[j].czestosc>0){plik_zapis<<t[j].znak<<" "<<t[j].czestosc<<endl;
	}
	plik_zapis.close();	

qsort (t, k, sizeof(zrodlo), compare);
	plik_zapis.open((nazwa_pliku_wejsciowego+".modelsort").c_str());
	for (int j=0;j<256;j++)
	if (t[j].czestosc>0){plik_zapis<<t[j].znak<<" "<<t[j].czestosc<<endl;
	}
	plik_zapis.close();


}



int main(int argc, char *argv[])
{


	string nazwa_pliku_wejsciowego;

	ifstream plik_odczyt;
	ofstream plik_zapis;
	
	int RetCode;
	
	//sprawdzenie czy podano nazwê pliku jako parametr wejœciowy
	//poprzez sprawdzenie liczby wprowadzonych parametrów
	if (argc<2)
	{
		cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
		return -1;
	}

	//zapamiêtanie nazwy pliku podanej jako parametr wejœciowy
	nazwa_pliku_wejsciowego = argv[1];

	cout << "Podana nazwa pliku: " << nazwa_pliku_wejsciowego << endl;

	cout << endl;
	

	//realizacja ile_bajtow
	cout << "Realizacja zadania 1 w toku!" << endl << endl;
	cout << "Sprawdzam, ile bajtow ma plik" << endl << endl;
	cout << "Tworze tablice symboli wraz z ich czestosciami" << endl << endl;
	cout << "Sortuje tablice symboli wraz z ich czestosciami" << endl << endl;
	
	//wywo³anie funkcji realizuj¹cej zadanie 1
	RetCode = ile_bajtow(nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);

	cout << endl;
	
	//sprawdzenie wyniku wykonania funkcji
	if (RetCode==-1)
		return -1;
	else
		return 0;
    system("PAUSE");
    return EXIT_SUCCESS;		
}
