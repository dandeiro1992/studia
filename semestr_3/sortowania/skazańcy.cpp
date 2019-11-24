#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
const int k=100;
int t[k],s[k];
void wysw (int t[],int k) {
     for (int i=0;i<k;i++)  printf ("%d=>%d\n",i,t[i]);
     
     }
void dajczapki(int t[], int k) {
     srand( time( NULL ) );
     int los;
     for (int i=0;i<k;i++)
     {t[i]=rand()%2;}
     
     }
     void zgaduj (int t[],  int k) {
         int c,d;
         for (int j=k-1;j>-1;j--){c=0,d=0;
          for (int i=0;i<j;i++){c=c+t[i]; 
          }  
          for (int i=j+1;i<k-1;i++){d=d+s[i]; 
          } d=(d+c)%2; 
        if (j==k-1) { s[j]=c%2; }else {if(s[k-1]==d)s[j]=0; else s[j]=1;  }
        }
          }
          int porownaj (int t[],int s[],int k){int c=0;
              for (int i=0;i<k;i++) {
                  if (t[i]!=s[i])c++;}
             return c; }
int main (void) {
   dajczapki(t,k); 
   
    wysw (t,k); zgaduj(t,k);   wysw (s,k);
    
    printf("Zginelo %d skazancow",porownaj(t,s,k));
    getche();
 return 0;   
}

