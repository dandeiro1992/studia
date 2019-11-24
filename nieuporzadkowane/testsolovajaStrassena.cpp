#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void zamien(long long int pierwsza,long long int druga)
{
	long long int tmp;
	tmp=pierwsza;
	pierwsza=druga;
	druga=tmp;
}
long long int losowanie(long long int poczatek,long long int koniec)
{
	long long int przypadkowa=rand();
	return poczatek+(przypadkowa%(koniec-poczatek));
}
long long int symbol_jacobiego(long long int a,long long int n)
{
//	int wynik=-1;
	if(a<0)
	{
		cout<<"podales bledna liczbe"<<endl;
	}
	if (a==0)
	{
		return 0;
	}
	if ((n%2==1)&&(a>n))
	{
		cout<<"wchodze tu"<<endl;
		return symbol_jacobiego(a%n,n);
	}
	
	if(a==1)
	{
		return 1;
	}
	
	if ((a==2)&&((n%8==1)||(n%8==7)))
	{
		cout<<"a=2, mod8"<<endl;
		return 1;
	}
	
	if ((a==2)&&((n%8==3)||(n%8==5)))
	{
		cout<<"a=2, mod8 i 3"<<endl;
		return -1;
	}
	
	if((a%2==0)&&((n%8==1)||(n%8==7)))
	{
		cout<<"dzielenie"<<endl;
		return symbol_jacobiego(a/2,n);
	}
	else if((a%2==0))
	{
		cout<<"dzielenie z minusikiem"<<endl;
		return -1*symbol_jacobiego(a/2,n);
	}
	
	if((a%4==3)&&(n%4==3))
	{
		cout<<"mod4=3"<<endl;
		
		return -1*symbol_jacobiego(n,a);
	}	
	else
	{
		cout<<"haha"<<endl;
		return symbol_jacobiego(n,a);
	}
	
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


int main()
{
	long long int n;
	long long int b;
	long long int c;
	long long int a;
	cout<<"Test Solovaja Strassena"<<endl;
	cout<<"wprowadz liczbe n do sprawdzenia"<<endl;
	cin>>n;
	a=losowanie(2,n-1);
	cout<<a<<endl;
	b=potega_modulo(a,((n-1)/2),n);
	cout<<"liczba b:	"<<b<<endl;
	c=symbol_jacobiego(a,n);
	cout<<"liczba c:	"<<c<<endl;
	if(b>(n/2))
	{
		b=b-n;
	}
	if (c==b)
	{
		cout<<"n jest liczba pierwsza"<<endl;
	}	
	else
	{
		cout<<"chyba nie"<<endl;
	}
	
	return 0;
}
