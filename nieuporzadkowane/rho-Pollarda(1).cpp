/////////////////////algorytm rho-Pollarda 	Damian Krata I4D1S1

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

long long int NWD(long long int a, long long int b)
{
	if(b==0)
	return a;
	else return NWD(b,a%b);
}
long long int potega_modulo(long long int podstawa,long long int wykladnik, long long int modulnik)
{
	long long int result=1;
	long long int a=podstawa%modulnik;
	//cout<<a<<"	a	";
	long long int x=a;
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
long long int absolute(long long int a)
{
	if(a>=0)
	{
		return a;
	}
	else
	return -a;
}


int main()
{
    long long int a, b;
	long long int d;
	long long int n;
	a=2;
	b=2;
	d=1;
	cout<<"Wprowadz liczbe n "<<endl;
	cin>>n;
	
	while (d==1)
	{
		a=potega_modulo(a,2,n);
		b=(potega_modulo(b,2,n)+2)%n;
		b=(potega_modulo(b,2,n)+2)%n;
		d=NWD(absolute(a-b),n);
		if((d>1)&&(d<n))
		{
			cout<<"liczba d:	"<<d<<endl;
		}
		if (d==n)
		{
			cout<<"porazka	-1"<<endl;
			break;
		}
	}
	
  
    return 0;
} 
