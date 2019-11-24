// Test Millera-Rabina
// Data   : 6.04.2008
// (C)2012 mgr Jerzy Wa³aszek
//----------------------------

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

typedef unsigned long long ulong;

// 64 bitowy generator pseudolosowy
//---------------------------------
ulong Losuj(ulong a,ulong b)
{
  ulong w;
  int i;

  for(i = 1; i <= 8; i++)
  {
    w <<= 8;
    w |= rand() % 256;
  }
  return a + (w % (b - a));
}

// Funkcja mno¿y a i b mod n
//--------------------------
ulong MnozModulo(ulong a, ulong b, ulong n)
{
  ulong m,w;

  w = 0;
  for(m = 1; m; m <<= 1)
  {
    if(b & m) w = (w + a) % n;
    a = (a << 1) % n;
  }
  return w;
}

// Funkcja oblicza a^e mod n
//--------------------------
ulong PotegujModulo(ulong a, ulong e, ulong n)
{
  ulong m,p,w;

  p = a; w = 1;
  for(m = 1; m; m <<= 1)
  {
    if(e & m) w = MnozModulo(w,p,n);
    p = MnozModulo(p,p,n);
  }
  return w;
}

int main()
{
  ulong a,d,p,x;
  int i,j,s,n;
  bool t;

  srand((unsigned)time(NULL));
  cin >> p >> n;
  s = 0;
  for(d = p - 1; d % 2 == 0; s++) d /= 2;
  t = true;
  for(i = 1; i <= n; i++)
  {
    a = Losuj(2,p-2);
    x = PotegujModulo(a,d,p);
    if((x == 1) || (x == p - 1)) continue;
    for(j = 1; (j < s) && (x != p - 1); j++)
    {
      x = MnozModulo(x,x,p);
      if(x == 1)
      {
        t = false; break;
      }
    }
    if(!t) break;
    if(x != p - 1)
    {
      t = false; break;
    }
  }
  cout << (t ? "TAK" : "NIE") << endl;
  return 0;
} 
