#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

long long losowanie( long long int poczatek, long long int koniec)
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
	long long int k;
	long long int t;
	long long int s;
	long long int a;
	long long int x;
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
	for(int i=1;i<=k;i++)
	{
		a=losowanie(2,n-2);
		//a=174;
		cout<<"i:	"<<i<<"	 a:	"<<a<<endl;
		x=potega_modulo(a,t,n);
		if((x==1)||(x==n-1)) continue;
		
		for(int j=1;(j<s)&&(x!=n-1);j++)
		{
			x=mnozenie_modulo(x,x,n);
			if(x==1)
			{
				test=false; break;	
			}
		}
		if(x!=n-1)
		{
			test=false;
			break;
		}
	}
		
	cout<<(test ? "liczba jest pierwsza " :"jest zlozona")<<endl;
	if(test)
	{
		cout<< " z pstwem (1/2)^"<<k<<endl;
	}
	return 0;
}
