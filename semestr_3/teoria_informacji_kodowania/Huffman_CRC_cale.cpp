#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <math.h>

using namespace std;
struct drz{
    int ojciec;
    int lewy;
    int prawy;
};
struct tk{
    int symbol;
    string kod;
    int dlkodu;
};
struct maxin{
    int maxx;
    int minn;
    int koniec;
    int pocz;
};
int str2int(string tekst){
    int liczba;
    stringstream konwersja(tekst);
    konwersja>>liczba;
    return liczba;
}
void sortujTabKodowa(int tab[],int znak[], int n){
    int temp;
    for(int j=n-1; j>0; j--)
        for (int i=0; i<j; i++){
            if (tab[i]>tab[i+1]){
            swap(tab[i], tab[i+1]);
            swap(znak[i], znak[i+1]);
        }
    }
}
int wyszukajBajty(int znaki[],int tab[],int licznik,string s){
    char c,znak[256];
    int i,flaga;
    ifstream wejscie;
    wejscie.open(s.c_str(),ifstream::binary);
		while (!wejscie.eof()){
			c=wejscie.get();
			if(!wejscie.eof()){
			i=0;
			flaga=1;
			while(flaga && i<licznik+1){
				if(znak[i]==c){
					tab[i]++;
					flaga=0;
				}
				else{
					if(i==licznik){
						znak[licznik]=c;
						znaki[licznik]=(signed char)znak[licznik];
						tab[licznik]++;
						licznik++;
						flaga=0;
                    }
                }
            i++;
            }
        }}
    wejscie.close();
    sortujTabKodowa(tab,znaki,licznik);
    return licznik;
}
int b_drzewa(struct drz drzewo[],int znaki[],int tab[],int licznik){
  	int i=0;
  	int dodatek=0;
    while(i<licznik){
        drzewo[i].ojciec=257+i;
        drzewo[i].lewy=znaki[i];
        drzewo[i].prawy=znaki[i+1];
        znaki[i+1]=257+i;
        tab[i+1]+=tab[i];
        tab[i]=0;
        sortujTabKodowa(tab,znaki,licznik);
        i++;
    }
    return (i);
}
int b_tabkodowej(struct tk tabk[],struct drz drzewo[],int licznik){
    struct tk tabkodowa[512];
    int i=0,j=0,k=0;
    if(licznik>1){
        tabkodowa[0].symbol=drzewo[licznik-2].ojciec;
        tabkodowa[0].kod="1";
        tabkodowa[0].dlkodu=tabkodowa[0].kod.size();
        for(i=0;i<licznik-1+licznik;i++){
            for(k=0;k<licznik-1;k++){
                if(tabkodowa[i].symbol==drzewo[licznik-2-k].ojciec){
                    tabkodowa[j+1].symbol=drzewo[licznik-2-k].lewy;
                    tabkodowa[j+2].symbol=drzewo[licznik-2-k].prawy;
                    tabkodowa[j+1].kod=tabkodowa[i].kod+"0";
                    tabkodowa[j+2].kod=tabkodowa[i].kod+"1";
                    tabkodowa[j+1].dlkodu=tabkodowa[j+1].kod.size();
                    tabkodowa[j+2].dlkodu=tabkodowa[j+2].kod.size();
                    j=j+2;
                    break;
                }
            }
        }
        j=0;
        for(i=0;i<2*licznik-1;i++){
            if(tabkodowa[i].symbol<257){
                tabk[j].symbol=tabkodowa[i].symbol;
                tabk[j].kod=tabkodowa[i].kod;
                tabk[j].dlkodu=tabkodowa[i].dlkodu;
                j++;
            }
        }
        return j;
    }
    else{
        tabk[0].symbol=drzewo[0].lewy;
        tabk[0].kod="1";
        tabk[0].dlkodu=1;
        return 1;
    }
}

int wylicz_crc32(char bajt,int crc32){
    bool jest=false;
    int i;
    char tmpb;
    int tmp;
    for(i=0;i<8;i++){
        if(crc32&0x80000000)jest=true;
        else jest=false;
        crc32<<=1;
        crc32&=0xfffffffe;
        tmpb=bajt>>(7-i);
        tmpb=tmpb&0x01;
        crc32|=(int)tmpb;
        if(jest)crc32^=0x04c11db7;
    }
    return crc32;
}

int strbin2int(string bin){
	int dec=0,size1,size2,i=0;
	size1=size2=bin.length()-1;
	if(bin[i]=='1')dec-=pow(2,size2--);
	else size2--;
	for(i=1;i<=size1;++i)
        if(bin[i]=='1')dec+=pow(2,size2--);
        else size2--;
	return dec;
}
int strbin22int(string bin){
	int dec=0,size1,size2,i=0;
	i=bin.length()-1;
	string tmp="0";
	for(i;i<32;i++){
        tmp+="0";
	}
    tmp+=bin;
    bin=tmp;
    size1=size2=bin.length()-1;
	for(i=1;i<=size1;++i)
        if(bin[i]=='1')dec+=pow(2,size2--);
        else size2--;
	return dec;
}
string odciecie_roz(string s){
    int i,kropka;
    string z;
    for(i=0;i<s.size();i++){
        if(s[i]=='.')kropka=i;
    }
    if(kropka!=0)z.assign(s,0,kropka);
    else z=s;
    return z;
}

string s_roz(string s){
    int i,kropka;
    string z;
    for(i=0;i<s.size();i++){
        if(s[i]=='.')kropka=i;
    }
    if(kropka!=0)z.assign(s,kropka,s.size());
    return z;
}
int zapis_komp(string s,string z,struct tk tabkodowa[],int licznik,int crc32){
    int i,tmp,tmp2,zwrot;
    string kod,kod2;
    ofstream wyjscie;
    ifstream wejscie;
    wyjscie.open(z.c_str(),ifstream::binary);
    wyjscie.put((char)0);
    wyjscie.write((char*)&crc32,sizeof(int));
    wyjscie.put((unsigned char)licznik-1);
    for(i=0;i<licznik;i++){
        wyjscie.put((char)tabkodowa[i].symbol);
        tmp=strbin22int(tabkodowa[i].kod);
        wyjscie.write((char*)&tmp,sizeof(int));
    }

    wejscie.open(s.c_str(),ifstream::binary);
    while(!wejscie.eof()){
        tmp2=(signed char)wejscie.get();
        if(wejscie.eof())break;
        for(i=0;i<licznik;i++){
            if(tmp2==tabkodowa[i].symbol)kod+=tabkodowa[i].kod;
        }
        tmp=kod.size();
        while(tmp>=8){
            kod2.assign(kod.c_str(),8);
            kod.assign(kod.c_str(),8,tmp-8);
            tmp2=strbin2int(kod2);
            wyjscie.put((char)tmp2);
            tmp=kod.size();
        }
    }
    i=kod.size();
    tmp=i;
    for(i;i<8;i++){
        kod+="0";
    }
    tmp2=strbin2int(kod);
    wyjscie.put((char)tmp2);
    zwrot=wyjscie.tellp();
    wyjscie.seekp(0);
    wyjscie.put((char)8-tmp);
    wyjscie.close();
    wejscie.close();
    return zwrot;
}
string int2bin(int liczba){
    string kod;
    while(liczba){
        if(liczba%2)kod="1"+kod;
        else kod="0"+kod;
        liczba=liczba/2;
    }
    return kod;
}
string int22bin(int liczba){
    string kod;
    int i;
    int jest=0;
    for(i=0;i<8;i++){
        if(liczba&0x80)jest=1;
        else jest=0;
        liczba<<=1;
        if(jest==1)kod=kod+"1";
        else kod=kod+"0";
    }
    return kod;
}
struct maxin odczyt_tablicy(string s,struct tk tabkodowa[],int licznik,int seek){
    struct maxin minax;
    int i,tmp;
    ifstream wejscie;
    wejscie.open(s.c_str(),ifstream::binary);
    wejscie.seekg(0,wejscie.end);
    minax.koniec=wejscie.tellg();
    wejscie.close();
    wejscie.open(s.c_str(),ifstream::binary);
    wejscie.seekg(seek,wejscie.beg);
    for(i=0;i<licznik;i++){
        tabkodowa[i].symbol=(signed char)wejscie.get();
        wejscie.read((char*)&tmp,4);
        tmp>>=1;
        tabkodowa[i].kod=int2bin(tmp);
        if(i==0)minax.minn=tabkodowa[i].dlkodu=tabkodowa[i].kod.size();
        else if(i==licznik-1) minax.maxx=tabkodowa[i].dlkodu=tabkodowa[i].kod.size();
        else tabkodowa[i].dlkodu=tabkodowa[i].kod.size();
    }
    minax.pocz=wejscie.tellg();
    minax.koniec-=wejscie.tellg();
    wejscie.close();
    return minax;
}

int dekompresja(string s,string e,struct maxin minax,int licznik,int bonus,struct tk tabkodowa[]){
    int i=0,found=0,j=0,tmp,tmp2,symbol;
    string kod,kod2;
    ifstream wejscie;
    wejscie.open(s.c_str(),ifstream::binary);
    wejscie.seekg(minax.pocz,wejscie.beg);
    ofstream wyjscie;
    wyjscie.open(e.c_str(),ifstream::binary);
    while(minax.koniec){
        if(!found&&(kod.size()<minax.maxx)){
            tmp=(unsigned char)wejscie.get();
            kod+=int22bin(tmp);
            minax.koniec--;
        }
        if(minax.minn>8)j=8; else j=minax.minn-1;
        tmp2=kod.size();
        while(j<=tmp2&&!found){
            i=0;
            j++;
            while(i<licznik&&!found){
                    kod2.assign(kod.c_str(),j);
                if(kod2==tabkodowa[i].kod){
                    found=1;
                    symbol=(char)tabkodowa[i].symbol;
                }
                i++;
            }
        }
        if(found){
            kod2.assign(kod.c_str(),j);
            kod.assign(kod.c_str(),j,tmp2-j);
            wyjscie.put(symbol);
            found=0;
        }
    }
    kod.assign(kod.c_str(),kod.size()-bonus);
    while(kod.size()){
        if(minax.minn>8)j=8; else j=minax.minn-1;
        tmp2=kod.size();
        while(j<=tmp2&&!found){
            i=0;
            j++;
            while(i<licznik&&!found){
                    kod2.assign(kod.c_str(),j);
                if(kod2==tabkodowa[i].kod){
                    found=1;
                    symbol=(char)tabkodowa[i].symbol;
                }
                i++;
            }
        }
        if(found){
            kod2.assign(kod.c_str(),j);
            kod.assign(kod.c_str(),j,tmp2-j);
            wyjscie.put(symbol);
            found=0;
        }
    }
    tmp=wyjscie.tellp();
    wejscie.close();
    wyjscie.close();
    return tmp;
}

int main(){
    struct drz drzewo[512];
    struct tk tabkodowa[256];
    char bajt,symbol;
    string z,s,tmps,e,kod,kod2;
	int i,suma=0,licznik=0,tab[256],znaki[256],wykonanie=0,crcstare,bonus,tmp,found=0,tmp2,minn=0,maxx=0,koniec,flaga=0,tryb=1;
	int crc32=0;
	while(tryb){
		cout<<endl<<"[1] - kodowanie"<<endl;
		cout<<"[2] - dekodowanie"<<endl;
		cout<<"[0] - koniec"<<endl;
		cin>>tryb;
		if (tryb==0) return 0;
		cout<<"Podaj nazwe pliku "<<endl;
		cin>>s;
	    if(tryb==1){
	        ifstream spr;
	        spr.open(s.c_str(),ifstream::binary);
	        if(spr.is_open()){
	            cout<<"Plik do kompresji: "<<s<<endl<<endl;
	            cout<<"Obliczanie CRC32."<<endl;
	            ifstream wejscie;
	            wejscie.open(s.c_str(),ifstream::binary);
	            while(wejscie.good()){
	                bajt=wejscie.get();
	                crc32=wylicz_crc32(bajt,crc32);
	            }
	            for(i=0;i<4;i++){
	                crc32=wylicz_crc32(0,crc32);
	            }
	            wejscie.close();
	            cout<<"CRC32= "<<crc32<<endl<<endl;
	            cout<<"Budowanie modelu zrodla."<<endl;
	            licznik=wyszukajBajty(znaki,tab,licznik,s);
	            for(i=0;i<=licznik-1;i++) suma=suma+tab[i];
	            cout<<"wszystkich symboli: "<<suma<<endl<<"rodzaji symboli:"<<licznik<<endl<<endl;
	            cout<<"Budowanie drzewa."<<endl;
	            tmp=b_drzewa(drzewo,znaki,tab,licznik);
	            cout<<"symboli dodatkowych :"<<tmp<<endl<<endl;
	            cout<<"Budowanie tabeli kodowej."<<endl;
	            tmp=b_tabkodowej(tabkodowa,drzewo,licznik);
	            cout<<"Rozmiar tabeli kodowej:"<<tmp<<endl<<endl;
	            z=odciecie_roz(s);
	            z+=s_roz(s);
	            z+="1";
	            cout<<"Kompresja pliku."<<endl;
	            tmp=zapis_komp(s,z,tabkodowa,licznik,crc32);
	            cout<<"Zapisane bajty do pliku *.huff : "<<tmp<<endl<<endl;
	            cout<<"nazwa pliku skompresowanego: "<<z<<endl;
	            cout<<"stopien kompresji: "<<(float)tmp/suma*100<<" %"<<endl;
	            cout<<"Zapisane CRC32: "<<crc32<<endl;
	        }
	        else cout<<"Blad! Nie znaleziono pliku do kompresji"<<endl<<endl;
	        wykonanie=1;
	        spr.close();
	    }
	    else if(tryb==2){
	        struct maxin minax;
	        ifstream spr;
	        spr.open(s.c_str(),ifstream::binary);
	        if(spr.is_open()){
	            cout<<"Plik do dekompresji: "<<s<<endl<<endl;
	            ifstream wejscie;
	            wejscie.open(s.c_str(),ifstream::binary);
	            bonus=wejscie.get();
	            cout<<"Odczyt CRC32."<<endl;
	            wejscie.read((char*)&crcstare,4);
	            cout<<"odczytane CRC32: "<<crcstare<<endl<<endl;
	            licznik=(unsigned char)wejscie.get();
	            licznik++;
	            tmp=wejscie.tellg();
	            wejscie.close();
	            cout<<"Odczyt tabeli kodowej."<<endl;
	            minax=odczyt_tablicy(s,tabkodowa,licznik,tmp);
	            cout<<"liczba elementow tabeli kodowej: "<<licznik<<endl<<endl;
	            e=odciecie_roz(s);
	            e+="_dekodowany";
	            e+=s_roz(s);
	            e.erase(e.length()-1,1);
	            cout<<"dekompresja pliku."<<endl;
	            tmp=dekompresja(s,e,minax,licznik,bonus,tabkodowa);
	            cout<<"dekompresja zakonczona, liczba bajtow pliku *.* : "<<tmp<<s_roz(s)<<endl<<endl;
	            crc32=0;
	            cout<<"obliczanie CRC32 pliku po dekompresji."<<endl;
	            wejscie.open(e.c_str(),ifstream::binary);
	            while(wejscie.good()){
	                bajt=wejscie.get();
	                crc32=wylicz_crc32(bajt,crc32);
	            }
	            for(i=0;i<4;i++){
	                crc32=wylicz_crc32(0,crc32);
	            }
	            wejscie.close();
	            cout<<"nazwa pliku po dekompresji: "<<e<<endl;
	            cout<<"rozmiar pliku po dekompresji: "<<tmp<<endl;
	            if(crc32==crcstare)cout<<"crc zgodne "<<crc32<<"="<<crcstare<<endl<<endl;
	            else cout<<"crc nie zgodnde "<<crc32<<"!="<<crcstare<<endl<<endl;
	            cout<<"Zakonczenie dekompresji."<<endl<<endl;
	        }
	            else cout<<"Blad! Nie znaleziono pliku do kompresji"<<endl<<endl;
	            wykonanie=1;
	    }
	    else if(!wykonanie){
	        cout<<"Blad! nie ma takiego trybu"<<endl;
	        cout<<"Mozliwe tryby:"<<endl;
	        cout<<"[1] - kompresja"<<endl;
	        cout<<"[2] - dekompresja"<<endl;
	        cout<<"[0] - wyjscie"<<endl;
	        cout<<"podaj poprawny tryb!"<<endl;
	        wykonanie=1;
	    }
    }
return 0;
}
