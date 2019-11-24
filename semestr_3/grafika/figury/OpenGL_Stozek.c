//////////////////////////////////////////////////////////////////////////////////////////
// stozek by Majkel
//
// sterowanie:
// W,S,A,D - zmiana podzialow poziomych i pionowych
// +,-     - zmiana rozmiaru stozka
//////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>


// Definicja stalych
#define WYSOKOSC				4.0
#define PROMIEN                 3.0
#define PODZIALY_POZIOME        16.0
#define PODZIALY_PIONOWE        16.0
#define OBSERWATOR_ODLEGLOSC    20.0
#define OBSERWATOR_OBROT_X      20.0
#define OBSERWATOR_OBROT_Y      20.0
#define OBSERWATOR_FOV_Y        30.0


// Zmienne globalne
double  promien       = PROMIEN;
double  wysokosc	  = WYSOKOSC;
double  p_pion        = PODZIALY_PIONOWE;
double  p_poz         = PODZIALY_POZIOME;
int     szerokoscOkna = 1024;
int     wysokoscOkna  = 768;
float a,x,y,z;


// Prototypy funkcji
void RysujStozek(double R, double H);
void UstawParametryWidoku(int szer, int wys);
void WyswietlObraz(void);
void ObslugaKlawiatury(unsigned char klawisz, int x, int y);

//funkcja rysujaca stozek
void RysujStozek(double R, double H)
{
     float x, y, z, r, fi, skok_poz, skok_pion;
     const long double PI = 3.1415926535897932384626433832795028841971693993751058209;
	 skok_poz = PI/p_poz;
	 skok_pion= H/p_pion;

//pierscienie
     glBegin(GL_LINE_STRIP);
     for(y = 0; y < H; y += skok_pion)
     {
          for(fi = 0; fi <= 2.0001*PI; fi += skok_poz)
          {
               r = (H-y)*R/H;
               x = r * cos(fi);
               z = r * sin(fi);
               glVertex3f(x, y, z);
          }
     }
     glEnd();

//podstawa dolna
	 glBegin(GL_TRIANGLE_FAN);

		  glVertex3f(0.0, 0.0, 0.0);
          for(fi = 0; fi <= 2.0001*PI; fi += skok_poz)
          {
               x = R * cos(fi);
               z = R * sin(fi);
               glVertex3f(x, 0, z);
          }
     
     glEnd();

//sciany boczne
     glBegin(GL_TRIANGLE_FAN);

		  glVertex3f(0, H, 0);
          for(fi = 0; fi < 2.0001*PI; fi += skok_poz)
          {
               x = R * cos(fi);
               z = R * sin(fi);
               glVertex3f(x, 0, z);
          }
     
     glEnd();
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

  // Narysowanie szescianu
  RysujStozek(promien, wysokosc);

  // Przelaczenie buforow ramki
  glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{
  if(klawisz == '+'){
      promien *= 0.9;
      wysokosc *=1.05;}
  else if (klawisz == '-'){
      promien /= 0.9;
      wysokosc /=1.05;}
  else if (klawisz == 'w' && p_poz<=36)
      p_poz++;
  else if (klawisz == 's' && p_poz>=2)
      p_poz--;
  else if (klawisz == 'a' && p_pion<=36)
      p_pion++;
  else if (klawisz == 'd' && p_pion>=2)
      p_pion--;
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
  glutInitWindowPosition(100, 100);

  // Ustawienie rozmiarow okna
  glutInitWindowSize(szerokoscOkna, wysokoscOkna);

  // Utworzenie okna
  glutCreateWindow("Stozek");

  // Odblokowanie bufora glebokosci
  glEnable(GL_DEPTH_TEST);

  // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
  glClearDepth(1000.0);

  // Ustawienie koloru czyszczenia bufora ramki
  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

  // Wlaczenie wyswietlania wielokatow w postaci obrysow (przydatne w celach diagnostycznych).
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
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
