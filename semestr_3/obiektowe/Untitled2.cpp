#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
class Osoba
{
      public:
      char imie[100], nazwisko[100];
      int wzrost, waga;
      };
      Osoba o;
int main(int argc, char *argv[])
      {
             cout <<"Podaj imie:";
             cin >> o.imie;
             cout <<"Podaj nazwisko:";
             cin >> o.nazwisko;
             cout << "Podaj wage:";
             cin >> o.waga;
             cout <<"Podaj wzrost:";
             cin >> o.wzrost;
             cout << "Nazwisko: " << o.nazwisko <<endl;
             cout << "Imie    : " << o.imie<<endl;
             cout << "Waga    : " << o.waga <<endl;
             cout << "Wzrost  : " << o.wzrost<<endl;
             
      system("PAUSE");
      return EXIT_SUCCESS;
      }
