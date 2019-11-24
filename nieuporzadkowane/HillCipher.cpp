#include "HillCipher.h"
#include "Matrix.h"
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <bitset>
#include <math.h>
#define SZYFROWANIE true
#define DESZYFROWANIE false

using namespace std;

HillCipher::HillCipher()
{
    //ctor
}

HillCipher::~HillCipher()
{
    //dtor
}

void HillCipher::Encrypt(Matrix m, Wector w, Wector &wynik,std::map <std::string,int> mapa,string plik)
{
    for(int i=0;i<m.get_rozmiar(m);i++)
    {
        wynik.tablica[i]=0;
    }
    for(int wiersz =0;wiersz<m.get_rozmiar(m);wiersz++)
    {
       for(int kolumna=0;kolumna<m.get_rozmiar(m);kolumna++)
       {
           wynik.tablica[wiersz]+=(w.tablica[kolumna]*m.tablica[wiersz][kolumna]);
       }

    }
    for(int i=0;i<m.get_rozmiar(m);i++)
        wynik.tablica[i]%=26;
    /*cout<<"wyswietlam wynik mnozenia macierzy"<<endl;
    for (int i=0;i<m.get_rozmiar(m);i++)
        cout<<wynik.tablica[i]<<'\t';
*/
    ofstream wynik_szyfr;
    wynik_szyfr.open(plik.c_str(),ios_base::out);
    for(int i=0;i<m.get_rozmiar(m);i++)
    {
        int sprawdzana_liczba=wynik.tablica[i];
        //cout<<sprawdzana_liczba<<endl;
        for(std::map<string,int>::iterator it=mapa.begin();it!=mapa.end();++it)
            {
                 if(sprawdzana_liczba==it->second)
                 {
                    wynik_szyfr<<(it->first);
                    //cout<<it->first;
                    break;
                 }
            }

    }
    wynik_szyfr.close();
}

void HillCipher::Decrypt(Matrix m, Wector w, Wector &wynik,std::map <std::string,int> mapa,string plik)
{
    for(int i=0;i<m.get_rozmiar(m);i++)
    {
        wynik.tablica[i]=0;
    }
    m.macierz_odwrotna();
    for(int wiersz =0;wiersz<m.get_rozmiar(m);wiersz++)
    {
       for(int kolumna=0;kolumna<m.get_rozmiar(m);kolumna++)
       {
           wynik.tablica[wiersz]+=(w.tablica[kolumna]*m.tablica[wiersz][kolumna]);
       }

    }
    for(int i=0;i<m.get_rozmiar(m);i++)
        wynik.tablica[i]%=26;
    /*cout<<"wyswietlam wynik mnozenia macierzy"<<endl;
    for (int i=0;i<m.get_rozmiar(m);i++)
        cout<<wynik.tablica[i]<<'\t';
*/
    ofstream wynik_szyfr;
    wynik_szyfr.open(plik.c_str(),ios_base::out);
    for(int i=0;i<m.get_rozmiar(m);i++)
    {
        int sprawdzana_liczba=wynik.tablica[i];
        //cout<<sprawdzana_liczba<<endl;
        for(std::map<string,int>::iterator it=mapa.begin();it!=mapa.end();++it)
            {
                 if(sprawdzana_liczba==it->second)
                 {
                    wynik_szyfr<<(it->first);
                    //cout<<it->first;
                    break;
                 }
            }

    }
    wynik_szyfr.close();
}
