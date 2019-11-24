#include <iostream>
#include <string>
#include "dodatek.h"
#include "pchor.h"
using namespace std;

Podchorazy::Podchorazy(string name, string surname, int age, int k, int p, string st) : Student(name, surname, age)
{
    stopien=st;
    kompania=k;
    pluton=p;

}
 void Podchorazy::prezentuj ()
{
    cout<<"Pododzial: "<<pluton<<"pl/"<<kompania<<"kp\nStopien: "<<stopien<<"\n";
    Student::prezentuj();
}
void Podchorazy::przedstaw_sie()
{
    cout<<pluton<<"/"<<kompania<<"\n"<<stopien<<"\n";
    Student::przedstaw_sie();
}

