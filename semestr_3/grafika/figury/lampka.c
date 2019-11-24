//////////////////////////////////////////////////////////////////////////////////////////
// Program demonstruje  skladanie transformacji przy modelowaniu zlozonych obiektow
// skladajacych sie z wielu elementow ruchomych (ramie robota).
 
#include <GL/glut.h>
#include <math.h>
 
// Stale wyznaczajace predkosci katowe planety i ksiezyca (w stopniach/sek.)
#define PREDKOSC_KATOWA_PLANETY  1.0
#define PREDKOSC_KATOWA_KSIEZYCA -5.0
 
#define pi 3.14159265358979323846
#define DEG2RAD(x) ((float)(x)*pi/180.0)
#define RAD2DEG(x) ((float)(x)*180.0/pi)
 
// Wskazniki do wykorzystywanych kwadryk
GLUquadricObj *podstawa;
GLUquadricObj *podstawaDyskG;
GLUquadricObj *podstawaDyskD;
GLUquadricObj *czescKlosza;
GLUquadricObj *czescDyskG;
GLUquadricObj *czescDyskD;
GLUquadricObj *klosz;
GLUquadricObj *kloszDyskG;
 
GLfloat rotObsY     = 40.0;
GLfloat rotObsX     = 40.0;
GLfloat rotPodstawy = 0.0;
GLfloat rotRamienia1= 0.0;
GLfloat rotGlowicy  = 20.0;
GLfloat rozUchwytow = 0.5;
GLfloat odleglosc   = 20.0;
GLfloat wysokosc    = 2.0;
GLfloat zmienna;
 
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja inicjujaca elementy skladowe ramienia robota zamodelowane jako kwadryki
//
void Inicjujlampke(void)
{
  // Zainicjowanie scian bocznych walca bedacego podstawa lampki
  podstawa = gluNewQuadric();
  gluQuadricDrawStyle(podstawa, GLU_LINE);
 
  // Zainicjowanie gornej podstawy walca
  podstawaDyskG = gluNewQuadric();
  gluQuadricDrawStyle(podstawaDyskG, GLU_LINE);
 
  // Zainicjowanie dolnej podstawy walca
  podstawaDyskD = gluNewQuadric();
  gluQuadricDrawStyle(podstawaDyskD, GLU_LINE);
 
  // Zainicjowanie scian bocznych walca gornej czesci klosza
  czescKlosza = gluNewQuadric();
  gluQuadricDrawStyle(czescKlosza, GLU_LINE);
 
  // Zainicjowanie gornej podstawy walca
  czescDyskG = gluNewQuadric();
  gluQuadricDrawStyle(czescDyskG, GLU_LINE);
 
  // Zainicjowanie dolnej podstawy walca
  czescDyskD = gluNewQuadric();
  gluQuadricDrawStyle(czescDyskD, GLU_LINE);
 
  // Zainicjowanie scian bocznych stozka bedacego kloszem
  klosz = gluNewQuadric();
  gluQuadricDrawStyle(klosz, GLU_LINE);
 
  // Zainicjowanie gornej podstawy walca
  kloszDyskG = gluNewQuadric();
  gluQuadricDrawStyle(kloszDyskG, GLU_LINE);
}
 
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca obraz sceny widzianej z biezacej pozycji obserwatora
// Zalozenie: Funkcja glutWireSpehere moze ryswac tylko sfere o promieniu 1 
void RysujLampke(GLfloat obrotRamienia1, GLfloat obrotGlowicy)
{
  // Pocztaek tworzenia ukladu wspolrzednych
  glBegin(GL_LINES);
 
  // Os X
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-20.0, 0.0, 0.0);
  glVertex3f(20.0, 0.0, 0.0);
 
  // Os Y
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0, -20.0, 0.0);
  glVertex3f(0.0, 20.0, 0.0);
 
  // Os Z
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0, 0.0, -20.0);
  glVertex3f(0.0, 0.0, 20.0);
 
  // Koniec tworzenia ukladu wspolrzednych
  glEnd();
 
  glColor3f(1.0,1.0,1.0);
 
  //podstawa lampki
  glPushMatrix();
  glRotatef(-90.0,1,0,0);
  gluCylinder(podstawa,5.0,5.0,0.5,20,4);
  gluDisk(podstawaDyskD,0.0,5.0,20,4);
  glTranslatef(0.0,0.0,0.5);
  gluDisk(podstawaDyskG,0.0,5.0,20,4);
  glPopMatrix();
 
  //rotacja lampki
  glRotatef(obrotGlowicy, 0, 1, 0);
 
  //wspornik
  glPushMatrix();
  glTranslatef(0.0,0.5+2.5,0.0);
  glScalef(0.5,5.0,0.5);
  glutWireCube(1);
  glPopMatrix();
 
  //rotacja ramienia
  glTranslatef(-0.5,0.5+4.5,0.0);
  glRotatef(obrotRamienia1, 1, 0, 0);
 
  //ramie
  glPushMatrix();
  glTranslatef(0.0,0.0,-2.0);
  glScalef(0.25,0.25,5.0);
  glutWireCube(1);
  glPopMatrix();
 
  //czesc klosza
  glPushMatrix();
  glRotatef(-90.0,1,0,0);
  glTranslatef(0.0,4.5,-0.5);
  gluCylinder(czescKlosza,0.25,0.25,1.0,20,4);
  gluDisk(czescDyskD,0.0,0.25,20,4);
  glTranslatef(0.0,0.0,1.0);
  gluDisk(czescDyskG,0.0,0.25,20,4);
  glPopMatrix();
 
  //klosz
  glPushMatrix();
  glRotatef(-90.0,1,0,0);
  glTranslatef(0.0,4.5,-0.5-1.0);
  gluCylinder(klosz,1.0,0.5,1.0,20,4);
  glTranslatef(0.0,0.0,1.0);
  gluDisk(kloszDyskG,0.0,0.5,20,4);
  glPopMatrix();
 
}
 
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja generujaca pojedyncza klatke animacji
void WyswietlObraz(void)
{
  // Wyczyszczenie bufora ramki i bufora glebokosci
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
  // Powielenie macierzy na wierzcholku stosu
  glPushMatrix();
 
  // Wyznaczenie polozenia obserwatora (przeksztalcenie uladu wspolrzednych
  // sceny do ukladu wspolrzednych obserwatora).
  zmienna=RAD2DEG(asin(wysokosc/odleglosc));
  glTranslatef(0,0, -odleglosc);
  glRotatef(zmienna,1,0,0);
  glRotatef(rotObsY,0,1,0);
 
  //glTranslatef(0, 0, -Obserwator);
  //glRotatef(rotObsX, 1, 0, 0);
  //glRotatef(rotObsY,0,1,0);
 
 
  // Generacja obrazu sceny w niewidocznym buforze ramki
  RysujLampke(rotRamienia1,rotGlowicy);
 
  // Usuniecie macierzy lezacej na  wierzcholku stosu (powrot do stanu
  // sprzed wywolania funkcji)
  glPopMatrix();
 
  // Przelaczenie buforow ramki
  glutSwapBuffers();
 
 
}
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja ustawiajaca parametry rzutu perspektywicznego i rozmiary viewportu
void UstawParametryWidoku(int szerokosc, int wysokosc)
{
  // Ustawienie parametrow viewportu
  glViewport(0, 0, szerokosc, wysokosc);
 
  // Przejscie w tryb modyfikacji macierzy rzutowania
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, (float)szerokosc/(float)wysokosc, 1.0, 1000.0);
 
  // Przejscie w tryb modyfikacji macierzy przeksztalcen geometrycznych
  glMatrixMode(GL_MODELVIEW);
 
  // Zmiana macierzy znajdujacej sie na wierzcholku stosu na macierz jednostkowa
  glLoadIdentity();
}
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja klawiszy specjalnych
void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y)
{
  switch(klawisz)
    {
    case GLUT_KEY_UP:
      //rotObsX = (rotObsX < 90.0) ? rotObsX + 1.0 : rotObsX;
                wysokosc = (wysokosc < odleglosc) ? wysokosc + 0.5 :wysokosc;
      break;
 
    case GLUT_KEY_DOWN:
      //rotObsX = (rotObsX > 0.0) ? rotObsX - 1.0 : rotObsX;
                wysokosc = (wysokosc > 0.0) ? wysokosc - 0.5 :wysokosc;
      break;
 
    case GLUT_KEY_LEFT:
      rotObsY = (rotObsY > -90.0) ? rotObsY - 1.0 : rotObsY;
      break;
 
    case GLUT_KEY_RIGHT:
      rotObsY = (rotObsY < 90.0) ? rotObsY + 1.0 : rotObsY;
      break;
 
 
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{
 
  switch(klawisz)
    {
    case '2':
      rotRamienia1 = (rotRamienia1 < 90.0) ? rotRamienia1 + 1.0 : rotRamienia1;
      break;
 
    case '@':
      rotRamienia1 = (rotRamienia1 > 0.0) ? rotRamienia1 - 1.0 : rotRamienia1;
      break;
 
    case '4':
      rotGlowicy = (rotGlowicy < 360.0) ? rotGlowicy + 1.0 : rotGlowicy;
      break;
 
    case '$':
      rotGlowicy = (rotGlowicy > 0.0) ? rotGlowicy - 1.0 : rotGlowicy;
      break;
 
        case '+':
                odleglosc = (odleglosc<100.0) ? odleglosc+1.0 : odleglosc;
                break;
 
        case '-':
                odleglosc = (odleglosc/wysokosc>1.0) ? odleglosc-1.0 : odleglosc;
                break;
    }
 
  if(klawisz == 27)
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
  glutInitWindowSize(400, 400);
 
  // Utworzenie okna
  glutCreateWindow("Wieza z klockow");
 
  // Odblokowanie bufora glebokosci
  glEnable(GL_DEPTH_TEST);
 
  // Ustawienie funkcji wykonywanej na danych w buforze glebokosci
  glDepthFunc(GL_LEQUAL);
 
  // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
  glClearDepth(1000.0);
 
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
 
  // Zarejestrowanie funkcji obslugi klawiszy specjalnych
  glutSpecialFunc(ObslugaKlawiszySpecjalnych);
 
 
  // Zainicjowanie kwadryk tworzacych ramie robota
  Inicjujlampke();
 
  // Obsluga glownej petli programu (wywolywanie zarejestrowanych callbackow
  // w odpowiedzi na odbierane zdarzenia lub obsluga stanu bezczynnosci)
  glutMainLoop();
 
  return 0;
}