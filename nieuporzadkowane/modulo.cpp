#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
	
unsigned long long int potega(unsigned long long int podstawa,unsigned long long int wykladnik, unsigned long long int modulnik)
{
	unsigned long long int result=1;
	unsigned long long int a=podstawa%modulnik;
	//cout<<a<<"	a	";
	unsigned long long int x=a;
	//cout<<x<<"	x	";
	int pomoc;
	
	do
	{
		//cout<<"wykladnik jest rowny"<<wykladnik<<endl;
		pomoc=wykladnik%2;
		//cout<<pomoc<<endl;
		if(pomoc==1)
		{
			
			result=result*x;
			result=result%modulnik;
			x=x*x;
			x=x%modulnik;
		}
		else
		{
			x=x*x;
			x=x%modulnik;
		}
		wykladnik>>=1;
		//cout<<"	x	"<<x<<endl;
	}
	while(wykladnik!=0);
	
	return result;
}


unsigned long long int mnozenie_modulo(unsigned long long int a,unsigned long long int b, unsigned long long int modulnik)
{
	unsigned long long int w=0;
	int m=1;
	while(m!=0)
	{
		if((b&m)!=0)
		{
			w=(w+a)%modulnik;
		}
			a<<=1;
			a=a%modulnik;
			m<<=1;
	}
	return w;
}
int main()
{
	unsigned long long int hej=mnozenie_modulo(17,10,3);
	cout<<hej;
	return 0;
}
