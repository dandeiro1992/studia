#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	string nazwa_pliku_odczyt, tekst;
	
	ifstream plik_odczyt_binary;
	ofstream plik_odczyt_tekstowy;
	
	ofstream plik_zapis_binary;
	ofstream plik_zapis_tekstowy;
	
	int kod;
	
	if (argc<2)
	{
		cout << "Nieprawidlowa liczba parametrow wejsciowych !" << endl;
		return -1;
	}
	
	nazwa_pliku_odczyt = argv[1];
	
	cout << "Podana nazwa pliku: " << nazwa_pliku_odczyt << endl;
	
	plik_odczyt.open(nazwa_pliku_odczyt.c_str(), ios::binary);
	
	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku do odczytu !" << endl;
		return -1;
	}
	
	plik_zapis.open("wynik.txt", ios::binary);
	
	if (!plik_zapis.is_open())
	{
		cout << "Blad otwierania pliku do zapisu !" << endl;
		return -1;
	}
	
	//kod=plik_odczyt.get();
	
	while (plik_odczyt.good())
	{
		cout << hex << kod << " ";
		
		//plik_zapis << kod << " ";
		
		plik_zapis.put(kod);
		
		kod=plik_odczyt.get();
		
		//plik_odczyt >> tekst;
		//cout << char(kod);	
	}
	
	plik_odczyt.close();
	
	plik_zapis.close();
	
	return 0;
}
