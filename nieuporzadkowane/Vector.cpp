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

Wector::Wector(int t)
{
    rozmiar=t;
    tablica=new int[t];
}

Wector::~Wector()
{
    //dtor
}

int Wector::get_rozmiar(Wector m)
{
    return m.rozmiar;
}
void Wector::set_rozmiar(int t)
{
    rozmiar=t;
}
void Wector::wyswietl()
{
    for(int i = 0; i < rozmiar; ++i)
        cout<<tablica[i]<<'\t';
    cout<<endl;

}

void Wector::przypisanie(std::string tekst_jawny, std::map <std::string,int> mapa)
{
    for(int i=0;i<rozmiar;i++)
    {
        int tmp=mapa.find(tekst_jawny.substr(i,1))->second;
        tablica[i]=tmp;
    }
}
