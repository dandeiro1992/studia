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
        string napis;
        cout << "Zawartosc pliku:" << endl;
        while( !plik.eof() )
        {
            plik>>napis;
            cout << napis << endl;
        }
        plik.close();
    } else cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
    
    
system("PAUSE");
return EXIT_SUCCESS;
}
string str = "123";
int i = atoi(str.c_str());
