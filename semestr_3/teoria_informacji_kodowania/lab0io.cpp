//-----------------------------------------------------------//
// Teoria informacji i kodowania - æwiczenia laboratoryjne   //
// Przyk³adowy kod programu w C++ demonstruj¹cy operacje I/O // 
//                                                           //
// Wojciech SULEJ, ITA, WCY, WAT                             //
//-----------------------------------------------------------//

//w³¹czenie do programu w jêzyku C++ standardowej biblioteki jêzyka C
#include <cstdlib>

//w³¹czenie do programu biblioteki obs³ugi napisów 
//jest to jednolity, niezale¿ny od systemu i bezpieczny interfejs do manipulowania napisami
//ten typ danych zastêpuje tradycyjne ³añcuchy znaków char*
#include <string>

//w³¹czenie do programu biblioteki obs³ugi strumieni I/O
//jest to jednolity, niezale¿ny od systemu i bezpieczny interfejs do obs³ugi operacji I/O
//umo¿liwia on w szczególnoœci wyœwietlanie napisów w oknie konsoli tekstowej,
//a tak¿e pobieranie i przetwarzanie znaków wprowadzanych z klawiatury 
#include <iostream>

//okreœlenie domyœlnej przestrzeni nazw
using namespace std;

int main(int argc, char *argv[])
{
     
	//deklaracje zmiennych tekstowych zastêpuj¹cych tradycyjne ³añcuchy znaków char*
	string tekst1 = "Witamy serdecznie";
	string tekst2 = " w WAT.";
     
	//deklaracje zmiennych nietekstowych
	int liczba = 11;
	float pi = 3.14;
	char znak = '7';
	
	unsigned char bajt_8b = 35;
	     	 
	//-----------------------------------------------------------//
	// Zadanie 1                                                 //
	// Wyœwietlanie wartoœci zmiennych w oknie konsoli tekstowej //
	//-----------------------------------------------------------//
	 
	//wyœwietlenie dowolnego tekstu w oknie konsoli tekstowej
	//standard output stream, standardowy strumieñ wyjœciowy
	//cout = console output
	cout << "Witamy serdecznie";
	cout << " w WAT." << endl;

	//modyfikator strumienia wyjœciowego (endl) powoduj¹cy przejœcie do nastêpnej linii na ekranie
	cout << endl;

	//proste ³¹czenie (konkatenacja) dwóch zmiennych tekstowych
	cout << "tekst1 + tekst2: " << tekst1 + tekst2 << endl;
     
	//wyœwietlenie wartoœci dowolnej zmiennej nietekstowej w oknie konsoli tekstowej
	cout << "liczba: " << liczba << endl;
	cout << "pi: " << pi << endl;
	cout << "znak: " << znak << endl;
	
	cout << "bajt_8b: " << bajt_8b << " (" << (int)bajt_8b << ")" << endl;
     
	cout << endl;

	//wyœwietlenie wartoœci dziesiêtnej podanej liczby binarnej w oknie konsoli tekstowej
	cout << "liczba 11110000b: " << strtol("11110000", 0, 2) << endl;
    
	//funkcja strtol() zamienia liczbê binarn¹ wyra¿on¹ jako ci¹g znaków "0" i "1" na liczbê ca³kowit¹ typu long
	//np. "11110000" -> 240

	cout << endl;
	     
	//modyfikator strumienia wyjœciowego (hex) powoduj¹cy, ¿e liczby wyœwietlane s¹ jako liczby w systemie szesnastkowym
	//umo¿liwia prost¹ konwersjê wyœwietlanych liczb na postaæ heksadecymaln¹
	cout << "liczba hex: " << hex << liczba << endl;
     
	//modyfikator strumienia wyjœciowego (dec) powoduj¹cy, ¿e liczby wyœwietlane s¹ jako liczby w systemie dziesiêtnym
	cout << "liczba dec: " << dec << liczba << endl;

	cout << endl;
		
	//-------------------------------------------------------------//
	// Zadanie 2                                                   //
	// Pobranie liczby wprowadzonej przez u¿ytkownika z klawiatury //
	// i wyœwietlenie jej po zamianie na system szesnastkowy       //
	//-------------------------------------------------------------//
	 
	cout << "Podaj liczbe [dec]: ";
	 
	//pobranie i przetworzenie znaków wprowadzanych z klawiatury
	//standard input stream, standardowy strumieñ wejœciowy
	//cin = console input
	cin >> liczba;
     
	cout << "Podales liczbe [hex]: " << hex << liczba << endl;
     
	cout << endl;
     
	//-----------------------------------------------------------------//
	// Zadanie 3                                                       //
	// Wyœwietlenie liczby wszystkich parametrów wejœciowych           //
	// podanych przy uruchamianiu programu i wyœwietlenie ich wartoœci //
	//-----------------------------------------------------------------//
     
	cout << "Liczba parametrow wejsciowych (argc): " << argc << endl;
     
	for (int i = 0; i < argc; i++)
		cout << "Parametr " << i << " (argv[" << i << "]): " << argv[i] << endl;

	cout << endl;
	cout << endl;

	//-------------------------------------------------------//
	// Zadanie 4                                             //
	// Pobranie liczby wprowadzonej jako                     //
	// parametr wejœciowy przy uruchamianiu programu         //
	// i wyœwietlenie jej po zamianie na system szesnastkowy //
	//-------------------------------------------------------//
	
	//sprawdzenie czy podano liczbê jako parametr wejœciowy
	//poprzez sprawdzenie liczby wprowadzonych parametrów
	if (argc<2)
	{
		cout << "Brak liczby jako parametru wejsciowego!" << endl;
		return -1;
	}
	
	//funkcja z biblioteki standardowej C zamieniaj¹ca ³añcuch znaków na liczbê ca³kowit¹
	liczba = atoi(argv[1]);

	cout << "Podana liczba jako parametr wejsciowy [dec]: " << dec << liczba << endl;
	cout << "Podana liczba po konwersji [hex]: " << hex << liczba << endl;
     
	cout << endl;

	//-------------------------------------------------------//

	return EXIT_SUCCESS;
}

