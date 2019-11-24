#include "operacje_podstawowe.h"

unsigned int Operacje_podstawowe:: rotright(unsigned int x, int n)
{
	unsigned int r=x<<(32-n);
	unsigned int s=x>>n;
	unsigned int wynik=r|s;
	return wynik;
}

