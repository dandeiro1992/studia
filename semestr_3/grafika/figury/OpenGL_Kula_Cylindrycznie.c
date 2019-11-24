//////////////////////////////////////////////////////////////////////////////////////////
// kula by Majkel (wspolrzedne cylindryczne)
//
// sterowanie:
// W,S,A,D - zmiana podzialow poziomych i pionowych
// +,-     - zmiana rozmiaru stozka
//////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>


// Definicja stalych
#define PROMIEN                 3.0
#define PODZIALY_POZIOME        12.0
#define PODZIALY_PIONOWE        16.0
#define OBSERWATOR_ODLEGLOSC    20.0
#define OBSERWATOR_OBROT_X      20.0
#define OBSERWATOR_OBROT_Y      20.0
#define OBSERWATOR_FOV_Y        30.0


// Zmienne globalne
double  promien       = PROMIEN;
double  p_pion        = PODZIALY_PIONOWE;
double  p_poz         = PODZIALY_POZIOME;
int     szerokoscOkna = 1024;
int     wysokoscOkna  = 768;
float a,x,y,z;


// Prototypy funkcji
void RysujKule(double R);
void UstawParametryWidoku(int szer, int wys);
void WyswietlObraz(void);
void ObslugaKlawiatury(unsigned char klawisz, int x, int y);

//funkcja rysujaca kule
void RysujKule(double R)
{
     float x, y, z, r, fi, skok_poz, skok_pion;
     const long double PI = 3.1415926535897932384626433832795028841971693993751058209;
	 skok_poz = PI/p_poz;
	 skok_pion= R/p_pion;
//osie ukladu wspolrzednych
/*
	 glColor3f(1,0,0);
     glBegin(GL_LINES);
                       glVertex3f(-10,0,0);
                       glVertex3f(10,0,0);
                       glVertex3f(0,-10,0);
                       glVertex3f(0,10,0);
                       glVertex3f(0,0,-100);
                       glVertex3f(0,0,10);
     glEnd();
*/

//poludniki
     glColor3f(1,1,1);
     for(fi = 0; fi <= 2.0001*PI; fi += skok_poz){
            //gorna polkula
            glBegin(GL_LINE_STRIP);
            for(y = R; y >=0; y -= skok_pion){
                  glVertex3f(sqrt(R*R-y*y)*cos(fi), y, sqrt(R*R-y*y)*sin(fi));
            }
            glEnd();
            //dolna polkula
            glBegin(GL_LINE_STRIP);
            for(y = -R; y <=0; y += skok_pion){
                  glVertex3f(sqrt(R*R-y*y)*cos(fi), y, sqrt(R*R-y*y)*sin(fi));
            }            
            glEnd();
     }

//rownolezniki
     for(y = 0; y <= R; y += skok_pion){
            glBegin(GL_LINE_STRIP);
            for(fi = 0; fi <= 2.0001*PI; fi += skok_poz){
                  glVertex3f(sqrt(R*R-y*y)*cos(fi), y, sqrt(R*R-y*y)*sin(fi));
            }
            glEnd();
     }
     for(y = 0; y >= -R; y -= skok_pion){
            glBegin(GL_LINE_STRIP);
            for(fi = 0; fi <= 2.0001*PI; fi += skok_poz){
                  glVertex3f(sqrt(R*R-y*y)*cos(fi), y, sqrt(R*R-y*y)*sin(fi));
            }
            glEnd();
     }     
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
  RysujKule(promien);

  // Przelaczenie buforow ramki
  glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{
  if(klawisz == '+'){
      promien *= 0.9;}
  else if (klawisz == '-'){
      promien /= 0.9;}
  else if (klawisz == 'w' && p_poz<=36)
      p_poz++;
  else if (klawisz == 's' && p_poz>=2)
      p_poz--;
  else if (klawisz == 'a' && p_pion<=120)
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
  glutCreateWindow("Kula");

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
