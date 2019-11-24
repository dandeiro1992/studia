#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
string int2bin(unsigned int znak){
	string cos;
	int i=0;
	int b=0;
	while(znak){
	if (znak%2) {
		cos="1"+cos;
		znak=znak/2;
	}
	else {
		cos="0"+cos;
		znak=znak/2;
	}
	i++;
}
b=8-i;
while (b){
	cos="0"+cos;
	b--;
}
return cos;
}

string int2binv2(unsigned int znak){
	string cos;
	int i=0;
	int b=0;
	while(znak){
	if (znak%2) {
		cos="1"+cos;
		znak=znak/2;
	}
	else {
		cos="0"+cos;
		znak=znak/2;
	}
	i++;
}
b=32-i;
while (b){
	cos="0"+cos;
	b--;
}
return cos;
}


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
	
	int main(int argc, char* argv[]) {
	string nazwa_pliku_wejsciowego;// pierwszy parametr
	ifstream plik_odczyt;
	ofstream plik_zapis;
	string nowa_nazwa_pliku; //rozszerzenie .crc32
	unsigned char bajt_8b;
	bool wynik;
	
	//sprawdzenie czy podano nazwê pliku jako parametr wejœciowy
	//poprzez sprawdzenie liczby wprowadzonych parametrów
	if (argc<2)
	{
		cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
		return -1;
	}
	nazwa_pliku_wejsciowego = argv[1]; // pierwszy parametr .code

	
	cout << "Podana nazwa pliku: " << nazwa_pliku_wejsciowego <<endl;
	cout << endl;
	
	cout << "Realizacja programu" << endl;
	
	cout << endl;
	
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(),ios::binary);
	
	wynik=plik_odczyt.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku odczytywanego!" << endl;
		return -3;
	}
	nowa_nazwa_pliku = nazwa_pliku_wejsciowego.substr(0, nazwa_pliku_wejsciowego.find_last_of(".")) + ".crc32";
	
	plik_zapis.open(nowa_nazwa_pliku.c_str());
		//sprawdzenie czy plik do zapisu zosta³ otworzony poprawnie
	wynik=plik_zapis.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku do zapisu!" << endl;
		return -4;
}


	unsigned int bufor=0x00000000; //bufor inicjowany 32 bitami o wartosci 0
	unsigned int wielomian= 0x04C11DB7; //wielomian
	string kodp;
	bajt_8b=plik_odczyt.get();
	kodp=int2bin(bajt_8b);
	unsigned int nzb= 0x80000000; //najbardziej znacz¹cy bit
	
	cout << "Obliczanie crc" <<endl;
	cout << endl; 
	
while(plik_odczyt.good())
	{
		
		if(bufor & nzb)
		{
			bufor=bufor<<1; //przesuniecie logiczne w lewo
			if(kodp.substr(0,1)=="1") // jezeli pierwszy bit pobranego symbolu 1 to dodajemy do buforu na ostatni bit 1
			bufor=bufor+0x1;
			kodp.erase(0,1);	
			bufor=bufor^wielomian; //xor
		}
		else
		{
			bufor=bufor<<1;
			if(kodp.substr(0,1)=="1")
			bufor=bufor+0x1;
			kodp.erase(0,1);	
		}	
		
		if(kodp.empty())
			{
				bajt_8b=plik_odczyt.get();
				if(!plik_odczyt.good())
				{
					break;
				}
				kodp=int2bin(bajt_8b);
				
			}
	}
	
	for(int i=0; i<32; i++)
	{
		if(bufor & nzb)
		{
			bufor=bufor<<1;
			bufor=bufor^wielomian;	
		}
		else
		bufor=bufor<<1;
	}
	
	string binary=int2binv2(bufor);
	string bajt;
	for (int j=0;j<4;j++){
		bajt=binary.substr(0,8);
		plik_zapis << char(strtol(bajt.c_str(),NULL,2)); //zapis znakowy
		binary.erase(0,8);
	}
	plik_zapis << int2binv2(bufor) << endl; //zapis binarny
	
	ostringstream ss;
	
	ss << hex << bufor;
	string hex = ss.str ();
	for (int k=hex.length();k<8;k++)
    hex="0"+hex;
    
	plik_zapis << hex <<  endl; //zapis szesnastkowy
	
	plik_zapis << dec << bufor << endl; //zapis dziesiêtny

	
	
 plik_zapis.close();
 plik_odczyt.close();	

cout << "Program wykonal sie poprawnie!" << endl;
	
	return 0;
}

