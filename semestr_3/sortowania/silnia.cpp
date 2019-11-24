#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <math.h>
using namespace std;
string dodaj(string liczbaa, string liczbab)
{
    int da = liczbaa.length() - 1;
    int db = liczbab.length() - 1;
    string wynik = "";
    int p = 0;
    while(da >= 0 || db >= 0)
    {
        int ca, cb, w;
       if(da >= 0) ca = liczbaa[da] - 48; else ca = 0;
        if(db >= 0) cb = liczbab[db] - 48; else cb = 0;
               w = ca + cb + p;
        wynik = "0" + wynik;
        wynik[0] = 48 + w % 10;
       p = w / 10;

      da--; db--;
    }
   
    if(p) wynik = "1" + wynik;

    return wynik;
}
   string zm (string liczba1) {
            int poz = liczba1.length() - 1;
            while ((liczba1[poz])==48 &&(poz>=0)){
                            
                            liczba1[poz]=57;
                            poz--;} if (poz>=0){liczba1[poz]--;} poz=0;
                           while (liczba1[poz]==48)liczba1.erase(0,1);
           return liczba1;
           }
string mnoz2 (string liczba,string liczba1) {int x;
    
                     int poz = liczba1.length() - 1;
                    
                     if (liczba1[poz]>48){liczba1[poz]--;} 
                     else {
                     liczba1= zm (liczba1);   }
                     if ((poz<0)||((liczba1[poz]==48)&&(poz==0))){ return liczba;cout<<liczba1[poz]<<endl; }else{return dodaj(mnoz2 (liczba,liczba1),liczba);}
    
     }
 

long double stirling (int liczba) {
     return pow(liczba/M_E,liczba)*sqrt(2*M_PI*liczba);
     }
     

     string silnia (string liczba){
        string  liczba1=liczba;
         int poz = liczba1.length() - 1;
                    
                     if (liczba1[poz]>48){liczba1[poz]--;} 
                     else {
                     liczba1= zm (liczba1);   }
                     if ((poz<0)||((liczba1[poz]==48)&&(poz==0))){ return liczba;cout<<liczba1[poz]<<endl; }else{return mnoz2(silnia(liczba1),liczba);}
    
     }
     string postac (string liczba) 
     {
            return liczba.substr(0,1)+"."+liczba.substr(1,5)+"e+";
            
            }
int main (void) {
 int liczba;
 string liczba2;
 cin >>liczba2;
string liczba3=silnia(liczba2);
 cout<<postac(liczba3)<<liczba3.length()-1<<endl;   
     cout<<stirling(atoi(liczba2.c_str()))<<endl;  
    getche();
    
     return 0;
    
}

