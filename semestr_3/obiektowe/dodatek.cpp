#include <iostream>
#include "dodatek.h"
using namespace std;

Student::Student()
{
    przedmioty=NULL;
}
Student::Student(string name, string surname,int age)
{
    imie=name;
    nazwisko=surname;
    wiek=age;
    przedmioty=NULL;
}

int Student::dodajprzedmiot( string n)
{
    if (przedmioty==NULL )
    {
        przedmioty= new rygor;
        przedmioty->nazwa=n;
        przedmioty->numer_przedmiotu=0;
        przedmioty->next=NULL;
        przedmioty->ocena=0;
    }
    else
    {
        rygor *p=przedmioty;
        while (p->next!=NULL)
            p=p->next;

        p->next=new rygor;
        p->next->nazwa=n;
        p->next->numer_przedmiotu=p->numer_przedmiotu+1;
        p->next->next=NULL;
        p->next->ocena=0;
    }
}
int Student::ocenprzedmiot (int o, int id)
{
    rygor *p=przedmioty;
    while(p!=NULL && p->numer_przedmiotu<id) p=p->next;
    if(p==NULL) return -1;
    else
    {
        p->ocena=o;
        return 0;
    }
    }

double Student::srednia()
{
    rygor *p=przedmioty;
    double suma;
    int i=0;
    if (p==NULL)
        return 0.0;
    else
        {
            while (p!=NULL)
            {
                 suma+=(double) p->ocena;
                 p=p->next;
                 i++;
            }
            return   suma/(double) i;
        }
}
bool Student::zaliczony(){}
void Student::odpowiedz(int id){}
void Student::prezentuj()
{
    cout<<"Imie i nazwisko: "<<imie<<" "<<nazwisko<<"\nWiek: "<<wiek<<"\n";
    rygor *p=przedmioty;
    while (p!=NULL)
    {
        cout<<p->nazwa<<" "<<p->ocena<<endl;
        p=p->next;
    }
    cout<<"Srednia: "<<srednia()<<endl<<endl;
}

void Student::przedstaw_sie ()
{
    cout<<imie<<" "<<nazwisko<<"\n"<<wiek<<"\n\n";
}






