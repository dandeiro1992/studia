#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

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

void rodzinaplik (listodrzewo *head, string aa, ofstream &plik_zapis)   
{    
      
       if (head != NULL)  {    
             if(head->prawy){//head->kod=aa; 
             	rodzinaplik (head->lewy, aa+"0", plik_zapis);    
				      
             plik_zapis<<head->symbol<<" "<<head->lewy->symbol<<" "<<head->prawy->symbol<<endl; 
			  
             rodzinaplik (head->prawy, aa+"1", plik_zapis);  
             } 
      } 
}

void kodplik (listodrzewo *head, string aa, ofstream &plik_zapis)   {   
      
       if(head != NULL)  {    
             //head->kod=aa; 
             	kodplik (head->lewy, aa+"0", plik_zapis);    
				     
             plik_zapis<<head->symbol<< " " << aa<<endl; 
			  
             kodplik (head->prawy, aa+"1", plik_zapis);  
              
      } 
}

void liscieplik (listodrzewo *head, string aa,  ofstream &plik_zapis)   {   
      
       if(head != NULL)  {    
             //head->kod=aa; 
             	liscieplik (head->lewy, aa+"0", plik_zapis);    
				if (!head->lewy) plik_zapis<<head->symbol<< " "<< aa<<endl;     
              
			  else liscieplik (head->prawy, aa+"1", plik_zapis);  
              
      } 
}


int k=-1;
listodrzewo* tworzeniedrzewa (listodrzewo* head)
{
	
	listodrzewo* kolejny;
	kolejny=new listodrzewo;
	kolejny->symbol=k;
	k--;
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


int Zadanie1(string nazwa_pliku_wejsciowego, ifstream &plik_odczyt, ofstream &plik_zapis)
{

	string tekst,tekst1;

	plik_odczyt.open(nazwa_pliku_wejsciowego.c_str());

    //funkcja c_str() zamienia wartoœæ zmiennej tekstowej typu string na tradycyjne ³añcuchy znaków *char
	//jest to niezbêdne w przypadku podawania zmiennej tekstowej typu string jako argument do niektórych funkcji m.in. funkcji open()
    
    //sprawdzenie czy plik odczytywany zosta³ otworzony poprawnie
	if (!plik_odczyt.is_open())
	{
		cout << "Blad otwierania pliku odczytywanego w trybie tekstowym!" << endl;
		return -1;
	}

	//plik_zapis.open("wynik_tekstowy.txt");


//	if (!plik_zapis.is_open())
//	{
//		cout << "Blad otwierania pliku do zapisu w trybie tekstowym!" << endl;
//		return -1;
//	}


	while (true)
	{ 
		//pobranie tekstu z pliku odczytywanego
		plik_odczyt >> tekst;


		//funkcja good() sprawdza m.in. czy wewnêtrzny znacznik aktualnej pozycji w pliku nie wskazuje na koniec tego pliku
		//je¿eli tak (zwracana jest wtedy wartoœæ false) to nie nastêpuje zapis i odczytywanie zostaje zakoñczone
		if (!plik_odczyt.good()) break;
			plik_odczyt >> tekst1;
		
		head=dodaj (head, atoi(tekst1.c_str()), atoi(tekst.c_str()));
		//zapisanie tekstu do pliku do zapisu wraz z modyfikatorem przejœcia do nastêpnej linii
	
		
		//wyœwietlenie pobranego tekstu w oknie konsoli tekstowej
	
	}
			
	//zamkniêcie pliku odczytywanego
	plik_odczyt.close();

	//zamkniêcie pliku do zapisu
//	plik_zapis.close();
	
		
	plik_zapis.open((nazwa_pliku_wejsciowego+".tree").c_str());
    while(head->next)
	head=tworzeniedrzewa (head);
	rodzinaplik(head, "", plik_zapis);
	plik_zapis.close();
	
	plik_zapis.open((nazwa_pliku_wejsciowego+".coding").c_str());
	kodplik (head, "", plik_zapis);
	plik_zapis.close();
	
	plik_zapis.open((nazwa_pliku_wejsciowego+".code").c_str());
	liscieplik (head, "", plik_zapis);
	plik_zapis.close();
	
	return 0;
}


int main(int argc, char *argv[])
{
	//deklaracje zmiennych tekstowych zastêpuj¹cych tradycyjne ³añcuchy znaków *char
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
while(head->next)
	head=tworzeniedrzewa (head);
	
	//sprawdzenie wyniku wykonania funkcji
	if (RetCode==-1)
		return -1;
	else
		return 0;

    return EXIT_SUCCESS;
}
