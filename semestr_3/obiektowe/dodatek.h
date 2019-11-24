#ifndef DODATEK_H_
#define DODATEK_H_

#include <iostream>

using namespace std;

class Student {
private:
    string imie;
    string nazwisko;
    int wiek;
    struct rygor{
        int numer_przedmiotu;
        string nazwa;
        int ocena;
        rygor *next;
    }*przedmioty ;

public:
    Student();
    Student(string name, string surname, int age);
    int dodajprzedmiot (string n);
    int ocenprzedmiot (int o, int id);
    double srednia ();
    bool zaliczony ();
    void odpowiedz (int id);
    virtual void prezentuj (); // fynkcja która zapyta studenta np o 4 przedmiot a on odpowie angielski i ocene
    virtual void przedstaw_sie();
};

#endif // DODATEK_H_
