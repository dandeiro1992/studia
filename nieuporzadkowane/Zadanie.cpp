#include "Matrix.h"
#include "HillCipher.h"
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
std::map <string,int> mapa;
double d = 0;

double det(int n, double **mat)//[3][3])
{
    int c, subi, i, j, subj;
    //double submat[3][3];
        double **submat = new double *[n];
        for ( int i = 0; i < n; ++i )
        {
        submat[i] = new double [n];
        }
    if (n == 2)
    {
        return( (mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
    }
    else
    {
        for(c = 0; c < n; c++)
        {
            subi = 0;
            for(i = 1; i < n; i++)
            {
                subj = 0;
                for(j = 0; j < n; j++)
                {
                    if (j == c)
                    {
                        continue;
                    }
                    submat[subi][subj] = mat[i][j];
                    subj++;
                }
                subi++;
            }
        d = d + (pow(-1 ,c) * mat[0][c] * det(n - 1 ,submat));
        }
    }
    return d;
}
int main()
{
    double tmp;
    int tmp2,dlugosc_text;
    int i=0;
    ifstream alfabet;
    ifstream klucz;
    ifstream tekst_jawny;
    alfabet.open("alfabet.txt",ios_base::in);
    klucz.open("klucz.txt",ios_base::in);
    tekst_jawny.open("tekst.txt",ios_base::in);
    string s;
    string key;
    string text;
    getline(alfabet,s);
    getline (klucz,key);
    getline (tekst_jawny,text);
    cout<<s<<endl;
    cout<<key<<endl;
    cout<<text<<endl;
    dlugosc_text=text.length();
    tmp=key.length();
    tmp=sqrt(tmp);
    tmp=pow(tmp,2);
    tmp2=(int)tmp;
    if(tmp2!=key.length())
    {
        cout<<"nie da rady"<<endl;
    }
    else
    {

         while(alfabet.good())
    {
        mapa.insert(std::pair <string,int>(s,i));
        getline(alfabet,s);
        cout<<s;
        i++;
    }
    alfabet.close();

    for (std::map<string,int>::iterator it=mapa.begin(); it!=mapa.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';




    cout<<"zaczynam przypisywac"<<endl;
    Wector wektor(dlugosc_text);
    wektor.przypisanie(text,mapa);
    wektor.wyswietl();
    int rozmiar=(int)(sqrt(tmp));
    cout<<rozmiar<<"   rozmiar"<<endl;
    Matrix macierz(rozmiar);
    macierz.przypisanie(key,mapa);
    cout<<"wypisuje macierz"<<endl;
    macierz.wyswietl();
    Wector wynik(macierz.get_rozmiar(macierz));

    ///////////////////////////////////
    cout<<"mnoze macierze"<<endl;
    HillCipher szyfr;
    //szyfr.Encrypt(macierz,wektor,wynik,mapa,"szyfr.txt");
    szyfr.Decrypt(macierz,wektor,wynik,mapa,"szyfr.txt");
   /* double nowa[3][3];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            nowa[i][j]=(double)macierz.tablica[i][j];
        }

    }
   // cout<<"\ndeterminant"<<det(3,nowa);

    int w=3,k=3;
    double **tab2 = new double *[w]; //alokacja pamieci
for ( int i = 0; i < w; ++i )
{
tab2[i] = new double [k]; //alokacja pamieci
for ( int j = 0; j < k; ++j) //wpisanie wartosci do tablicy
tab2[i][j]=(i+5+j)%4;
}
//wypisz tab2[w][k]
for ( int i = 0; i < w; ++i, cout<<endl )
for ( int j = 0; j < k; ++j)
cout<<tab2[i][j]<<'\t';


cout<<"\ndeterminant"<<det(3,tab2)<<endl;

    macierz.wyswietl();
    cout<<"wyznacznik macierzy z klasy: "<<macierz.det(macierz.rozmiar,macierz.tablica)<<endl;

    cout<<"teraz zrobimy sobie macierz dopelnien"<<endl;
    cout<<macierz.dopelnienie(3,macierz.tablica,0,0)<<endl;
    Matrix pomocnicza(rozmiar);
    for ( int i = 0; i < 3; ++i, cout<<endl )
    for ( int j = 0; j < 3; ++j)
    {
        pomocnicza.tablica[i][j]=macierz.dopelnienie(3,macierz.tablica,i,j);
        cout<<macierz.dopelnienie(3,macierz.tablica,i,j)<<'\t';
    }


    cout<<endl<<endl;
    pomocnicza.wyswietl();
    cout<<endl<<endl;
    pomocnicza.transponowana();
    pomocnicza.wyswietl();
     cout<<endl<<endl;
     macierz.wyswietl();
    macierz.macierz_odwrotna();
    macierz.wyswietl();
    //cout<<"wyznacznik jest rowny"<<macierz.wyznacznik(macierz.tablica,3)<<endl;
    */
    alfabet.close();
    klucz.close();
    tekst_jawny.close();
    }
    return 0;

}
