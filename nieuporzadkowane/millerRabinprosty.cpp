#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

unsigned long long losowanie(unsigned long long int poczatek, unsigned long long int koniec)
{
	unsigned long long int przypadkowa=rand();
	return poczatek+(przypadkowa%(koniec-poczatek));
}

unsigned long long int potega_modulo(unsigned long long int podstawa,unsigned long long int wykladnik, unsigned long long int modulnik)
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
	srand( time( NULL ) );
	unsigned long long int n;
	unsigned long long int k;
	unsigned long long int t;
	int s;
	unsigned long long int a;
	unsigned long long int x;
	int i;
	int counter=0;
	bool test;
	cout<<"Wprowadz liczbe n - ktorej pierwszosc badamy"<<endl;
	cin>>n;
	cout<<"Wprowadz liczbe prob - k"<<endl;
	cin>>k;
	t=n-1;
	s=0;
	do 
	{
		s=s+1;
		t=t/2;
	} while(t%2==0);
	test=true;
	cout<<s<<"    "<<t<<endl;
	for (int j=0;j<k;j++)
	{
		a=losowanie(2,n-1);
		{
			x=potega_modulo(a,t,n);
			if(x==1)
			{
				continue;
			}
			else
			{
				i=0;
				while(x!=(n-1))
				{
					x=mnozenie_modulo(x,x,n);
					i=i+1;
				}
				if((i==s)|(x==1))
				{
					cout<<"liczba jest zlozona "<<endl;
				}
			}
		}
	}


	return 0;
}
