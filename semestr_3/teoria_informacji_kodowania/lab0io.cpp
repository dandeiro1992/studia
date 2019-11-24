//-----------------------------------------------------------//
// Teoria informacji i kodowania - �wiczenia laboratoryjne   //
// Przyk�adowy kod programu w C++ demonstruj�cy operacje I/O // 
//                                                           //
// Wojciech SULEJ, ITA, WCY, WAT                             //
//-----------------------------------------------------------//

//w��czenie do programu w j�zyku C++ standardowej biblioteki j�zyka C
#include <cstdlib>

//w��czenie do programu biblioteki obs�ugi napis�w 
//jest to jednolity, niezale�ny od systemu i bezpieczny interfejs do manipulowania napisami
//ten typ danych zast�puje tradycyjne �a�cuchy znak�w char*
#include <string>

//w��czenie do programu biblioteki obs�ugi strumieni I/O
//jest to jednolity, niezale�ny od systemu i bezpieczny interfejs do obs�ugi operacji I/O
//umo�liwia on w szczeg�lno�ci wy�wietlanie napis�w w oknie konsoli tekstowej,
//a tak�e pobieranie i przetwarzanie znak�w wprowadzanych z klawiatury 
#include <iostream>

//okre�lenie domy�lnej przestrzeni nazw
using namespace std;

int main(int argc, char *argv[])
{
     
	//deklaracje zmiennych tekstowych zast�puj�cych tradycyjne �a�cuchy znak�w char*
	string tekst1 = "Witamy serdecznie";
	string tekst2 = " w WAT.";
     
	//deklaracje zmiennych nietekstowych
	int liczba = 11;
	float pi = 3.14;
	char znak = '7';
	
	unsigned char bajt_8b = 35;
	     	 
	//-----------------------------------------------------------//
	// Zadanie 1                                                 //
	// Wy�wietlanie warto�ci zmiennych w oknie konsoli tekstowej //
	//-----------------------------------------------------------//
	 
	//wy�wietlenie dowolnego tekstu w oknie konsoli tekstowej
	//standard output stream, standardowy strumie� wyj�ciowy
	//cout = console output
	cout << "Witamy serdecznie";
	cout << " w WAT." << endl;

	//modyfikator strumienia wyj�ciowego (endl) powoduj�cy przej�cie do nast�pnej linii na ekranie
	cout << endl;

	//proste ��czenie (konkatenacja) dw�ch zmiennych tekstowych
	cout << "tekst1 + tekst2: " << tekst1 + tekst2 << endl;
     
	//wy�wietlenie warto�ci dowolnej zmiennej nietekstowej w oknie konsoli tekstowej
	cout << "liczba: " << liczba << endl;
	cout << "pi: " << pi << endl;
	cout << "znak: " << znak << endl;
	
	cout << "bajt_8b: " << bajt_8b << " (" << (int)bajt_8b << ")" << endl;
     
	cout << endl;

	//wy�wietlenie warto�ci dziesi�tnej podanej liczby binarnej w oknie konsoli tekstowej
	cout << "liczba 11110000b: " << strtol("11110000", 0, 2) << endl;
    
	//funkcja strtol() zamienia liczb� binarn� wyra�on� jako ci�g znak�w "0" i "1" na liczb� ca�kowit� typu long
	//np. "11110000" -> 240

	cout << endl;
	     
	//modyfikator strumienia wyj�ciowego (hex) powoduj�cy, �e liczby wy�wietlane s� jako liczby w systemie szesnastkowym
	//umo�liwia prost� konwersj� wy�wietlanych liczb na posta� heksadecymaln�
	cout << "liczba hex: " << hex << liczba << endl;
     
	//modyfikator strumienia wyj�ciowego (dec) powoduj�cy, �e liczby wy�wietlane s� jako liczby w systemie dziesi�tnym
	cout << "liczba dec: " << dec << liczba << endl;

	cout << endl;
		
	//-------------------------------------------------------------//
	// Zadanie 2                                                   //
	// Pobranie liczby wprowadzonej przez u�ytkownika z klawiatury //
	// i wy�wietlenie jej po zamianie na system szesnastkowy       //
	//-------------------------------------------------------------//
	 
	cout << "Podaj liczbe [dec]: ";
	 
	//pobranie i przetworzenie znak�w wprowadzanych z klawiatury
	//standard input stream, standardowy strumie� wej�ciowy
	//cin = console input
	cin >> liczba;
     
	cout << "Podales liczbe [hex]: " << hex << liczba << endl;
     
	cout << endl;
     
	//-----------------------------------------------------------------//
	// Zadanie 3                                                       //
	// Wy�wietlenie liczby wszystkich parametr�w wej�ciowych           //
	// podanych przy uruchamianiu programu i wy�wietlenie ich warto�ci //
	//-----------------------------------------------------------------//
     
	cout << "Liczba parametrow wejsciowych (argc): " << argc << endl;
     
	for (int i = 0; i < argc; i++)
		cout << "Parametr " << i << " (argv[" << i << "]): " << argv[i] << endl;

	cout << endl;
	cout << endl;

	//-------------------------------------------------------//
	// Zadanie 4                                             //
	// Pobranie liczby wprowadzonej jako                     //
	// parametr wej�ciowy przy uruchamianiu programu         //
	// i wy�wietlenie jej po zamianie na system szesnastkowy //
	//-------------------------------------------------------//
	
	//sprawdzenie czy podano liczb� jako parametr wej�ciowy
	//poprzez sprawdzenie liczby wprowadzonych parametr�w
	if (argc<2)
	{
		cout << "Brak liczby jako parametru wejsciowego!" << endl;
		return -1;
	}
	
	//funkcja z biblioteki standardowej C zamieniaj�ca �a�cuch znak�w na liczb� ca�kowit�
	liczba = atoi(argv[1]);

	cout << "Podana liczba jako parametr wejsciowy [dec]: " << dec << liczba << endl;
	cout << "Podana liczba po konwersji [hex]: " << hex << liczba << endl;
     
	cout << endl;

	//-------------------------------------------------------//

	return EXIT_SUCCESS;
}

