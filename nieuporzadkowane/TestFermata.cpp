#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

long long int losowanie( long long int poczatek, long long int koniec)
{
	long long int przypadkowa=rand();
	return poczatek+(przypadkowa%(koniec-poczatek));
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

long long int mnozenie_modulo(long long int a,long long int b, long long int modulnik)
{
	long long int w=0;
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
	long long int n;
	long long int a;
	long long int k;
	long long int m;
	m=potega_modulo(540,560,561);
	cout<<m<<endl;
	bool test;
	cout<<"Wprowadz liczbe n - ktorej pierwszosc badamy"<<endl;
	cin>>n;
	cout<<"Wprowadz liczbe prob - k"<<endl;
	cin>>k;

	for(int i=0;i<k;i++)
	{
		a=losowanie(1,n-1);
		if(potega_modulo(a,n-1,n)==1)
		{
			cout<<"i:	"<<i<<"		a:		"<<a<<"potega	"<<potega_modulo(a,n-1,n)<<"		pierwsza"<<endl;
			continue;
		}
		else
		{
			cout<<"swiadek zlozonosci jest rowny "<<a<<"potega	"<<potega_modulo(a,n-1,n)<<endl; break;
		}
	}
	
	return 0;
	
}
