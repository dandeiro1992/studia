//------------------------------------------------------------------//
// Teoria informacji i kodowania - �wiczenia laboratoryjne          //
// Przyk�adowy kod programu w C++ demonstruj�cy operacje na plikach //
//                                                                  //
// Wojciech SULEJ, ITA, WCY, WAT                                    //
//------------------------------------------------------------------//

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

//w��czenie do programu biblioteki obs�ugi strumieni plikowych
//jest to jednolity, niezale�ny od systemu i bezpieczny interfejs do obs�ugi plik�w
//umo�liwia on w szczeg�lno�ci odczytywanie danych z plik�w i zapisywanie danych do plik�w
#include <fstream>

//okre�lenie domy�lnej przestrzeni nazw
using namespace std;

//deklaracje (zapowiedzi) funkcji realizuj�cych kolejne zadania
//(pe�ne definicje tych funkcji znajduj� si� po funkcji main)
int Zadanie1(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis);

int Zadanie2(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis);

int Zadanie3(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis);

//-------------------------------------------------------------------//

int main(int argc, char *argv[])
{
	//deklaracje zmiennych tekstowych zast�puj�cych tradycyjne �a�cuchy znak�w char* 
	//jak np. char* nazwa_pliku_wejsciowego;
	string nazwa_pliku_wejsciowego;

	//deklaracje zmiennych plikowych umo�liwiaj�cych wykonywanie operacji na plikach
	//ifstream - zmienna, za pomoc� kt�rej mo�liwe s� operacje na wybranym pliku w trybie do odczytu 
	//ofstream - zmienna, za pomoc� kt�rej mo�liwe s� operacje na wybranym pliku w trybie do zapisu 
	ifstream plik_odczyt;
	ofstream plik_zapis;
	
	int RetCode;
	
	//sprawdzenie czy podano nazw� pliku jako parametr wej�ciowy
	//poprzez sprawdzenie liczby wprowadzonych parametr�w
	if (argc<2)
	{
		cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
		return -1;
	}

	//zapami�tanie nazwy pliku podanej jako parametr wej�ciowy
	nazwa_pliku_wejsciowego = argv[1];

	cout << "Podana nazwa pliku: " << nazwa_pliku_wejsciowego << endl;

	cout << endl;
		
	//realizacja zadania 1
	cout << "Realizacja zadania 1" << endl << endl;
	
	//wywo�anie funkcji realizuj�cej zadanie 1
	RetCode = Zadanie1(nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);

	//sprawdzenie wyniku wykonania funkcji i w razie b��du zako�czenie programu
	if (RetCode==-1) return -1;
	
	cout << endl;
	
	//realizacja zadania 2
	cout << "Realizacja zadania 2" << endl << endl;
	
	//wywo�anie funkcji realizuj�cej zadanie 2
	RetCode = Zadanie2(nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);

	//sprawdzenie wyniku wykonania funkcji i w razie b��du zako�czenie programu
	if (RetCode==-1) return -1;
	
	cout << endl;
	
	//realizacja zadania 3
	cout << "Realizacja zadania 3" << endl << endl;
	
	//wywo�anie funkcji realizuj�cej zadanie 3
	RetCode = Zadanie3(nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);
	
	cout << endl;
		
	//sprawdzenie wyniku wykonania funkcji
	if (RetCode==-1)
		return -1;
	else
		return 0;
}

//--------------------------------------------------------------------//
// Definicja funkcji realizuj�cej zadanie 1                           //
//                                                                    //
// zmienna z nazw� pliku jest argumentem przekazywanym przez warto��  //
// zmienne plikowe s� argumentami przekazywanymi przez referencje (&) //
//--------------------------------------------------------------------//
int Zadanie1(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	//----------------------------------------------------------------//
    // Zadanie 1. OTWIERANIE I ZAMYKANIE PLIK�W TEKSTOWYCH            //
	//            OPERACJE NA NAPISACH                                //
	// Otworzenie pliku tekstowego w trybie tekstowym,                //
	// odczytanie kolejno wszystkich danych z pliku                   //
	// i zapisanie ich do innego pliku tekstowego.                    //
	// W trybie tekstowym piki s� traktowane jako zbi�r znak�w.       //
	//----------------------------------------------------------------//

	string nowa_nazwa_pliku, tekst;
	bool wynik;
	
	//otworzenie pliku odczytywanego w trybie tekstowym (wszystkie dane z pliku traktowane s� jako tekst)
	//funkcja open() wi��e zmienn� plikow� z wybranym fizycznym plikiem na dysku
	//w tym celu nale�y poda� jako pierwszy argument tej funkcji nazw� wybranego pliku
	//podaj�c jako argument sam� nazw� pliku zak�adamy, �e znajduje si� on w katalogu bie��cym (w tym, z kt�rego uruchomiono program)
	//je�eli plik nie znajduje si� w katalogu bie��cym to jako argument trzeba poda� �cie�k� do pliku wraz z jego nazw�
	//nale�y pami�ta�, �e prawid�owo podana �cie�ka ma posta� np.: C:\\Dev-Cpp\\Pliki\\test.txt lub C:/Dev-Cpp/Pliki/test.txt
	//czyli do rozdzielania katalog�w w �cie�ce trzeba u�y� podw�jnych backslashy "\\" lub pojedynczych slashy "/"
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str());

    //funkcja c_str() zamienia warto�� zmiennej tekstowej typu string na tradycyjne �a�cuchy znak�w char*
	//jest to niezb�dne w przypadku podawania zmiennej tekstowej typu string jako argumentu do niekt�rych funkcji m.in. funkcji open()
    
    //sprawdzenie czy plik odczytywany zosta� otworzony poprawnie
    wynik=plik_odczyt.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku odczytywanego w trybie tekstowym!" << endl;
		return -1;
	}
	
	//wyznaczenie nazwy pliku do zapisu poprzez oddzielenie od nazwy pliku wej�ciowego rozszerzenia razem ze znakiem "."
	//np. test.txt -> test
	//nast�pnie dodanie do tak powsta�ej nazwy ko�c�wki "_tryb_tekstowy.txt"
	//np. test.txt -> test_tryb_tekstowy.txt
	nazwa_pliku_wejsciowego.erase(nazwa_pliku_wejsciowego.find_last_of("."), nazwa_pliku_wejsciowego.length());
	nowa_nazwa_pliku = nazwa_pliku_wejsciowego + "_tryb_tekstowy.txt";
			
	//funkcja find_last_of() odszukuje w zadanej zmiennej tekstowej typu string ostatnie wyst�pienie okre�lonego znaku np. "." 
	//funkcja erase() usuwa z zadanej zmiennej tekstowej typu string wybran� cz�� tekstu
	//usuwana cz�� okre�lana jest poprzez podanie indeksu pocz�tku i liczby usuwanych znak�w licz�c od 0 do aktualnego rozmiaru tej zmiennej
	//funkcja length() zwraca rozmiar (liczb� znak�w) zadanej zmiennej tekstowej typu string
	
	//otworzenie pliku do zapisu w trybie tekstowym (wszystkie dane z pliku traktowane s� jako tekst)
	//je�eli plik nie istnieje automatycznie zostanie utworzony nowy plik
	plik_zapis.open(nowa_nazwa_pliku);

	//sprawdzenie czy plik do zapisu zosta� otworzony poprawnie
	wynik=plik_zapis.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku do zapisu w trybie tekstowym!" << endl;
		return -2;
	}

	//odczytanie tekstu z pliku za pomoc� operatora pobierania ze strumienia czyli ">>"
	//odczytywany jest tekst wskazywany przez wewn�trzny znacznik pozycji w pliku
	//(domy�lnie przy otwieraniu pliku znacznik ten jest ustawiony na jego pocz�tku)
	//do kolejnej spacji lub znaku ko�ca linii (tzw. znaku bia�ego) 
	//czyli w jednym wywo�aniu czytany jest jeden wyraz z tekstu
	//po tej operacji wewn�trzny znacznik pozycji w pliku automatycznie przesuwa si�
	//na pocz�tek kolejnego wyrazu po spacji (spacjach) lub znaku (znakach) ko�ca linii (tzw. znak bia�y) 
	//czyli pomijane s� wszelkie spacje i znaki ko�ca linii (tzw. znaki bia�e)
	while (true)
	{
		//pobranie tekstu z pliku odczytywanego za pomoc� operatora pobierania ze strumienia czyli ">>"
		plik_odczyt >> tekst;
	
		//funkcja good() sprawdza m.in. czy wewn�trzny znacznik aktualnej pozycji w pliku nie wskazuje na koniec tego pliku
		//je�eli tak (zwracana jest wtedy warto�� false) to nie nast�puje zapis i odczytywanie zostaje zako�czone
		wynik=plik_odczyt.good();
		if (!wynik) break;
		
		//zapisanie tekstu do pliku do zapisu za pomoc� operatora zapisu do strumienia czyli "<<"
		//wraz z modyfikatorem przej�cia do nast�pnej linii
		plik_zapis << tekst << endl;
		
		//wy�wietlenie pobranego tekstu w oknie konsoli tekstowej
		cout << tekst << endl;
	}
			
	//zamkni�cie pliku odczytywanego
	plik_odczyt.close();

	//zamkni�cie pliku do zapisu
	plik_zapis.close();
	
	return 0;
}

//------------------------------------------------------------------------//
// Definicja funkcji realizuj�cej zadanie 2                               //
//                                                                        //
// zmienna z nazw� pliku jest argumentem przekazywanym przez warto��      //
// zmienne plikowe s� argumentami przekazywanymi przez referencje (&)     //
//------------------------------------------------------------------------//
int Zadanie2(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	//--------------------------------------------------------------------//
	// Zadanie 2. OTWIERANIE I ZAMYKANIE PLIK�W W TRYBIE BINARNYM         //
	//            OPERACJE NA BAJTACH 8 BITOWYCH                          //
    // Otworzenie pliku tekstowego w trybie binarnym,                     //
	// odczytanie kolejno wszystkich danych z pliku                       //
	// i zapisanie ich do innego pliku tekstowego.                        //
	// W trybie binarnym pliki nie s� traktowane jako zbi�r znak�w,       //
	// ale jako zbi�r liczb (w tym wypadku jako zbi�r bajt�w 8-bitowych). //
	//--------------------------------------------------------------------//

	string nowa_nazwa_pliku;
	bool wynik;
	
	unsigned char bajt_8b;
		
	//otworzenie pliku odczytywanego w trybie binarnym (wszystkie dane z pliku traktowane s� jako liczby (bajty 8-bitowe))
	//aby otworzy� plik w trybie binarnym nale�y poda� jako drugi argument funkcji open() identyfikator ios::binary
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);

	//sprawdzenie czy plik odczytywany zosta� otworzony poprawnie
	wynik=plik_odczyt.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku odczytywanego w trybie binarnym!" << endl;
		return -3;
	}
	
	//wyznaczenie nazwy pliku do zapisu
	nowa_nazwa_pliku = nazwa_pliku_wejsciowego.substr(0, nazwa_pliku_wejsciowego.find_last_of(".")) + "_tryb_binarny.txt";
	
	//funkcja find_last_of() odszukuje w zadanej zmiennej tekstowej typu string ostatnie wyst�pienie okre�lonego znaku np. "."	
	//funkcja substr() daje w wyniku wybran� cz�� tekstu z zadanej zmiennej tekstowej typu string
	//wybierana cz�� okre�lana jest poprzez podanie indeksu pocz�tku i liczby wybieranych znak�w licz�c od 0 do aktualnego rozmiaru tej zmiennej
	
	//otworzenie pliku do zapisu w trybie binarnym (wszystkie dane z pliku traktowane s� jako liczby (bajty 8-bitowe))
	//je�eli plik nie istnieje automatycznie zostanie utworzony nowy plik
	plik_zapis.open(nowa_nazwa_pliku, ios::binary);
	
	//sprawdzenie czy plik do zapisu zosta� otworzony poprawnie
	wynik=plik_zapis.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku do zapisu w trybie binarnym!" << endl;
		return -4;
	}

	//odczytanie kolejno wszystkich bajt�w 8b z pliku
	//odczytywany jest kolejno jeden bajt 8b wskazywany przez wewn�trzny znacznik pozycji w pliku
	//(domy�lnie przy otwieraniu pliku znacznik ten jest ustawiony na jego pocz�tku)
	//po tej operacji wewn�trzny znacznik pozycji w pliku automatycznie przesuwa si� na kolejny bajt 8b
	while (true)
	{
		//pobranie jednego bajta 8b z pliku odczytywanego, s�u�y do tego funkcja get()
		bajt_8b=plik_odczyt.get();
		
		//funkcja good() sprawdza m.in. czy wewn�trzny znacznik aktualnej pozycji w pliku nie wskazuje na koniec tego pliku
		//je�eli tak (zwracana jest wtedy warto�� false) to nie nast�puje zapis i odczytywanie zostaje zako�czone
		wynik=plik_odczyt.good();
		if (!wynik) break;
		
		//zapisanie jednego bajta 8b do pliku do zapisu, s�u�y do tego funkcja put()
		plik_zapis.put(bajt_8b);		
		
		//wy�wietlenie pobranego bajta 8b w postaci heksadecymalnej w oknie konsoli tekstowej
		//mo�na por�wna� wy�wietlone warto�ci to tych otrzymanych po otworzeniu pliku do zapisu w dowolnym HEX edytorze,
		//poniewa� typ danych unsigned char jest typem znakowym wi�c, �eby wy�wietli� liczb�, a nie znak
		//trzeba dokona� konwersji na typ liczbowy np. int czyli (int) lub int(...)
		cout << hex << int(bajt_8b) << " ";		
	}

	cout << endl;

	//zamkni�cie pliku odczytywanego
	plik_odczyt.close();

	//zamkni�cie pliku do zapisu
	plik_zapis.close();

	return 0;
}

//--------------------------------------------------------------------//
// Definicja funkcji realizuj�cej zadanie 3                           //
//                                                                    //
// zmienna z nazw� pliku jest argumentem przekazywanym przez warto��  //
// zmienne plikowe s� argumentami przekazywanymi przez referencje (&) //
//--------------------------------------------------------------------//
int Zadanie3(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	//---------------------------------------------------------------//
    // Zadanie 3. ODCZYTYWANIE DANYCH Z PLIK�W W TRYBIE BINARNYM     //
    //            I ZAPISYWANIE INFORMACJI DO PLIK�W TEKSTOWYCH      //
	// Otworzenie pliku tekstowego w trybie binarnym,                //
	// odczytanie kolejno 10 pierwszych bajt�w 8-bitowych z pliku    //
	// i zapami�tanie ich w tablicy jako pary znak i kod ASCII znaku //
	// nast�pnie zapisanie tej tablicy w innym pliku tekstowym       //
	//---------------------------------------------------------------//

	string nowa_nazwa_pliku;
	bool wynik;

	unsigned char bajt_8b;
	
	//struktura umo�liwiaj�ca zapami�tanie pary znak i kod ASCII znaku
	struct element
	{
		char znak;
		int kod_znaku;
	};
	
	//typ char jest specjalnym typem znakowym
	//zmienna tego typu przechowuje pojedynczy "znak" np. a, x, y, A, X, Y, 1, 5, -, &, %
	//w rzeczywisto�ci jednak zmienna tego typu przechowuje liczb� 7-bitow� od 0 do 127 czyli kod ASCII danego znaku
	//jednak�e dzi�ki temu, �e jest to specjalny typ znakowy kompilator wie, �e wy�wietlaj�c w oknie konsoli 
	//lub zapisuj�c do pliku zawarto�� tej zmiennej ma by� pokazany w�a�nie odpowiedni znak, a nie jego kod ASCII
    //przyk�adowo: cout << znak; - wy�wietli w oknie konsoli tekstowej znak
    //             cout << int(znak); - wy�wietli w oknie konsoli tekstowej kod ASCII znaku (liczb�)
    //zmienna typu char zajmuje w pami�ci 8 bit�w, a wi�c umo�liwia zapisanie liczb spoza zakresu od 0 do 127
    //ale trzeba zwr�ci� uwag�, �e b�dzie to liczba ze znakiem, a wi�c liczba od -128 do 127 
    //aby u�y� zmiennej typu char do przechowania liczby od 0 do 255 nale�y u�y� jej wersji "zawsze dodatniej" czyli typu unsigned char
		
	//je�eli chcemy operowa� znakami u�ywamy typu char
	//je�eli chcemy operowa� na bajtach 8-bitowych u�ywamy typu unsigned char 
	    
    //dla zmiennej kod_znaku w strukturze u�yty zosta� typ int czyli liczba ca�kowita o rozmiarze w tym wypadku 32 bit�w    
    //zgodnie ze standardem C99 j�zyka C++ typ int ma mie� minimum 16 bit�w, 
	//ale w praktyce na maszynach 32-bitowych zazwyczaj typ int ma w�a�nie 32 bity
    //w tym wypadku mo�na by u�y� zmiennej o mniejszym rozmiarze (np. unsigned char, bo kod znaku to liczba od 0 do 127 lub szerzej od 0 do 255),
	//ale tak jest wygodniej ze wzgl�du na przysz�e wykorzystanie tego fragmentu kodu
		    
	//tablica 10 elementowa struktur umo�liwiaj�cych zapami�tanie pary znak i kod ASCII znaku
	//od razu zainicjowana warto�ciami 0 u�ywaj�c { }
	element tablica_robocza[10] = {0, 0};
		
	//otworzenie pliku odczytywanego w trybie binarnym
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);

	//sprawdzenie czy plik odczytywany zosta� otworzony poprawnie
	wynik=plik_odczyt.is_open(); 
	if (!wynik)
	{
		cout << "Blad otwierania pliku odczytywanego do tablicy!" << endl;
		return -5;
	}
	
	//odczytanie kolejno 10 pierwszych znak�w z pliku
	for (int i=0; i< 10; i++)
	{
		//pobranie jednego bajta 8b z pliku odczytywanego czyli jednego znaku
		bajt_8b=plik_odczyt.get();
		
		//sprawdzenie czy nie koniec pliku
		wynik=plik_odczyt.good();
		if (!wynik) break;
				
		//zapami�tanie odczytanego znaku i jego kodu w tablicy
		tablica_robocza[i].znak = bajt_8b;
		tablica_robocza[i].kod_znaku = int(bajt_8b);
		
		//pobierane s� kolejne znaki z pliku odczytywanego otwartego w trybie binarnym,
		//wi�c w rzeczywisto�ci pobierany jest bajt 8-bitowy czyli liczba od 0 do 255,
		//jednak�e w tym przypadku jest to plik zawieraj�cy tylko tekst,
		//a wi�c na pewno pobrane b�d� tylko liczby od 0 do 127 (kody ASCII)
		//st�d mo�emy bez obaw u�ywa� zamiennie typu char i unsigned char, gdy� w tym wypadku zakresy obu typ�w b�d� si� pokrywa�y		
	}
	
	//zamkni�cie pliku odczytywanego
	plik_odczyt.close();
	
	//wyznaczenie nazwy pliku do zapisu 
	nowa_nazwa_pliku = nazwa_pliku_wejsciowego.substr(0, nazwa_pliku_wejsciowego.find_last_of(".")) + "_tablica.txt";
		
	//otworzenie pliku do zapisu w trybie tekstowym
	//je�eli plik nie istnieje automatycznie zostanie utworzony nowy plik
	plik_zapis.open(nowa_nazwa_pliku);
	
	//sprawdzenie czy plik do zapisu zosta� otworzony poprawnie
	wynik=plik_zapis.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku do zapisu tablicy!" << endl;
		return -6;
	}
	
	//zapisanie zawarto��i tablicy do pliku wynikowego
	for (int i = 0; i < 10; i++)
	{
		//zapisanie jednego elementu tablicy do pliku wynikowego
		plik_zapis << tablica_robocza[i].znak << " " << tablica_robocza[i].kod_znaku << endl;
		
		//wy�wietlenie jednego elementu tablicy w oknie konsoli tekstowej
		cout << tablica_robocza[i].znak << " " << dec << tablica_robocza[i].kod_znaku << endl;			
	}
	
	//zamkni�cie pliku do zapisu
	plik_zapis.close();

	return 0;
}


