#include <GL/glut.h>
#include <math.h>

// Definicja stalych
#define DLUGOSC_BOKU            5.0
#define OBSERWATOR_FOV_Y        30.0
#define PI                      3.1415926535897932384626433832795 

// Zmienne globalne
double  bok           = DLUGOSC_BOKU; // Dlugosc boku szescianu
int     szerokoscOkna = 1180;
int     wysokoscOkna  = 700;
double ruszaj=0.0,obrot=0.0;
double OBSERWATOR_OBROT_Y=0;
double OBSERWATOR_OBROT_X=0;
double OBSERWATOR_OBROT_Z=0;
double OBSERWATOR_ODLEGLOSC=40.0,wysokosc=0.0,kat=0.0,r=0.0;
double obrot_smigla=0.0,xx=0.0,yy=0.0,zz=0.0;

// Prototypy funkcji
void RysujSzescian(double a);
void UstawParametryWidoku(int szer, int wys);
void WyswietlObraz(void);
void ObslugaKlawiatury(unsigned char klawisz, int x, int y);
double radian(float a);

// Funkcje

double rad(double a)
{
return (a*PI)/180;
}

void Rysuj(void)
{
     
gluLookAt(r,wysokosc,5,0,0,0,0,1,0);

glBegin(GL_LINES);
glColor3f(1,1,0);
glVertex3f(0,-100,0);
glVertex3f(0,100,0);
glColor3f(1,1,1);
glEnd();
glBegin(GL_LINES);
glColor3f(1,1,0);
glVertex3f(-100,0,0);
glVertex3f(100,0,0);
glColor3f(1,1,1);
glEnd();
glBegin(GL_LINES);
glColor3f(1,1,0);
glVertex3f(0,0,-100);
glVertex3f(0,0,100);
glColor3f(1,1,1);
glEnd();



glPushMatrix();

glRotatef(xx,1,0,0);
glRotatef(yy,0,1,0);
glRotatef(zz,0,0,1);
glTranslatef(0,0,10);


//kadlub
glPushMatrix();
GLUquadricObj *kadlub;
kadlub = gluNewQuadric();
glRotatef(90.0,0,1,0);
glTranslatef(0,0,-5);
gluCylinder(kadlub, 0.75, 0.75, 10.0, 40, 40);
gluDeleteQuadric(kadlub);
glPopMatrix();

glPushMatrix();
glTranslatef(-5,0,0);
glutSolidSphere(0.75,40,40);
glPopMatrix();

//skrzydlo duze
glPushMatrix();
glColor3f(1,0,1);
glTranslatef(0,0.75,0);
glScalef(12,1,32);
glutSolidCube(0.25);
glPopMatrix();

glPushMatrix();
glColor3f(0,1,0);
glTranslatef(-5.75,0,0);
glRotatef(obrot_smigla,1,0,0);
glScalef(1,1,16);
glutSolidCube(0.25);
glPopMatrix();

glPushMatrix();

glColor3f(1,0,1);
glTranslatef(4.25,0,1.5);
glScalef(6,1,12);
glutSolidCube(0.25);
glPopMatrix();

glPushMatrix();
glColor3f(1,0,1);
glTranslatef(4.25,0,-1.5);
glScalef(6,1,12);
glutSolidCube(0.25);
glPopMatrix();

glPushMatrix();
glColor3f(1,0,1);
glTranslatef(4.25,0.75,0);
glScalef(6,8,1);
glutSolidCube(0.25);
glPopMatrix();


glPopMatrix();

//xx++;
yy-=0.5;
//zz++;
obrot_smigla+=10.0;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja ustawiajaca parametry rzutu perspektywicznego i rozmiary viewportu. Powinna
// byæ wywolywana kazdorazowo po zmianie rozmiarow okna programu.
void UstawParametryWidoku(int szer, int wys)
{
  // Zapamietanie wielkosci widoku
  szerokoscOkna = szer;
  wysokoscOkna  = wys;

  // Ustawienie parametrow viewportu
  glViewport(0, 0, szerokoscOkna, wysokoscOkna);

  // Przejscie w tryb modyfikacji macierzy rzutowania
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(OBSERWATOR_FOV_Y, (float)szerokoscOkna/(float)wysokoscOkna, 1.0, 1000.0);
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja wyswietlajaca pojedyncza klatke animacji
void WyswietlObraz(void)
{
     
  // Wyczyszczenie bufora koloru i bufora glebokosci
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // Przejscie w tryb modyfikacji macierzy przeksztalcen geometrycznych
  glMatrixMode(GL_MODELVIEW);

  // Zastapienie aktywnej macierzy macierza jednostkowa
  glLoadIdentity();

  // Ustalenie polozenia obserwatora
  glTranslatef(0, 0, -OBSERWATOR_ODLEGLOSC);
  glRotatef(OBSERWATOR_OBROT_X, 1, 0, 0);
  glRotatef(OBSERWATOR_OBROT_Y, 0, 1, 0);
  glRotatef(OBSERWATOR_OBROT_Z, 0,0,1);
  if(obrot==1){ OBSERWATOR_OBROT_Y+=0.1;
  OBSERWATOR_OBROT_X+=0.1;
  OBSERWATOR_OBROT_Z+=0.1; }
  if(OBSERWATOR_OBROT_Y>360.0) OBSERWATOR_OBROT_Y=0.0;
  if(OBSERWATOR_OBROT_X>360.0) OBSERWATOR_OBROT_X=0.0;
  if(OBSERWATOR_OBROT_Z>360.0) OBSERWATOR_OBROT_Z=0.0;
  

  // Narysowanie bryly
  Rysuj();

  // Przelaczenie buforow ramki
  glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{
  if (klawisz == 'x')
      OBSERWATOR_OBROT_X+=1.0;
  else if (klawisz == 'X')
	  OBSERWATOR_OBROT_X-=1.0;
  else if (klawisz == 'y')
	  OBSERWATOR_OBROT_Y+=1.0;
  else if (klawisz == 'Y')
	  OBSERWATOR_OBROT_Y-=1.0;
  else if (klawisz == 'z')
	  OBSERWATOR_OBROT_Z+=1.0;
  else if (klawisz == 's')
	  obrot_smigla+=10.0;
  else if (klawisz == 'r')
	  r++;
  else if (klawisz == 'R')
	  r--;	  
  else if (klawisz == 'h')
	  wysokosc++;	  
  else if (klawisz == 'H')
	  wysokosc--;	  
  
	  

  else if (klawisz == 27)
      exit(0);      
}


//////////////////////////////////////////////////////////////////////////////////////////
// Glowna funkcja programu
int  main(int argc, char **argv)
{
  // Zainicjowanie biblioteki GLUT
  glutInit(&argc, argv);

  // Ustawienie trybu wyswietlania
  glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

  // Ustawienie polozenia dolenego lewego rogu okna
  glutInitWindowPosition(1, 1);

  // Ustawienie rozmiarow okna
  glutInitWindowSize(szerokoscOkna, wysokoscOkna);

  // Utworzenie okna
  glutCreateWindow("Przykladowy program");

  // Odblokowanie bufora glebokosci
  glEnable(GL_DEPTH_TEST);

  // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
  glClearDepth(1000.0);

  // Ustawienie koloru czyszczenia bufora ramki
  glClearColor (0.0f, 0.0f, 0.3f, 0.0f);

  // Wlaczenie wyswietlania wielokatow w postaci obrysow (przydatne w celach diagnostycznych).
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  // Zarejestrowanie funkcji (callback) odpowiedzialnej za 
  glutDisplayFunc(WyswietlObraz);

  // Zarejestrowanie funkcji (callback) wywolywanej za kazdym razem kiedy
  // zmieniane sa rozmiary okna
  glutReshapeFunc(UstawParametryWidoku);

  // Zarejestrowanie funkcji wykonywanej gdy okno nie obsluguje
  // zadnych zadan
  glutIdleFunc(WyswietlObraz);

  // Zarejestrowanie funkcji obslugi klawiatury
  glutKeyboardFunc(ObslugaKlawiatury);

  // Obsluga glownej petli programu (wywolywanie zarejestrowanych callbackow
  // w odpowiedzi na odbierane zdarzenia lub obsluga stanu bezczynnosci)
  glutMainLoop();

  return 0;
}
