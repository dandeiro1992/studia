#ifndef PCHOR_H_
#define PCHOR_H_
#include <iostream>
#include "dodatek.h"

using namespace std;

class Podchorazy : public Student{
private:

string stopien;
int kompania;
int pluton;
public:
    Podchorazy (string name, string surname, int age, int k, int p, string st);
    virtual void prezentuj (); // fynkcja która zapyta studenta np o 4 przedmiot a on odpowie angielski i ocene
    virtual void przedstaw_sie();
};


#endif // DODATEK_H_
