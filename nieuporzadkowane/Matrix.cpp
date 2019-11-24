#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <bitset>
#include <math.h>
#define SZYFROWANIE true
#define DESZYFROWANIE false
using namespace std;
//Matrix::Matrix()
//{
    //ctor
//}
Matrix::Matrix(int t)
{
    rozmiar=t;
    tablica=new int*[t];
    for(int i=0;i<t;i++)
    {
        tablica[i]=new int [t];
    }
}
Matrix::~Matrix()
{
    //dtor
}

int Matrix::get_rozmiar(Matrix m)
{
    return m.rozmiar;
}
void Matrix::set_rozmiar(int t)
{
    rozmiar=t;
}
bool Matrix::czy_odwracalna(Matrix m)
{

}
void Matrix::przypisanie(std::string key, std::map <std::string,int> mapa)
{
    for (int wiersz=0;wiersz<rozmiar;wiersz++)
    {
        for(int kolumna=0;kolumna<rozmiar;kolumna++)
        {
            int tmp=mapa.find(key.substr(wiersz*3+kolumna,1))->second;
            tablica[wiersz][kolumna]=tmp;
        }
    }
}

void Matrix::wyswietl()
{
    for(int i = 0; i < rozmiar; ++i, std::cout<<std::endl )
        for(int j = 0; j < rozmiar; ++j)
                std::cout<<tablica[i][j]<<'\t';

}
int Matrix::NWD(int a, int b)
{
    while(a!=b)
       if(a>b)
           a-=b;
       else
           b-=a;
    return a;
}
int Matrix::odwrotnosc (int liczba)
{
        int wynik=liczba;
        for(int i=1;i<11;i++)
        {
            wynik=(wynik*liczba)%26;
        }
        return wynik;
}

int Matrix::dopelnienie(int n, int **mat, int wiersz, int kolumna)
{
    int d=0;
    int przeskok_wiersz=0;
    int przeskok_kolumna=0;
    int **submat=new int*[n-1];
    for(int i=0;i<n-1;i++)
        submat[i]=new int[n-1];

    for(int i=0;i<n;i++)
    {
        if(i==wiersz)
        {
            przeskok_wiersz=1;
            continue;
        }
        przeskok_kolumna=0;
        for(int j=0;j<n;j++)
        {
            if(j==kolumna)
            {
                przeskok_kolumna=1;
                continue;
            }
            submat[i-przeskok_wiersz][j-przeskok_kolumna]=mat[i][j];
        }
    }

    d=(((int)(pow(-1,wiersz+kolumna)*det(n-1,submat)))%26);
    if(d<0)
        d+=26;
    return d;

}
void Matrix::transponowana()
{
    int tmp;
    for (int i=0;i<rozmiar;i++)
    {
        for(int j=i;j<rozmiar;j++)
        {
            tmp=tablica[i][j];
            tablica[i][j]=tablica[j][i];
            tablica[j][i]=tmp;
        }
    }

}
int Matrix::det(int n, int **mat)//[3][3])
{
    int d=0;
    int c, subi, i, j, subj;
    //double submat[3][3];
        int **submat = new int *[n];
        for ( int i = 0; i < n; ++i )
        {
        submat[i] = new int [n];
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
        d = ((int)(d + (pow(-1 ,c) * mat[0][c] * det(n - 1 ,submat))))%26;
        }
    }
    if(d<0)
    {
        d+=26;
    }
    return d;
}

void Matrix::macierz_odwrotna()
{
    int **tmp = new int *[rozmiar];
        for ( int i = 0; i < rozmiar; ++i )
        {
            tmp[i] = new int [rozmiar];
        }
    int wyznacznik=det(rozmiar,tablica);
    if(wyznacznik==0)
    {
        cout<<"nie mozna zrobic macierzy odwrotnej"<<endl;
    }
    else if(NWD(wyznacznik,26)!=1)
    {
        cout<<"nie ma elementu odwrotnego do wyznacznika"<<endl;
    }
    else
    {
        for ( int i = 0; i < rozmiar; ++i,cout<<endl)
        {
            for ( int j = 0; j < rozmiar; ++j)
            {
                tmp[i][j]=dopelnienie(rozmiar,tablica,i,j);
                cout<<dopelnienie(rozmiar,tablica,i,j)<<'\t';
            }
        }
         for ( int i = 0; i < rozmiar; ++i)
        {
            for ( int j = 0; j < rozmiar; ++j)
            {
                tablica[i][j]=tmp[i][j];
            }
        }
        cout<<endl;
        transponowana();
        int odwrotnosc_wyznacznik=odwrotnosc(wyznacznik);
        cout<<"odwrotnosc"<<odwrotnosc_wyznacznik<<endl;
        for ( int i = 0; i < rozmiar; ++i)
        {
            for ( int j = 0; j < rozmiar; ++j)
            {
                tablica[i][j]=(tablica[i][j]*odwrotnosc_wyznacznik)%26;
            }
        }

    }


}


