
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <GL/glut.h>


// Definicja stalych
#define LPOZ_MAX            100
#define LPOZ_MIN            4
#define LPION_MAX           100
#define LPION_MIN           3
#define R_MAX               10.0
#define WYS_MAX             5.0
#define KROK_FLOAT          0.1
#define X_OFFSET_SWIATLO    10
#define Y_OFFSET_SWIATLO    120
#define X_OFFSET_MAT        10
#define Y_OFFSET_MAT        220
#define X_OFFSET_OBIEKT     10
#define Y_OFFSET_OBIEKT     300
#define ID_MENU_SWIATLA     0
#define ID_MENU_MATERIALU   1
#define LPOZ_MENU_SWIATLA   10
#define LPOZ_MENU_MATERIALU 5
#define M_PI				3.14159

float OBSERWATOR_ODLEGLOSC   = 35.0;
float OBSERWATOR_OBROT_X     = 20.0;
float OBSERWATOR_OBROT_Y     = 20.0;
float OBSERWATOR_FOV_Y       = 30.0;
float OBSERWATOR_WYSOKOSC    = 5;
float roznica=0.5;
const GLfloat ambient_m1[4] = { 0.5, 0.3 , 0, 1 }; // braz
const GLfloat diffuse_m1[4]  = { 0.5, 0.3, 0, 1 };
const GLfloat specular_m1[4] = { 1, 1, 0, 1 };

const GLfloat ambient_m2[4] = { 1, 0, 0, 1 }; // czerw
const GLfloat diffuse_m2[4]  = { 1, 0, 0, 1 };
const GLfloat specular_m2[4] = { 0, 0, 0, 1 };
//swiatla
const GLfloat ambient_s1[4] = { 1, 1, 1, 1 }; //spot
const GLfloat diffuse_s1[4]  = { 1, 1, 1, 1 };
GLfloat specular_s1[4] = { 0, 0, 0, 1 };
GLfloat position_s1[] = { 5, 0, 0, 1 };
GLfloat direction_s1[] = { -90, 0, 0 };

const GLfloat ambient_s2[4] = {0.5, 0, 0.5, 1 }; //kierunkowe
const GLfloat diffuse_s2[4]  = {0.8, 0.8, 0.8, 1 };
GLfloat specular_s2[4] = { 0, 0, 0, 1 };
GLfloat position_s2[] = { 10, 10, 10, 0 };

// Makro przeliczajace stopnie na radiany
#define DEG2RAD(x)       ((float)(x)*M_PI/180.0)

// Zmienne globalne
double  kat = 0.0;         // Kat obrotu obserwatora wokol osi OY [stopnie]
int     lPionowych;        // Liczba podzialow pionowych 
int     lPoziomych;        // Liczba podzialow poziomych
double  promien;           // Promien walca
double  wysokosc;          // Wysokosc walca
int     sIndeks;           // Wybrana pozycja w tablicy parametrow swiatla
int     mIndeks;           // Wybrana pozycja w tablicy parametrow materialu
int     menu;              // Identyfikator wybranego menu (menu swiatla lub menu materialu) 
int     szerokoscOkna = 800;
int     wysokoscOkna  = 600;
float kat_x = 0,kat_y = 0, kat_z = 0, R_L1 =5;
// Tablica parametrow swiatla
GLfloat swiatlo[10][4];

// Tablica parametrow materialu z jakiego wykonany jest walec
GLfloat material[6][4];
 //Tablice wektorow
float wektor1[3], wektor2[3], wektor3[3];

// Prototypy funkcji
void UstawDomyslneWartosciParametrow(void);
void RysujTekstRastrowy(void *font, char *tekst);
void UstawKolorPozycji(int m, int indeks);
void WlaczOswietlenie(void);
void DefiniujMaterial(void);
void UstawParametryOswietlenia(int indeks, char operacja);
void UstawParametryMaterialu(int indeks, char operacja);
void RysujWalec(double h, double r, int nv, int nh);
void UstawParametryWidoku(int szer, int wys);
void RysujNakladke(void);
void WyswietlObraz(void);
void ObslugaKlawiatury(unsigned char klawisz, int x, int y);
void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y);


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja ustawiajaca domyslne parametry walca, materialu i zrodla swiatla



void UstawDomyslneWartosciParametrow(void)
{
  
  // Parametry walca
  lPionowych = 12;          // Liczba podzialow pionowych 
  lPoziomych = 12;          // Liczba podzialow poziomych
  promien    = 1.0;        // Promien walca
  wysokosc   = 2.0;        // Wysokosc walca  

  // Pozostale parametry
  sIndeks = 0;        // Wybrana pozycja w tablicy parametrow swiatla
  mIndeks = 0;        // Wybrana pozycja w tablicy parametrow materialu
  menu    = ID_MENU_SWIATLA;

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca tekst rastrowy <tekst> za pomca fontow bitmapowych <font>.Rysowanie
// tekstu wykonywane jest poczawszy od biezacej pozycji ekranu.
void RysujTekstRastrowy(void *font, char *tekst)
{
  int i;

  for (i = 0; i < (int)strlen(tekst); i++)
    glutBitmapCharacter(font, tekst[i]);
}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja ustawia kolor dla pozycji <indeks> w  menu <m>. Aktualnie wybrana pozycja 
// jest rysowana w kolorze zoltym.
void UstawKolorPozycji(int m, int indeks)
{
  if (m == menu) 
    if((m == ID_MENU_SWIATLA) && (indeks == sIndeks)
       || (m == ID_MENU_MATERIALU) && (indeks == mIndeks))

    // Pozycja podswietlona wyswietlana jest w kolkorze zoltym
    glColor3f(1.0, 1.0, 0.0);
  else

    // Pozostale na bialo
    glColor3f(1.0, 1.0, 1.0);
}


//////////////////////////////////////////////////////////////////////////////////////////
// Zdefiniowanie walasciwosci materialu walca na podstawie zapisanych w tablcy 'material'
// parametrow (material obowiazuje tylko do scian skierowanych przodem do obserwatora)
void Material1() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_m1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_m1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m1);
    glMaterialf(GL_FRONT, GL_SHININESS,128);
}

void Material2() {
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_m2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_m2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_m2);
    glMaterialf(GL_FRONT, GL_SHININESS, 0);
}

void Swiatlo1() {
    glPushMatrix();
    glEnable(GL_LIGHTING);
	glRotatef(kat_y, 1, 0, 0);
    glRotatef(kat_x, 0, 1, 0);
    glRotatef(kat_z, 0, 0, 1);
    glTranslatef(R_L1, 0, 0);
    glPushMatrix();
       glutWireSphere(0.25, 20, 20);
    glPopMatrix();

    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_s1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_s1);
    glLightfv(GL_LIGHT1, GL_POSITION, position_s1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction_s1);
    glPopMatrix();
}

void Swiatlo2() {

    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_s2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular_s2);
    glLightfv(GL_LIGHT2, GL_POSITION, position_s2);

}

void IloczynWektorowy() {
    wektor3[0] = wektor1[1]*wektor2[2] - wektor2[1]*wektor1[2];
    wektor3[1] = wektor1[2]*wektor2[0] - wektor2[2]*wektor1[0];
    wektor3[2] = wektor1[0]*wektor2[1] - wektor2[0]*wektor1[1];
}


//////////////////////////////////////////////////////////////////////////////////////////
// Ustawienie parametrow materoalu
void UstawParametryMaterialu(int indeks, char operacja)
{
  switch(indeks)
    {
      // Parametry odbicia swiatla swiatla otoczenia, swiatla rozproszonego, swiatla 
      // kierunkowego i emitowanego
    case 0:
    case 1:
    case 2:
    case 4:
      switch(operacja)
	{
	  // Zwiekszenie skladowej R o wartosc KROK_FLOAT
	case '1':
	  material[indeks][0] = (material[indeks][0] >= 1.0) ? 1.0 : material[indeks][0]+ KROK_FLOAT;
	  break;

	  // Zmniejszenie skladowej R o wartosc KROK_FLOAT
	case '!':
	  material[indeks][0] = (material[indeks][0] <= 0.1) ? 0.0 : material[indeks][0]- KROK_FLOAT;
	  break;
	  
	  // Zwiekszenie skladowej G o wartosc KROK_FLOAT
	case '2':
	  material[indeks][1] = (material[indeks][1] >= 1.0) ? 1.0 : material[indeks][1]+ KROK_FLOAT;
	  break;
	  
	  // Zmniejszenie skladowej G o wartosc KROK_FLOAT
	case '@':
	  material[indeks][1] = (material[indeks][1] <= 0.1) ? 0.0 : material[indeks][1]- KROK_FLOAT;
	  break;
	  
	  // Zwiekszenie skladowej B o wartosc KROK_FLOAT
	case '3':
	  material[indeks][2] = (material[indeks][2] >= 1.0) ? 1.0 : material[indeks][2]+ KROK_FLOAT;
	  break;
	  
	  // Zmniejszenie skladowej B o wartosc KROK_FLOAT
	case '#':
	  material[indeks][2] = (material[indeks][2] <= 0.1) ? 0.0 : material[indeks][2]- KROK_FLOAT;
	  break;

	  // Zwiekszenie skladowej A o wartosc KROK_FLOAT
	case '4':
	  material[indeks][3] = (material[indeks][3] >= 1.0) ? 1.0 : material[indeks][3]+ KROK_FLOAT;
	  break;
	  
	  // Zmniejszenie skladowej A o wartosc KROK_FLOAT
	case '$':
	  material[indeks][3] = (material[indeks][3] <= 0.1) ? 0.0 : material[indeks][3]- KROK_FLOAT;
	  break;
	}
      break;

      // Parametr opisujacy polysk powierzchni
    case 3:
      switch(operacja)
	{
	  // Zwiekszenie skladowej R o wartosc KROK_FLOAT*10
	case '1':
	  material[indeks][0] = (material[indeks][0] >= 100.0) ? 100.0 : material[indeks][0]+ KROK_FLOAT * 10.0;
	  break;
	  
	  // Zmniejszenie skladowej R o wartosc KROK_FLOAT*10
	case '!':
	  material[indeks][0] = (material[indeks][0] <= 0.0) ? 0.0 : material[indeks][0]- KROK_FLOAT * 10.0;
	  break;
	}
      break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca walec o zadanej wysokosci, promieniu oraz liczbie podzialow
// pionowych i poziomych. Tryb modelowania powierzchni bocznej  - GL_TRIANGLE_STRIP,
// podstaw - GL_TRIANGLE_FAN.
void RysujWalec(double h, double r, int nv, int nh)
{
  double dH, dAlfa;
  int   i, j,parzystosc=0;


  // Wyznaczenie kata wyznaczajacego pojedynczy wycinek pionowy
  dAlfa = 360.0L/(double)nh;

  // Wyznaczenie wysokosci pojedynczego wycinka poziomego
  dH = h/(double)nv;


  // Wyznaczanie wierzcholkow i wektorow normalnych powierzchni bocznych
  for (i = 0; floor((i+1)*dH*1.0E10) <= floor(h*1.0E10); i++) 
    {
		 if (i%2 == 1) {
            parzystosc = 1;
            } else
            parzystosc = 0;
      glBegin(GL_TRIANGLE_STRIP); 
      glNormal3f(0.0, 0.0, 1.0);
      glVertex3f(0.0, (i + 1)*dH, r);
      glVertex3f(0.0, i*dH, r);

      for (j = 1; j*dAlfa <= 360.0L + dAlfa; j++)
	{
		if (parzystosc%2 == 0) {
               Material1();
                parzystosc = 1;
            } else {
                Material2();
                parzystosc = 0;
            }
	  glNormal3f(sin(DEG2RAD(j*dAlfa)), 0.0, cos(DEG2RAD(j*dAlfa)));
	  glVertex3f(r*sin(DEG2RAD(j*dAlfa)), (i + 1)*dH, r*cos(DEG2RAD(j*dAlfa)));
	  glVertex3f(r*sin(DEG2RAD(j*dAlfa)), i*dH, r*cos(DEG2RAD(j*dAlfa)));
	}
      glEnd();
    }

  
  // Wyznaczenie wierzcholkow i wektorow normalnych dolnej podstawy 
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0.0, -1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  for (i = 0; i * dAlfa <= 360.0L + dAlfa; i++)
  {	   if (i%2 == 1) {
             Material1();
            } else
             Material2();
    glVertex3f(r*sin(DEG2RAD(i*dAlfa)), 0.0, r*cos(DEG2RAD(i*dAlfa)));
}glEnd();  

  // Wyznaczenie wierzcholkow i wektorow normalnych gornej podstawy 
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, h, 0.0);
  for (i = 0; i * dAlfa <= 360.0L + dAlfa; i++){
	  	   if (i%2 == 1) {
             Material1();
            } else
             Material2();
    glVertex3f(r*sin(DEG2RAD(i*dAlfa)), h, r*cos(DEG2RAD(i*dAlfa)));
  }
  
  glEnd(); 
  Swiatlo1();
  Swiatlo2();
}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja ustawiajaca parametry rzutu perspektywicznego i rozmiary viewportu
void UstawParametryWidoku(int szer, int wys)
{
  // Zapamietanie wielkosci widoku
  szerokoscOkna = szer;
  wysokoscOkna  = wys;
glShadeModel(GL_FLAT);
  // Ustawienie parametrow viewportu
  glViewport(0, 0, szerokoscOkna, wysokoscOkna);

  // Przejscie w tryb modyfikacji macierzy rzutowania
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, (float)szerokoscOkna/(float)wysokoscOkna, 1.0, 1000.0);

  // Przejscie w tryb modyfikacji macierzy przeksztalcen geometrycznych
  glMatrixMode(GL_MODELVIEW);

  // Zmiana macierzy znajdujacej sie na wierzcholku stosu na macierz jednostkowa 
  glLoadIdentity();
  
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca na wygenerowanym obrazie walca nkladke z tekstem opisujacym
// aktualne parametry zrodla swiatla i materialu.
void RysujNakladke(void)
{
 char buf[255];

  // Zmiana typu rzutu z perspektywicznego na ortogonalny
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, szerokoscOkna,  0.0, wysokoscOkna,-100.0, 100.0); 
 
  // Modelowanie sceny 2D (zawartosci nakladki)
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // Zablokowanie oswietlenia (mialoby ono wplyw na kolor tekstu)
  glDisable(GL_LIGHTING);

  // Okreslenie koloru tekstu
  glColor3f(1.0, 1.0, 1.0);

 // RYSOWANIE MENU PARAMETROW ZRODLA SWIATLA

  sprintf(buf, "Swiatlo");
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,0);
  sprintf(buf, " - otaczajace  (%.1f, %.1f, %.1f, %.1f)", swiatlo[0][0], swiatlo[0][1], swiatlo[0][2],
	  swiatlo[0][3]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 10);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,1);
  sprintf(buf, " - rozproszone (%.1f, %.1f, %.1f, %.1f)", swiatlo[1][0], swiatlo[1][1], swiatlo[1][2],
	  swiatlo[1][3]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 20);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,2);
  sprintf(buf, " - lustrzane   (%.1f, %.1f, %.1f, %.1f)", swiatlo[2][0], swiatlo[2][1], swiatlo[2][2],
	  swiatlo[2][3]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 30);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,3);
  sprintf(buf, " - polozenie   (%.1f, %.1f, %.1f, %.1f)", swiatlo[3][0], swiatlo[3][1], swiatlo[3][2],
	  swiatlo[3][3]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 40);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,4);
  sprintf(buf, " - kierunek    (%.1f, %.1f, %.1f)", swiatlo[4][0], swiatlo[4][1], swiatlo[4][2]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 50);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,5);
  sprintf(buf, " - tl. katowe  (%.1f)", swiatlo[5][0]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 60);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,6);
  sprintf(buf, " - kat odciecia(%.1f)", swiatlo[6][0]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 70);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,7);
  sprintf(buf, " - tl. stale   (%.2f)", swiatlo[7][0]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 80);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,8);
  sprintf(buf, " - tl. liniowe (%.2f)", swiatlo[8][0]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 90);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_SWIATLA,9);
  sprintf(buf, " - tl. kwadrat.(%.2f)", swiatlo[9][0]);
  glRasterPos2i(X_OFFSET_SWIATLO, Y_OFFSET_SWIATLO - 100);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);


 // RYSOWANIE MENU  PARAMETROW MATERIALU

  glColor3f(1.0, 1.0, 1.0);
  sprintf(buf, "Material");
  glRasterPos2i(X_OFFSET_MAT, Y_OFFSET_MAT);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_MATERIALU,0);
  sprintf(buf, " - otaczajace  (%.1f, %.1f, %.1f, %.1f)", material[0][0], material[0][1], 
	  material[0][2], material[0][3]);
  glRasterPos2i(X_OFFSET_MAT, Y_OFFSET_MAT - 10);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_MATERIALU,1);
  sprintf(buf, " - rozproszone (%.1f, %.1f, %.1f, %.1f)", material[1][0], material[1][1], 
	  material[1][2], material[1][3]);
  glRasterPos2i(X_OFFSET_MAT, Y_OFFSET_MAT - 20);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_MATERIALU,2);
  sprintf(buf, " - kierunkowe  (%.1f, %.1f, %.1f, %.1f)", material[2][0], material[2][1], 
	  material[2][2], material[2][3]);
  glRasterPos2i(X_OFFSET_MAT, Y_OFFSET_MAT - 30);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_MATERIALU,3);
  sprintf(buf, " - polysk      (%.2f)", material[3][0]);
  glRasterPos2i(X_OFFSET_MAT, Y_OFFSET_MAT - 40);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  UstawKolorPozycji(ID_MENU_MATERIALU,4);
  sprintf(buf, " - emitowane   (%.1f, %.1f, %.1f, %.1f)", material[4][0], material[4][1], 
	  material[4][2], material[4][3]);
  glRasterPos2i(X_OFFSET_MAT, Y_OFFSET_MAT - 50);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

 // RYSOWANIE MENU PARAMETROW WALCA

  glColor3f(1.0, 1.0, 1.0);

  sprintf(buf, "Walec:");
  glRasterPos2i(X_OFFSET_OBIEKT, Y_OFFSET_OBIEKT);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  sprintf(buf, " - promien (%.1f)", promien);
  glRasterPos2i(X_OFFSET_OBIEKT, Y_OFFSET_OBIEKT - 10);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  sprintf(buf, " - wysokosc (%.1f)", wysokosc);
  glRasterPos2i(X_OFFSET_OBIEKT, Y_OFFSET_OBIEKT - 20);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  sprintf(buf, " - podzialow pionowych (%d)", lPionowych);
  glRasterPos2i(X_OFFSET_OBIEKT, Y_OFFSET_OBIEKT - 30);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  sprintf(buf, " - podzialow poziomych (%d)", lPoziomych);
  glRasterPos2i(X_OFFSET_OBIEKT, Y_OFFSET_OBIEKT - 40);
  RysujTekstRastrowy(GLUT_BITMAP_8_BY_13, buf);

  // Przywrocenie macierzy sprzed wywolania funkcji
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();  

  // Odblokowanie oswietlenia
  glEnable(GL_LIGHTING);
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja generujaca pojedyncza klatke animacji
void WyswietlObraz(void)
{
  // Wyczyszczenie bufora ramki i bufora glebokosci
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // Okreslenie wielkosci widoku, wlaczenie rzutowania perspektywicznego
  // i zainicjowanie stosu macierzy modelowania
  UstawParametryWidoku(szerokoscOkna, wysokoscOkna);

  // Ustawienie oswietlenia sceny (polozenie zrodla swiatla wyznaczane jest w ukladzie
  // wspolrzednych obserwatora)
 // WlaczOswietlenie();

   /*// Przejscie w tryb modyfikacji macierzy przeksztalcen geometrycznych
    glMatrixMode(GL_MODELVIEW);

    // Zastapienie aktywnej macierzy macierza jednostkowa
    glLoadIdentity();*/
  // Wyznaczenie polozenia obserwatora (przeksztalcenie uladu wspolrzednych 
  // sceny do ukladu wspolrzednych obserwatora). Obserwator obraca sie wokol punktu 0.0
  // na osi OY. Promien obrotu = 20, pochylenie = 20 stopni,
  // predkosc obrotu = 0.25 stopnia/ramke.
   glTranslatef(0, 0, -OBSERWATOR_ODLEGLOSC);
    glRotatef(atan(OBSERWATOR_WYSOKOSC/OBSERWATOR_ODLEGLOSC) * 180/M_PI, 1, 0, 0);
    glRotatef(OBSERWATOR_OBROT_Y, 0, 1, 0);

  // Zdefiniowanie materialu walca
 // DefiniujMaterial();

  // Generacja obrazu walca
  RysujWalec(wysokosc, promien, lPoziomych, lPionowych);

  // Narysowanie tekstow z opisem parametrow oswietlenia i materialu
  RysujNakladke();

  // Przelaczenie buforow ramki
  glutSwapBuffers();

kat_x=kat_x+roznica;
  // Modyfikacja kata obrotu
  //kat += 0.25; 
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{
  switch(klawisz)
    {
		//obserwator
	case '+': OBSERWATOR_ODLEGLOSC++;
        break;
    case '-': OBSERWATOR_ODLEGLOSC--;
        break;
    case 'S': OBSERWATOR_WYSOKOSC++;
        break;
    case 's': OBSERWATOR_WYSOKOSC--;
        break;
    case 'a': OBSERWATOR_OBROT_Y++;
        break;
    case 'd': OBSERWATOR_OBROT_Y--;
        break;
//podzial
    case '2':
      lPionowych = (lPionowych == LPION_MAX)? LPION_MAX : lPionowych + 2;
      break;

    case '@':
      lPionowych = (lPionowych == LPION_MIN)? LPION_MIN : lPionowych - 2;
      break;

    case '1':
      lPoziomych = (lPoziomych == LPOZ_MAX)? LPOZ_MAX : lPoziomych + 2;
      break;

    case '!':
      lPoziomych = (lPoziomych == LPOZ_MIN)? LPOZ_MIN : lPoziomych - 2;
      break;
//wysokosc
    case 'w':
      wysokosc = (wysokosc == WYS_MAX) ? WYS_MAX : wysokosc + 1;
      break;

    case 'W':
      wysokosc = (wysokosc == 1) ? wysokosc : wysokosc - 1;
      break;
//promien walca
    case 'p':
      promien = (promien == R_MAX) ? R_MAX : promien + 1;   
      break;

    case 'P':
      promien = (promien == 1) ? promien : promien - 1;
      break;
//reset
    case 'r':
      UstawDomyslneWartosciParametrow();
      break;

    case 'm':
      menu = (menu == ID_MENU_SWIATLA) ? ID_MENU_MATERIALU : ID_MENU_SWIATLA;
      break;
//predkosc
	case '3':
		if(roznica<2) roznica=roznica+0.5;
		break;
	case '#' :
		if(roznica>0.5) roznica=roznica-0.5;
		break;
//kat
	case '7':
		kat_y+=0.5;
		break;
	case '&':
		kat_y-=0.5;
		break;
//wlaczenie swiatel
    case '4': glEnable(GL_LIGHT1);
        break;
    case '$': glDisable(GL_LIGHT1);
        break;
    case '5': glEnable(GL_LIGHT2);
        break;
    case '%': glDisable(GL_LIGHT2);
        break;
//promien swiatla
	case '8': R_L1++;
				  break;
	case '*': R_L1--;
				  break;
      if (menu == ID_MENU_SWIATLA)
	UstawParametryOswietlenia(sIndeks, klawisz);
      else
	UstawParametryMaterialu(mIndeks, klawisz);
      break;

      // Wcisniecie klawisza ESC powoduje wyjscie z programu
    case 27:
      exit(0);      
    }
}



//////////////////////////////////////////////////////////////////////////////////////////
// Glowna funkcja programu
int  main(int argc, char **argv)
{
  // Zainicjowanie biblioteki GLUT
  glutInit(&argc, argv);

  // Ustawienie trybu wyswietlania
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

  // Ustawienie polozenia dolenego lewego rogu okna
  glutInitWindowPosition(100, 100);

  // Ustawienie rozmiarow okna
  glutInitWindowSize(szerokoscOkna, wysokoscOkna);

  // Utworzenie okna
  glutCreateWindow("Oswietlony walec");

  // Odblokowanie bufora glebokosci
  glEnable(GL_DEPTH_TEST);

  // Ustawienie funkcji wykonywanej na danych w buforze glebokosci
  glDepthFunc(GL_LEQUAL);

  // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
  glClearDepth(1000.0);

  // Odblokowanie wykonywania operacji na skladowych "alfa"
  glEnable(GL_BLEND);

  // Wybor funkcji mieszajacej kolory
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Ustawienie koloru czyszczenia bufora ramki
  glClearColor (0.0, 0.3, 0.0, 0.0);
  
  // Zarejestrowanie funkcji (callback) wyswietlajacej
  glutDisplayFunc(WyswietlObraz);

  // Zarejestrowanie funkcji (callback) wywolywanej za kazdym razem kiedy
  // zmieniane sa rozmiary okna
  glutReshapeFunc(UstawParametryWidoku);

  // Zarejestrowanie funkcji wykonywanej gdy okno nie obsluguje
  // zadnych zadan
  glutIdleFunc(WyswietlObraz);

  // Zarejestrowanie funkcji obslugi klawiatury
  glutKeyboardFunc(ObslugaKlawiatury);

  /*// Zarejestrowanie funkcji obslugi klawiszy specjalnych
  glutSpecialFunc(ObslugaKlawiszySpecjalnych);
*/
  // Ustawienie domyslnych wartosci parametrow
  UstawDomyslneWartosciParametrow();

  // Obsluga glownej petli programu (wywolywanie zarejestrowanych callbackow
  // w odpowiedzi na odbierane zdarzenia lub obsluga stanu bezczynnosci)
  glutMainLoop();

  return 0;
}

