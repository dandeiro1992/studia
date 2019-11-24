#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int main(int argc, char *argv[])
{
 
 
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
            cout <<"lol"<<napis1<<" "<<napis2<<" "<<napis3<<" "<<napis4<<" " << endl;
        }
        plik.close();
    } else cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
    
    
system("PAUSE");
return EXIT_SUCCESS;
}
