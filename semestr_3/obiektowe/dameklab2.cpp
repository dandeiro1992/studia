#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class Pojazd
{
      public:
      string nazwa; 
      int przebieg;
      int predkosc;
      public:
      void jazda(int czas)
      {
           przebieg=przebieg+czas*(predkosc);
           
      };
      void stop(int czas)
      {
           cout<<"samochod "<<nazwa<<" stoi "<<czas<<" sekund"<<endl;
      };
      };
Pojazd N1;
Pojazd N2;
int main(int argc, char *argv[])
      {
             cout<<"Wprowadz dane pierwszego samochodu: po enterach nazwe, przebieg w metrach na s,predkosc"<<endl;
             cin>>N1.nazwa>>N1.przebieg>>N1.predkosc;
             cout<<"Wprowadz dane drugiego samochodu: po enterach nazwe, przebieg w metrach na s,predkosc"<<endl;
             cin>>N2.nazwa>>N2.przebieg>>N2.predkosc;
             //wczytywanie danych z pliku
    
  fstream plik;
    plik.open( "dane.txt", ios::in );
    if( plik.good() )
    {
        string napis,napis1,napis2,napis3,napis4;
        cout << "Zawartosc pliku:" << endl;
        getline( plik, napis );
        while( !plik.eof() )
        {
            plik>>napis1>>napis2>>napis3>>napis4;
            cout <<napis1<<" "<<napis2<<" "<<napis3<<" "<<napis4<<" " << endl;
            int pierwszy=atoi(napis2.c_str());
            int drugi=atoi(napis3.c_str());
            int czas=atoi(napis4.c_str());
            if (pierwszy==1)
            N1.jazda(czas);
            else
            N1.stop(czas);
            if(drugi==1)
            N2.jazda(czas);
            else
            N2.stop(czas);
        }
        plik.close();
    } else cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
    
    cout<<"samochod pierwszy ma przebieg"<<" "<<N1.przebieg<<endl;
    cout<<"samochod drugi ma przebieg"<<" "<<N2.przebieg<<endl;
    
             
      system("PAUSE");
      return EXIT_SUCCESS;
      }
