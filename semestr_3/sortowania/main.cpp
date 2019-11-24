#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int n1 = 10000, n2 = 100000;

void bubble_asc      (int*, int);
void bubble_desc     (int*, int);
void bubble_asc_wart (int*, int);
void bubble_desc_wart(int*, int);
void wstawianie_asc  (int*, int);
void wstawianie_desc (int*, int);
void shell_asc       (int*, int);
void shell_desc      (int*, int);

void wszystkie_sortowania (int*, int);
void cpy(int *tab1, int *tab2, int n) { for(int i=0;i<n;i++) tab2[i]=tab1[i]; }
void show(int *tab, int n) { for(int i=0;i<n;i++) printf("%d, ", tab[i]); printf("\n"); }

int main()
{
    int tab1[n1], tab2[n1], tab3[n1], tab4[n1], tab5[n1];
    int tab6[n2], tab7[n2], tab8[n2], tab9[n2];
    
    srand(time(0));
    for(int i = 0; i < n1; i++) tab1[i] = rand()%100;
    for(int i = 0; i < n2; i++) tab6[i] = rand()%100;
    
    //for(int i = 0; i < n2; i++) printf("%d\n", tab6[i]);
    //for(int i = 0; i < n1; i++) printf("%d\n", tab1[i]);
    
    //wszystkie_sortowania(tab1, n1);
    wszystkie_sortowania(tab6, n2);
    
    getch();
}

void wszystkie_sortowania(int* tab, int n)
{
    int temp[n];
    cpy(tab, temp, n);
    printf("1. Sortowanie losowej tablicy (%d)\n", n, n);
    
    float czas=clock();
    bubble_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" a) Bubble Sort - czas: %f\n", czas);
    
    cpy(tab, temp, n);
    czas=clock();
    bubble_asc_wart(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" b) Bubble Sort z wartownikiem - czas: %f\n", czas);
    
    cpy(tab, temp, n);
    czas=clock();
    wstawianie_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" c) Przez wstawianie - czas: %f\n", czas);
    
    cpy(tab, temp, n);
    czas=clock();
    shell_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" d) Shell - czas: %f\n", czas);    
    
    /////////////////////////////////////////////////////////////////////////////////
    
    cpy(tab, temp, n);
    bubble_asc_wart(temp, n);    
    printf("2. Sortowanie tablicy posortowanej rosnaco (%d)\n", n);
    
    czas=clock();
    bubble_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" a) Bubble Sort - czas: %f\n", czas);
    
    czas=clock();
    bubble_asc_wart(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" b) Bubble Sort z wartownikiem - czas: %f\n", czas);
    
    czas=clock();
    wstawianie_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" c) Przez wstawianie - czas: %f\n", czas);
    
    czas=clock();
    shell_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" d) Shell - czas: %f\n", czas);
    
    /////////////////////////////////////////////////////////////////////////////////
    
    
    printf("3. Sortowanie tablicy posortowanej malejaca (%d)\n", n);
    
    cpy(tab, temp, n);
    bubble_desc_wart(temp, n);
    czas=clock();
    bubble_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" a) Bubble Sort - czas: %f\n", czas);
    
    cpy(tab, temp, n);
    bubble_desc_wart(temp, n);
    czas=clock();
    bubble_asc_wart(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" b) Bubble Sort z wartownikiem - czas: %f\n", czas);
    
    cpy(tab, temp, n);
    bubble_desc_wart(temp, n);
    czas=clock();
    wstawianie_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" c) Przez wstawianie - czas: %f\n", czas);
    
    cpy(tab, temp, n);
    bubble_desc_wart(temp, n);
    czas=clock();
    shell_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" d) Shell - czas: %f\n", czas);
    
    /////////////////////////////////////////////////////////////////////////////////
    
    printf("4. Sortowanie tablicy posortowanej rosnaco z losowym pierwszym el. (%d)\n", n);
    
    temp[0] = 49;
    czas=clock();
    bubble_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" a) Bubble Sort - czas: %f\n", czas);
    
    temp[0] = 49;
    czas=clock();
    bubble_asc_wart(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" b) Bubble Sort z wartownikiem - czas: %f\n", czas);
    
    temp[0] = 49;
    czas=clock();
    wstawianie_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" c) Przez wstawianie - czas: %f\n", czas);
    
    temp[0] = 49;
    czas=clock();
    shell_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" d) Shell - czas: %f\n", czas);
    
    /////////////////////////////////////////////////////////////////////////////////
    
    cpy(tab, temp, n);
    bubble_asc_wart(temp, n);
    temp[n-1] = 17;
    
    printf("5. Sortowanie tablicy posortowanej rosnaco z losowym ostatnim el. (%d)\n", n);
    
    cpy(tab, temp, n);
    bubble_asc_wart(temp, n);
    temp[n-1] = 17;
    czas=clock();
    bubble_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" a) Bubble Sort - czas: %f\n", czas);
    
    cpy(tab, temp, n);
    bubble_asc_wart(temp, n);
    temp[n-1] = 17;
    czas=clock();
    bubble_asc_wart(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" b) Bubble Sort z wartownikiem - czas: %f\n", czas);
    
    cpy(tab, temp, n);
    bubble_asc_wart(temp, n);
    temp[n-1] = 17;
    czas=clock();
    wstawianie_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" c) Przez wstawianie - czas: %f\n", czas);
    
    cpy(tab, temp, n);
    bubble_asc_wart(temp, n);
    temp[n-1] = 17;
    czas=clock();
    shell_asc(temp, n);
    czas=(clock()-czas)/CLK_TCK;
    printf(" d) Shell - czas: %f\n", czas);
}

void bubble_asc(int *tab, int n)
{
     for(int i=0; i<n; i++)
          for(int j=i; j<n; j++)
          {
               if(tab[i] > tab[j])
               {
                         int temp=tab[i];
                         tab[i]=tab[j];
                         tab[j]=temp;
               }
          }
}

void bubble_desc(int *tab, int n)
{
     for(int i=0; i<n; i++)
          for(int j=i; j<n; j++)
          {
               if(tab[i] < tab[j])
               {
                         int temp=tab[i];
                         tab[i]=tab[j];
                         tab[j]=temp;
               }
          }
}

void bubble_asc_wart(int *tab, int n)
{
     for(int temp,i,j=1;j<=n;j++)
     {
             temp=tab[j];
             tab[0]=tab[j];
             for(i=j-1; (temp < tab[i]) && (i >= 0); i--)
             {
                     tab[i+1]=tab[i];
                     i--;
             }
             tab[i+1]=temp;
     } 
}

void bubble_desc_wart(int *tab, int n)
{
     for(int temp,i,j=1; j<=n; j++)
     {
             temp=tab[j];
             tab[0]=tab[j];
             for(i=j-1; (temp > tab[i]) && (i >= 0); i--)
             {
                     tab[i+1]=tab[i];
                     i--;
             }
             tab[i+1]=temp;
     } 
}


void wstawianie_asc(int* tab, int n)
{
     for(int j,temp,i=n-2; i>=0; i--)
     {
           temp = tab[i];
           for(j=i+1; (j < n) && (temp > tab[j]); j++) tab[j-1] = tab[j];
           tab[j-1] = temp;
     }
}

void wstawianie_desc(int* tab, int n)
{
     for(int j,temp,i=n-2; i>=0; i--)
     {
           temp = tab[i];
           for(j=i+1; (j < n) && (temp < tab[j]); j++) tab[j-1] = tab[j];
           tab[j-1] = temp;
     }
}

void shell_asc(int* tab, int n)
{
     for(int i=n/2; i>0; i/=2)
        for(int k,temp,j=n-i-1; j>=0; j--)
        {
            temp = tab[j];
            for(k=i+j; (k < n) && !(temp <= tab[k]); k += i) tab[k-i] = tab[k];
            tab[k-i] = temp;
        }
}

void shell_desc(int* tab, int n)
{
     for(int i=n/2; i>0; i/=2)
        for(int k,temp,j=n-i-1; j>=0; j--)
        {
            temp = tab[j];
            for(k=i+j; (k < n) && !(temp > tab[k]); k += i) tab[k-i] = tab[k];
            tab[k-i] = temp;
        }
}
