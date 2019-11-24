#include<stdlib.h>
#include <stdio.h>

#define SIZECRC 4
#define degreegen 32
#define kropka 46
#define BUFSIZE 4


int nowa_nazwa(char *nazwa_pliku, char *rozszerzenie, char *nazwa_pliku_nowa) 
{
    int i,n;
   	char *w_nazwy;
    
    for (n=0; n<24; n++)
       nazwa_pliku_nowa[n]=0;

    n=0;
    w_nazwy=nazwa_pliku;
    nazwa_pliku_nowa[0]=*w_nazwy;
    while ((nazwa_pliku_nowa[n]!=kropka)&&(nazwa_pliku_nowa[n]!='\0'))
           {
           n++;
           w_nazwy++;
           nazwa_pliku_nowa[n]=*w_nazwy;
           }
    n++;
    i=0;
    nazwa_pliku_nowa[n]=rozszerzenie[0];
    while (rozszerzenie[i]!='\0')
           {
           n++;
           i++;
           nazwa_pliku_nowa[n]=rozszerzenie[i];
           }         
    return 0;
}    


int dzielenie(char *nazwa_pliku_in, unsigned char reszta[], unsigned char wielomian[])
{
 unsigned char bufor_wejscia[BUFSIZE], kolejka[SIZECRC+BUFSIZE];   
 unsigned char start=0, koniec=0, maska=128, ostatni_bit, pierwszy_bit;
 int n,m;
 int licznik_bitow=0;
 int licznik_bajtow_in=0, licznik_buforu=0;
     
    for (int i=0; i<SIZECRC+BUFSIZE; i++)
       kolejka[i]=0;   
 
    FILE *wskaznik_pliku_in=NULL;
	wskaznik_pliku_in=fopen(nazwa_pliku_in,"rb"); 

    if (wskaznik_pliku_in == NULL)
	{
	  printf("Nie mozna otworzyc pliku: %s  \n", nazwa_pliku_in);
	  exit(EXIT_FAILURE);
	}

    while(n=fread(bufor_wejscia,sizeof(unsigned char),BUFSIZE,wskaznik_pliku_in)) 
    {
        //printf("Return fread %d\n",n);
        for (int i=0; i<n; i++)
                  kolejka[SIZECRC+i]=bufor_wejscia[i];
        licznik_bitow=8*n;
        licznik_bajtow_in+=n;
                
        while (licznik_bitow)
        {
          licznik_buforu=1+(licznik_bitow-1)/8; 
          //printf("Liczba bitow %d. Licznik buforu %d. \n", licznik_bitow, licznik_buforu);
          pierwszy_bit=maska&kolejka[0];    
         
          for (int i=0; i<SIZECRC+licznik_buforu; i++)
               {
                 kolejka[i]=(kolejka[i]<<1);
                 if (i<(SIZECRC+licznik_buforu-1))
                    ostatni_bit=(kolejka[i+1])>>7;
                 else
                    ostatni_bit=0;   
                 kolejka[i]=kolejka[i]|ostatni_bit; 
                 //printf("Bajt %d kolejki po przesunieciu: %#x\n", i, kolejka[i]);
               }
          if (pierwszy_bit!=0)  //jesli pierwszy bit jest jedynka
               for(int i=0; i<SIZECRC; i++)
                  {
                    kolejka[i]=kolejka[i]^wielomian[i];          
                    //printf("Bajt %d kolejki po xorowaniu: %#x\n", i, kolejka[i]);
                  }     
          licznik_bitow--;  
                   
        } // end while                    
    } // end while    
    
    //printf("Sukcesywne dopisywanie degreegen zer na koncu kolejki.\n");
    licznik_bitow=degreegen;
      
        while (licznik_bitow>0)
        {
          //printf("Liczba bitow %d\n", licznik_bitow);

          pierwszy_bit=maska&kolejka[0];    
          //printf("Pierwszy bit %#x\n", pierwszy_bit);  
          for (int i=0; i<SIZECRC; i++)
               {
                 kolejka[i]=(kolejka[i]<<1);
                 ostatni_bit=kolejka[i+1]>>7;
                 kolejka[i]=kolejka[i]|ostatni_bit; 
               }  
              //for(int i=0; i<SIZECRC+n; i++)
              //   printf("Po przesunieciu bajt %d kolejki: %#x\n", i, kolejka[i]);      
          //Zero na koncu jest dopisywane z definicji przesuniecia       
          if (pierwszy_bit!=0)  //jesli pierwszy bit jest jedynka                              
                 for(int i=0; i<SIZECRC; i++)
                 {
                    kolejka[i]=kolejka[i]^wielomian[i];          
                    //printf("Bajt %d kolejki po xorowaniu: %#x\n", i, kolejka[i]);
                 }     
          licznik_bitow--;       
   
        }// end while
 
 for(int i=0; i<SIZECRC; i++)
      reszta[i]=kolejka[i];   
             
 fclose(wskaznik_pliku_in);
                 
 return licznik_bajtow_in;   

}

int main()
{
unsigned char wielomian[SIZECRC], reszta[SIZECRC], reszta2[SIZECRC];
char n_plik[24];
char wartoscCRC[]= "CRC";
char dodaneCRC[]= "zCRC";
char n_plik_CRC[24], n_plik_zCRC[24];
int n, licznik=0 ;
unsigned char bajt_out;
unsigned char bufor_wejscia[BUFSIZE];

wielomian[0]=0x04;
wielomian[1]=0xc1;
wielomian[2]=0x1d;
wielomian[3]=0xb7;

/*
for (int i=0; i<SIZECRC; i++)
   {
    wielomian[i]=0;
   }
*/
for (int i=0; i<SIZECRC; i++)
   {
    //printf("Podaj szesnastkowo %d. bajt wielomianu generujacego: \n", i+1);
    //scanf("%x",&wielomian[i]);
    printf("Wartosc %d. bajtu wielomianu to: %02x\n", i+1, wielomian[i]);
   }


for (int i=0; i<24; i++)
   {
    n_plik[i]=0;
   } 
printf("\nPodaj nazwe pliku, dla ktorego wyznaczana jest CRC:\n");
scanf("%s",n_plik);

printf("\nNazwa przetwarzanego pliku to: %s\n\n", n_plik);   

n=dzielenie(n_plik, reszta,wielomian);
printf("Z pliku %s odczytano %d bajtow.\n\n", n_plik, n);

for(int i=0; i<SIZECRC; i++)
 {  
   bajt_out=reszta[i];
   printf("Bajt %d wartosci CRC: %#x\n", i, reszta[i]);      
//   fwrite(&bajt_out,sizeof(unsigned char),1,wskaznik_pliku_vCRC);   
 }

//fclose(wskaznik_pliku_vCRC);
//printf("Wartosc CRC zostala zapisana do pliku %s\n", n_plik_CRC); 

//Dopisywanie do pliku zrodlowego
FILE *wskaznik_pliku_in=NULL;
wskaznik_pliku_in=fopen(n_plik,"rb"); 

if (wskaznik_pliku_in == NULL)
	{
	  printf("Nie mozna otworzyc pliku: %s  \n", n_plik);
	  exit(EXIT_FAILURE);
	}

n=nowa_nazwa(n_plik, dodaneCRC, n_plik_zCRC);

FILE *wskaznik_pliku_zCRC=NULL;
wskaznik_pliku_zCRC=fopen(n_plik_zCRC,"wb"); 

if (wskaznik_pliku_zCRC == NULL)
  {
   printf("Nie mozna otworzyc pliku: %s \n", n_plik_zCRC);
   exit(EXIT_FAILURE);
  }  
//Przepisywanie pliku
licznik=0;
while(n=fread(bufor_wejscia,sizeof(unsigned char),BUFSIZE,wskaznik_pliku_in)) 
    { 
       for(int i=0; i<n; i++)
		  {
            bajt_out = bufor_wejscia[i];
            fwrite(&bajt_out,sizeof(unsigned char),1,wskaznik_pliku_zCRC); 
          }
      licznik+=n;
    }
 printf("\nPrzepisano %d bajtow do pliku %s\n", licznik, n_plik_zCRC);

fclose(wskaznik_pliku_in);
//Dopisanie CRC

for(int i=0; i<SIZECRC; i++)
 {  
   bajt_out=reszta[i];    
   fwrite(&bajt_out,sizeof(unsigned char),1,wskaznik_pliku_zCRC);   
 }
fclose(wskaznik_pliku_zCRC);
printf("Dopisano %d bajtow CRC do pliku %s\n", SIZECRC, n_plik_zCRC);

   system("PAUSE"); 

//Sprawdzenie CRC pliku z dopisana wartoscia (kodem) CRC
  FILE * pFile;
  long lSize;
  char * buffer;
  size_t result;

  pFile = fopen (n_plik_zCRC , "rb" );
  if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek (pFile , 0 , SEEK_END);
  lSize = ftell (pFile);
  rewind (pFile);

  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // copy the file into the buffer:
  result = fread (buffer,1,lSize,pFile);
  if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

  /* the whole file is now loaded in the memory buffer. */

  // terminate
  fclose (pFile);
  pFile = fopen("aaa.testCRC", "wb");
  fwrite(buffer,sizeof(unsigned char),(lSize-4),pFile);
  fclose (pFile);

  for (int i = 0; i < SIZECRC; i++) reszta2[i] = 0;
  
  printf("\nSprawdzenie wartosci CRC dla pliku %s\n", n_plik_zCRC);   
  n=dzielenie("aaa.testCRC", reszta2,wielomian);
  remove("aaa.testCRC");
  printf("Z pliku %s odczytano %d bajtow.\n\n", n_plik_zCRC, n);
  for(int i=0; i<SIZECRC; i++)
          printf("Bajt %d wartosci CRC: %#x\n", i, reszta2[i]);
  bool czyZgodne = true;
  for (int i = 0; i < SIZECRC; i++){
      if (reszta[i] != reszta2[i]){
                    czyZgodne = false;
                    }
      }
  if (czyZgodne){
      printf ("\nNie stwierdzono naruszenia integralnosci danych.\n\n");
      }
  else {
      printf ("\nStwierdzono naruszenie integralnosci danych.\n\n"); 
      }        
   system("PAUSE");       
   return 0;  
} 
