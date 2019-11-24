//////////////////////////////////////////////////////////////////////////////////////////
//
// Program wyswietlajacy szescian w rzucie perspektywicznym. Dlugosc boku szescianu
// moze byc interaktywnie zmieniana za pomoca klwiszy '+' i '-'.
//
//////////////////////////////////////////////////////////////////////////////////////////
#include <GL/glut.h>
#include <math.h>


// Definicja stalych
#define DLUGOSC_BOKU            4.0
#define OBSERWATOR_ODLEGLOSC    20.0
#define OBSERWATOR_FOV_Y        30.0 
#define PI                      3.14

// Zmienne globalne
double  bok           = DLUGOSC_BOKU; // dlugosc boku szescianu
int     szerokoscOkna = 800;
int     wysokoscOkna  = 600;

float podzial = 10.0;
float xx = 0.0;
float yy = 0.0;
float zz = 0.0;
float x;
float y;
float xxx_obrot = 30.0; 
float yyy_obrot = 30.0; 
float zzz_obrot = 0.0;
float r = 3;

// Prototypy funkcji
void RysujSzescian(double a);
void UstawParametryWidoku(int szer, int wys);
void WyswietlObraz(void);
void ObslugaKlawiatury(unsigned char klawisz, int x, int y);

float radian(double a)
{
    return (a*PI)/180;
}

//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca sferê w trybie GL_TRIANGLES.
// Srodek sfery znajduje siê w punkcie (0,0,0).

void RysujSzescian(double a)
{
	//Narysowanie linii pomocniczych
  glBegin(GL_LINES);
  // Os X
  glColor3f(0.3, 0.8, 0.3);
  glVertex3f(-20.0, 0.0, 0.0);
  glVertex3f(20.0, 0.0, 0.0);

  // Os Y
  glColor3f(0.8,0.3,0.3);
  glVertex3f(0.0, -20.0, 0.0);
  glVertex3f(0.0, 20.0, 0.0);

  // Os Z
  glColor3f(0.1,0.1,0.8);
  glVertex3f(0.0, 0.0, -20.0);
  glVertex3f(0.0, 0.0, 20.0);
  glEnd();

  //Narysowanie sfery
  
  glBegin(GL_TRIANGLES);
    glColor3f(0.0,0.8,0.9);
    for (int i=0;i<=360;i+=podzial){
         for (int j=0;j<=360;j+=podzial){
             glVertex3f(r*cos(radian(i))*cos(radian(j)),r*sin(radian(i)),r*cos(radian(i))*sin(radian(j)));
             glVertex3f(r*cos(radian(i+podzial))*cos(radian(j)),r*sin(radian(i+podzial)),r*cos(radian(i+podzial))*sin(radian(j)));
             glVertex3f(r*cos(radian(i))*cos(radian(j+podzial)),r*sin(radian(i)),r*cos(radian(i))*sin(radian(j+podzial)));
             }
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
  glTranslatef(xx,yy,zz); // odleg³oœæ obserwatora od osi X,Y,Z
  glTranslatef(0, 0, -OBSERWATOR_ODLEGLOSC);
  
  //Funkcje odpowiedzialne za obrót wzglêdem wybranej osi
  glRotatef(xxx_obrot, 1, 0, 0);
  glRotatef(yyy_obrot, 0, 1, 0);
  glRotatef(zzz_obrot, 0, 0, 1);

  // Narysowanie szescianu
  RysujSzescian(bok);

  // Przelaczenie buforow ramki
  glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{
  if (klawisz == 27)
      exit(0);     
  else if (klawisz =='+') //zbli¿enie obserwatora wzglêdem osi z
     zz++;
  else if (klawisz =='-') //oddalenie obserwatora wzglêdem osi z
     zz--;
  else if (klawisz =='x') //obrot obserwatora wzglêdem osi x
     xxx_obrot++;
  else if (klawisz =='z') //obrot obserwatora wzglêdem osi x w drug¹ stronê
     xxx_obrot--;
  else if (klawisz =='s') //obrot obserwatora wzglêdem osi y
     yyy_obrot++;
  else if (klawisz =='a') //obrot obserwatora wzglêdem osi y w drug¹ stronê
     yyy_obrot--;
  else if (klawisz =='q') //obrot obserwatora wzglêdem osi z
     zzz_obrot++;
  else if (klawisz =='w') //obrot obserwatora wzglêdem osi z w drug¹ stronê
     zzz_obrot--;
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
  glutCreateWindow("Sfera");

  // Odblokowanie bufora glebokosci
  glEnable(GL_DEPTH_TEST);

  // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
  glClearDepth(1000.0);

  // Ustawienie koloru czyszczenia bufora ramki
  glClearColor (0.0f, 0.5f, 0.5f, 0.9f);

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