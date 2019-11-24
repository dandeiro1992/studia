#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
class Osoba
{
      public:
      char imie[100]; 
      int wzrost, waga;
      };
      Osoba j;
      Osoba m;
      Osoba a;
int main(int argc, char *argv[])
      {
             cout <<"Podaj imie:";
             cin >> j.imie;
             cout << "Podaj wage:";
             cin >> j.waga;
             cout <<"Podaj wzrost:";
             cin >> j.wzrost;
             m.waga=j.waga*2;
             a.wzrost=j.wzrost-25;
             
             cout << "Imie    : " << j.imie<<endl;
             cout << "Waga    : " << j.waga <<endl;
             cout << "Wzrost  : " << j.wzrost<<endl;
             
             cout << "Imie    : Marek " <<endl;
             cout << "Waga    : " << m.waga <<endl;
             cout << "Wzrost  : " << m.wzrost<<endl;
             
             cout << "Imie    : Anna" <<endl;
             cout << "Waga    : " << a.waga <<endl;
             cout << "Wzrost  : " << a.wzrost<<endl;
             
      system("PAUSE");
      return EXIT_SUCCESS;
      }
