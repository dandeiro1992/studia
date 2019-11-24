#include <iostream>
#include "dodatek.h"
#include "pchor.h"

using namespace std;


int main()
{
    Student st1("Damian", "Krata", 23);
    Student st2("Robert", "Jarosz", 20);
    Student st3("Grzeniu", "Galkowski", 20);
    Podchorazy pc1("Bartosz", "Grzybowski", 20, 3,1 ,"st. szer. pchor. ");

    st1.przedstaw_sie();

    st2.dodajprzedmiot ("Sluzba powtorkowa");
    st2.dodajprzedmiot ("Programowanie");
    st2.ocenprzedmiot (5,0);
    st2.ocenprzedmiot (4,1);
    st2.prezentuj();

    pc1.dodajprzedmiot("Logistyka");
    pc1.ocenprzedmiot (5,0);
    pc1.prezentuj();


}
