//------------------------------------------------------------------//
// Teoria informacji i kodowania - æwiczenia laboratoryjne          //
// Przyk³adowy kod programu w C++ demonstruj¹cy operacje na plikach //
//                                                                  //
// Wojciech SULEJ, ITA, WCY, WAT                                    //
//------------------------------------------------------------------//

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

//w³¹czenie do programu biblioteki obs³ugi strumieni plikowych
//jest to jednolity, niezale¿ny od systemu i bezpieczny interfejs do obs³ugi plików
//umo¿liwia on w szczególnoœci odczytywanie danych z plików i zapisywanie danych do plików
#include <fstream>

//okreœlenie domyœlnej przestrzeni nazw
using namespace std;

//deklaracje (zapowiedzi) funkcji realizuj¹cych kolejne zadania
//(pe³ne definicje tych funkcji znajduj¹ siê po funkcji main)
int Zadanie1(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis);

int Zadanie2(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis);

int Zadanie3(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis);

//-------------------------------------------------------------------//

int main(int argc, char *argv[])
{
	//deklaracje zmiennych tekstowych zastêpuj¹cych tradycyjne ³añcuchy znaków char* 
	//jak np. char* nazwa_pliku_wejsciowego;
	string nazwa_pliku_wejsciowego;

	//deklaracje zmiennych plikowych umo¿liwiaj¹cych wykonywanie operacji na plikach
	//ifstream - zmienna, za pomoc¹ której mo¿liwe s¹ operacje na wybranym pliku w trybie do odczytu 
	//ofstream - zmienna, za pomoc¹ której mo¿liwe s¹ operacje na wybranym pliku w trybie do zapisu 
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
		
	//realizacja zadania 1
	cout << "Realizacja zadania 1" << endl << endl;
	
	//wywo³anie funkcji realizuj¹cej zadanie 1
	RetCode = Zadanie1(nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);

	//sprawdzenie wyniku wykonania funkcji i w razie b³êdu zakoñczenie programu
	if (RetCode==-1) return -1;
	
	cout << endl;
	
	//realizacja zadania 2
	cout << "Realizacja zadania 2" << endl << endl;
	
	//wywo³anie funkcji realizuj¹cej zadanie 2
	RetCode = Zadanie2(nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);

	//sprawdzenie wyniku wykonania funkcji i w razie b³êdu zakoñczenie programu
	if (RetCode==-1) return -1;
	
	cout << endl;
	
	//realizacja zadania 3
	cout << "Realizacja zadania 3" << endl << endl;
	
	//wywo³anie funkcji realizuj¹cej zadanie 3
	RetCode = Zadanie3(nazwa_pliku_wejsciowego, plik_odczyt, plik_zapis);
	
	cout << endl;
		
	//sprawdzenie wyniku wykonania funkcji
	if (RetCode==-1)
		return -1;
	else
		return 0;
}

//--------------------------------------------------------------------//
// Definicja funkcji realizuj¹cej zadanie 1                           //
//                                                                    //
// zmienna z nazw¹ pliku jest argumentem przekazywanym przez wartoœæ  //
// zmienne plikowe s¹ argumentami przekazywanymi przez referencje (&) //
//--------------------------------------------------------------------//
int Zadanie1(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	//----------------------------------------------------------------//
    // Zadanie 1. OTWIERANIE I ZAMYKANIE PLIKÓW TEKSTOWYCH            //
	//            OPERACJE NA NAPISACH                                //
	// Otworzenie pliku tekstowego w trybie tekstowym,                //
	// odczytanie kolejno wszystkich danych z pliku                   //
	// i zapisanie ich do innego pliku tekstowego.                    //
	// W trybie tekstowym piki s¹ traktowane jako zbiór znaków.       //
	//----------------------------------------------------------------//

	string nowa_nazwa_pliku, tekst;
	bool wynik;
	
	//otworzenie pliku odczytywanego w trybie tekstowym (wszystkie dane z pliku traktowane s¹ jako tekst)
	//funkcja open() wi¹¿e zmienn¹ plikow¹ z wybranym fizycznym plikiem na dysku
	//w tym celu nale¿y podaæ jako pierwszy argument tej funkcji nazwê wybranego pliku
	//podaj¹c jako argument sam¹ nazwê pliku zak³adamy, ¿e znajduje siê on w katalogu bie¿¹cym (w tym, z którego uruchomiono program)
	//je¿eli plik nie znajduje siê w katalogu bie¿¹cym to jako argument trzeba podaæ œcie¿kê do pliku wraz z jego nazw¹
	//nale¿y pamiêtaæ, ¿e prawid³owo podana œcie¿ka ma postaæ np.: C:\\Dev-Cpp\\Pliki\\test.txt lub C:/Dev-Cpp/Pliki/test.txt
	//czyli do rozdzielania katalogów w œcie¿ce trzeba u¿yæ podwójnych backslashy "\\" lub pojedynczych slashy "/"
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str());

    //funkcja c_str() zamienia wartoœæ zmiennej tekstowej typu string na tradycyjne ³añcuchy znaków char*
	//jest to niezbêdne w przypadku podawania zmiennej tekstowej typu string jako argumentu do niektórych funkcji m.in. funkcji open()
    
    //sprawdzenie czy plik odczytywany zosta³ otworzony poprawnie
    wynik=plik_odczyt.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku odczytywanego w trybie tekstowym!" << endl;
		return -1;
	}
	
	//wyznaczenie nazwy pliku do zapisu poprzez oddzielenie od nazwy pliku wejœciowego rozszerzenia razem ze znakiem "."
	//np. test.txt -> test
	//nastêpnie dodanie do tak powsta³ej nazwy koñcówki "_tryb_tekstowy.txt"
	//np. test.txt -> test_tryb_tekstowy.txt
	nazwa_pliku_wejsciowego.erase(nazwa_pliku_wejsciowego.find_last_of("."), nazwa_pliku_wejsciowego.length());
	nowa_nazwa_pliku = nazwa_pliku_wejsciowego + "_tryb_tekstowy.txt";
			
	//funkcja find_last_of() odszukuje w zadanej zmiennej tekstowej typu string ostatnie wyst¹pienie okreœlonego znaku np. "." 
	//funkcja erase() usuwa z zadanej zmiennej tekstowej typu string wybran¹ czêœæ tekstu
	//usuwana czêœæ okreœlana jest poprzez podanie indeksu pocz¹tku i liczby usuwanych znaków licz¹c od 0 do aktualnego rozmiaru tej zmiennej
	//funkcja length() zwraca rozmiar (liczbê znaków) zadanej zmiennej tekstowej typu string
	
	//otworzenie pliku do zapisu w trybie tekstowym (wszystkie dane z pliku traktowane s¹ jako tekst)
	//je¿eli plik nie istnieje automatycznie zostanie utworzony nowy plik
	plik_zapis.open(nowa_nazwa_pliku);

	//sprawdzenie czy plik do zapisu zosta³ otworzony poprawnie
	wynik=plik_zapis.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku do zapisu w trybie tekstowym!" << endl;
		return -2;
	}

	//odczytanie tekstu z pliku za pomoc¹ operatora pobierania ze strumienia czyli ">>"
	//odczytywany jest tekst wskazywany przez wewnêtrzny znacznik pozycji w pliku
	//(domyœlnie przy otwieraniu pliku znacznik ten jest ustawiony na jego pocz¹tku)
	//do kolejnej spacji lub znaku koñca linii (tzw. znaku bia³ego) 
	//czyli w jednym wywo³aniu czytany jest jeden wyraz z tekstu
	//po tej operacji wewnêtrzny znacznik pozycji w pliku automatycznie przesuwa siê
	//na pocz¹tek kolejnego wyrazu po spacji (spacjach) lub znaku (znakach) koñca linii (tzw. znak bia³y) 
	//czyli pomijane s¹ wszelkie spacje i znaki koñca linii (tzw. znaki bia³e)
	while (true)
	{
		//pobranie tekstu z pliku odczytywanego za pomoc¹ operatora pobierania ze strumienia czyli ">>"
		plik_odczyt >> tekst;
	
		//funkcja good() sprawdza m.in. czy wewnêtrzny znacznik aktualnej pozycji w pliku nie wskazuje na koniec tego pliku
		//je¿eli tak (zwracana jest wtedy wartoœæ false) to nie nastêpuje zapis i odczytywanie zostaje zakoñczone
		wynik=plik_odczyt.good();
		if (!wynik) break;
		
		//zapisanie tekstu do pliku do zapisu za pomoc¹ operatora zapisu do strumienia czyli "<<"
		//wraz z modyfikatorem przejœcia do nastêpnej linii
		plik_zapis << tekst << endl;
		
		//wyœwietlenie pobranego tekstu w oknie konsoli tekstowej
		cout << tekst << endl;
	}
			
	//zamkniêcie pliku odczytywanego
	plik_odczyt.close();

	//zamkniêcie pliku do zapisu
	plik_zapis.close();
	
	return 0;
}

//------------------------------------------------------------------------//
// Definicja funkcji realizuj¹cej zadanie 2                               //
//                                                                        //
// zmienna z nazw¹ pliku jest argumentem przekazywanym przez wartoœæ      //
// zmienne plikowe s¹ argumentami przekazywanymi przez referencje (&)     //
//------------------------------------------------------------------------//
int Zadanie2(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	//--------------------------------------------------------------------//
	// Zadanie 2. OTWIERANIE I ZAMYKANIE PLIKÓW W TRYBIE BINARNYM         //
	//            OPERACJE NA BAJTACH 8 BITOWYCH                          //
    // Otworzenie pliku tekstowego w trybie binarnym,                     //
	// odczytanie kolejno wszystkich danych z pliku                       //
	// i zapisanie ich do innego pliku tekstowego.                        //
	// W trybie binarnym pliki nie s¹ traktowane jako zbiór znaków,       //
	// ale jako zbiór liczb (w tym wypadku jako zbiór bajtów 8-bitowych). //
	//--------------------------------------------------------------------//

	string nowa_nazwa_pliku;
	bool wynik;
	
	unsigned char bajt_8b;
		
	//otworzenie pliku odczytywanego w trybie binarnym (wszystkie dane z pliku traktowane s¹ jako liczby (bajty 8-bitowe))
	//aby otworzyæ plik w trybie binarnym nale¿y podaæ jako drugi argument funkcji open() identyfikator ios::binary
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);

	//sprawdzenie czy plik odczytywany zosta³ otworzony poprawnie
	wynik=plik_odczyt.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku odczytywanego w trybie binarnym!" << endl;
		return -3;
	}
	
	//wyznaczenie nazwy pliku do zapisu
	nowa_nazwa_pliku = nazwa_pliku_wejsciowego.substr(0, nazwa_pliku_wejsciowego.find_last_of(".")) + "_tryb_binarny.txt";
	
	//funkcja find_last_of() odszukuje w zadanej zmiennej tekstowej typu string ostatnie wyst¹pienie okreœlonego znaku np. "."	
	//funkcja substr() daje w wyniku wybran¹ czêœæ tekstu z zadanej zmiennej tekstowej typu string
	//wybierana czêœæ okreœlana jest poprzez podanie indeksu pocz¹tku i liczby wybieranych znaków licz¹c od 0 do aktualnego rozmiaru tej zmiennej
	
	//otworzenie pliku do zapisu w trybie binarnym (wszystkie dane z pliku traktowane s¹ jako liczby (bajty 8-bitowe))
	//je¿eli plik nie istnieje automatycznie zostanie utworzony nowy plik
	plik_zapis.open(nowa_nazwa_pliku, ios::binary);
	
	//sprawdzenie czy plik do zapisu zosta³ otworzony poprawnie
	wynik=plik_zapis.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku do zapisu w trybie binarnym!" << endl;
		return -4;
	}

	//odczytanie kolejno wszystkich bajtów 8b z pliku
	//odczytywany jest kolejno jeden bajt 8b wskazywany przez wewnêtrzny znacznik pozycji w pliku
	//(domyœlnie przy otwieraniu pliku znacznik ten jest ustawiony na jego pocz¹tku)
	//po tej operacji wewnêtrzny znacznik pozycji w pliku automatycznie przesuwa siê na kolejny bajt 8b
	while (true)
	{
		//pobranie jednego bajta 8b z pliku odczytywanego, s³u¿y do tego funkcja get()
		bajt_8b=plik_odczyt.get();
		
		//funkcja good() sprawdza m.in. czy wewnêtrzny znacznik aktualnej pozycji w pliku nie wskazuje na koniec tego pliku
		//je¿eli tak (zwracana jest wtedy wartoœæ false) to nie nastêpuje zapis i odczytywanie zostaje zakoñczone
		wynik=plik_odczyt.good();
		if (!wynik) break;
		
		//zapisanie jednego bajta 8b do pliku do zapisu, s³u¿y do tego funkcja put()
		plik_zapis.put(bajt_8b);		
		
		//wyœwietlenie pobranego bajta 8b w postaci heksadecymalnej w oknie konsoli tekstowej
		//mo¿na porównaæ wyœwietlone wartoœci to tych otrzymanych po otworzeniu pliku do zapisu w dowolnym HEX edytorze,
		//poniewa¿ typ danych unsigned char jest typem znakowym wiêc, ¿eby wyœwietliæ liczbê, a nie znak
		//trzeba dokonaæ konwersji na typ liczbowy np. int czyli (int) lub int(...)
		cout << hex << int(bajt_8b) << " ";		
	}

	cout << endl;

	//zamkniêcie pliku odczytywanego
	plik_odczyt.close();

	//zamkniêcie pliku do zapisu
	plik_zapis.close();

	return 0;
}

//--------------------------------------------------------------------//
// Definicja funkcji realizuj¹cej zadanie 3                           //
//                                                                    //
// zmienna z nazw¹ pliku jest argumentem przekazywanym przez wartoœæ  //
// zmienne plikowe s¹ argumentami przekazywanymi przez referencje (&) //
//--------------------------------------------------------------------//
int Zadanie3(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{
	//---------------------------------------------------------------//
    // Zadanie 3. ODCZYTYWANIE DANYCH Z PLIKÓW W TRYBIE BINARNYM     //
    //            I ZAPISYWANIE INFORMACJI DO PLIKÓW TEKSTOWYCH      //
	// Otworzenie pliku tekstowego w trybie binarnym,                //
	// odczytanie kolejno 10 pierwszych bajtów 8-bitowych z pliku    //
	// i zapamiêtanie ich w tablicy jako pary znak i kod ASCII znaku //
	// nastêpnie zapisanie tej tablicy w innym pliku tekstowym       //
	//---------------------------------------------------------------//

	string nowa_nazwa_pliku;
	bool wynik;

	unsigned char bajt_8b;
	
	//struktura umo¿liwiaj¹ca zapamiêtanie pary znak i kod ASCII znaku
	struct element
	{
		char znak;
		int kod_znaku;
	};
	
	//typ char jest specjalnym typem znakowym
	//zmienna tego typu przechowuje pojedynczy "znak" np. a, x, y, A, X, Y, 1, 5, -, &, %
	//w rzeczywistoœci jednak zmienna tego typu przechowuje liczbê 7-bitow¹ od 0 do 127 czyli kod ASCII danego znaku
	//jednak¿e dziêki temu, ¿e jest to specjalny typ znakowy kompilator wie, ¿e wyœwietlaj¹c w oknie konsoli 
	//lub zapisuj¹c do pliku zawartoœæ tej zmiennej ma byæ pokazany w³aœnie odpowiedni znak, a nie jego kod ASCII
    //przyk³adowo: cout << znak; - wyœwietli w oknie konsoli tekstowej znak
    //             cout << int(znak); - wyœwietli w oknie konsoli tekstowej kod ASCII znaku (liczbê)
    //zmienna typu char zajmuje w pamiêci 8 bitów, a wiêc umo¿liwia zapisanie liczb spoza zakresu od 0 do 127
    //ale trzeba zwróciæ uwagê, ¿e bêdzie to liczba ze znakiem, a wiêc liczba od -128 do 127 
    //aby u¿yæ zmiennej typu char do przechowania liczby od 0 do 255 nale¿y u¿yæ jej wersji "zawsze dodatniej" czyli typu unsigned char
		
	//je¿eli chcemy operowaæ znakami u¿ywamy typu char
	//je¿eli chcemy operowaæ na bajtach 8-bitowych u¿ywamy typu unsigned char 
	    
    //dla zmiennej kod_znaku w strukturze u¿yty zosta³ typ int czyli liczba ca³kowita o rozmiarze w tym wypadku 32 bitów    
    //zgodnie ze standardem C99 jêzyka C++ typ int ma mieæ minimum 16 bitów, 
	//ale w praktyce na maszynach 32-bitowych zazwyczaj typ int ma w³aœnie 32 bity
    //w tym wypadku mo¿na by u¿yæ zmiennej o mniejszym rozmiarze (np. unsigned char, bo kod znaku to liczba od 0 do 127 lub szerzej od 0 do 255),
	//ale tak jest wygodniej ze wzglêdu na przysz³e wykorzystanie tego fragmentu kodu
		    
	//tablica 10 elementowa struktur umo¿liwiaj¹cych zapamiêtanie pary znak i kod ASCII znaku
	//od razu zainicjowana wartoœciami 0 u¿ywaj¹c { }
	element tablica_robocza[10] = {0, 0};
		
	//otworzenie pliku odczytywanego w trybie binarnym
	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str(), ios::binary);

	//sprawdzenie czy plik odczytywany zosta³ otworzony poprawnie
	wynik=plik_odczyt.is_open(); 
	if (!wynik)
	{
		cout << "Blad otwierania pliku odczytywanego do tablicy!" << endl;
		return -5;
	}
	
	//odczytanie kolejno 10 pierwszych znaków z pliku
	for (int i=0; i< 10; i++)
	{
		//pobranie jednego bajta 8b z pliku odczytywanego czyli jednego znaku
		bajt_8b=plik_odczyt.get();
		
		//sprawdzenie czy nie koniec pliku
		wynik=plik_odczyt.good();
		if (!wynik) break;
				
		//zapamiêtanie odczytanego znaku i jego kodu w tablicy
		tablica_robocza[i].znak = bajt_8b;
		tablica_robocza[i].kod_znaku = int(bajt_8b);
		
		//pobierane s¹ kolejne znaki z pliku odczytywanego otwartego w trybie binarnym,
		//wiêc w rzeczywistoœci pobierany jest bajt 8-bitowy czyli liczba od 0 do 255,
		//jednak¿e w tym przypadku jest to plik zawieraj¹cy tylko tekst,
		//a wiêc na pewno pobrane bêd¹ tylko liczby od 0 do 127 (kody ASCII)
		//st¹d mo¿emy bez obaw u¿ywaæ zamiennie typu char i unsigned char, gdy¿ w tym wypadku zakresy obu typów bêd¹ siê pokrywa³y		
	}
	
	//zamkniêcie pliku odczytywanego
	plik_odczyt.close();
	
	//wyznaczenie nazwy pliku do zapisu 
	nowa_nazwa_pliku = nazwa_pliku_wejsciowego.substr(0, nazwa_pliku_wejsciowego.find_last_of(".")) + "_tablica.txt";
		
	//otworzenie pliku do zapisu w trybie tekstowym
	//je¿eli plik nie istnieje automatycznie zostanie utworzony nowy plik
	plik_zapis.open(nowa_nazwa_pliku);
	
	//sprawdzenie czy plik do zapisu zosta³ otworzony poprawnie
	wynik=plik_zapis.is_open();
	if (!wynik)
	{
		cout << "Blad otwierania pliku do zapisu tablicy!" << endl;
		return -6;
	}
	
	//zapisanie zawartoœæi tablicy do pliku wynikowego
	for (int i = 0; i < 10; i++)
	{
		//zapisanie jednego elementu tablicy do pliku wynikowego
		plik_zapis << tablica_robocza[i].znak << " " << tablica_robocza[i].kod_znaku << endl;
		
		//wyœwietlenie jednego elementu tablicy w oknie konsoli tekstowej
		cout << tablica_robocza[i].znak << " " << dec << tablica_robocza[i].kod_znaku << endl;			
	}
	
	//zamkniêcie pliku do zapisu
	plik_zapis.close();

	return 0;
}


