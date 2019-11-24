//////////////////////////////////////////////////////////////////////////////////////////
// Program demonstruje  skladanie transformacji przy modelowaniu zlozonych obiektow
// skladajacych sie z wielu elementow ruchomych (ramie robota).
 
#include <GL/glut.h>
 
// Stale wyznaczajace predkosci katowe planety i ksiezyca (w stopniach/sek.)
#define PREDKOSC_KATOWA_PLANETY  1.0
#define PREDKOSC_KATOWA_KSIEZYCA -5.0
 
// Wskazniki do wykorzystywanych kwadryk
GLUquadricObj *podstawaSciany;
GLUquadricObj *podstawaDyskG;
GLUquadricObj *przegubSciany;
GLUquadricObj *przegubDyskG;
GLUquadricObj *przegubDyskD;
GLUquadricObj *glowicaSciany;
GLUquadricObj *glowicaDyskG;
GLUquadricObj *glowicaDyskD;
 
GLfloat rotObsY     = 40.0;
GLfloat rotObsX     = 40.0;
GLfloat rotObsZ     = 0.0;
GLfloat rotPodstawy = 0.0;
GLfloat rotRamienia1= 0.0;
GLfloat rotRamienia2= 0.0;
GLfloat rotGlowicy  = 30.0;
GLfloat rozUchwytow = 0;
GLfloat xx = 0;
GLfloat yy = 0;
GLfloat zz = 0;
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja inicjujaca elementy skladowe ramienia robota zamodelowane jako kwadryki
//
void InicjujRamieRobota(void)
{
  // Zainicjowanie scian bocznych walca bedacego podstawa ramienia
  podstawaSciany = gluNewQuadric();
  gluQuadricDrawStyle(podstawaSciany, GLU_LINE);
 
  // Zainicjowanie gornej podstawy walca
  podstawaDyskG = gluNewQuadric();
  gluQuadricDrawStyle(podstawaDyskG, GLU_LINE);
 
  // Zainicjowanie scian bocznych cylindrycznego przegubu ramienia
  przegubSciany = gluNewQuadric();
  gluQuadricDrawStyle(przegubSciany, GLU_LINE);
 
  // Zainicjowanie gornej podstawy walca
  przegubDyskG = gluNewQuadric();
  gluQuadricDrawStyle(przegubDyskG, GLU_LINE);
 
  // Zainicjowanie dolnej podstawy walca
  przegubDyskD = gluNewQuadric();
  gluQuadricDrawStyle(przegubDyskD, GLU_LINE);
 
  // Zainicjowanie scian bocznych cylindra glowicy
  glowicaSciany = gluNewQuadric();
  gluQuadricDrawStyle(glowicaSciany, GLU_LINE);
 
  // Zainicjowanie gornej podstawy walca
  glowicaDyskG = gluNewQuadric();
  gluQuadricDrawStyle(glowicaDyskG, GLU_LINE);
 
  // Zainicjowanie dolnej podstawy walca
  glowicaDyskD = gluNewQuadric();
  gluQuadricDrawStyle(glowicaDyskD, GLU_LINE);
 
}
 
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja rysujaca obraz sceny widzianej z biezacej pozycji obserwatora
// Zalozenie: Funkcja glutWireSpehere moze ryswac tylko sfere o promieniu 1
void RysujRamieRobota(GLfloat obrotPodstawy, GLfloat obrotRamienia1,
            GLfloat obrotRamienia2, GLfloat obrotGlowicy,
            GLfloat rozstawUchwytow)
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
 
 
 
 
  // Przygotowanie stosu macierzy modelowania
  glPushMatrix();
 
  // Rysowanie podstawy ramienia (cylinder bez dolnej podstawy)
  glPushMatrix();
  // - sciany boczne
  glRotatef(-90.0, 1, 0, 0);
  gluCylinder(podstawaSciany, 2.5, 2.5, 1.0, 20, 4);
 
  // - gorna podstawa
  glTranslatef(0.0, 0.0, 1.0);
  gluDisk(podstawaDyskG, 0.0, 2.5, 20, 4);
  glPopMatrix();
 
glRotatef(obrotRamienia1, 0, 1, 0);
  // Rysowanie ramienia (cylinder i kulka na gorze)
  glPushMatrix();
  glTranslatef(0.0, 4.0, 0);
  glRotatef(90,1,0,0);
  gluCylinder(podstawaSciany, 0.625, 0.625, 3.0, 20, 4);
  glTranslatef(0.0, 0, -0.5);
  gluSphere(podstawaSciany,0.75,10,10);
  glPopMatrix();
 
 
  // Wyznaczenie osi obrotu ramienia w plaszczyznie pionowej
  glTranslatef(0.0, 4.5, 0.0);
 
  // Obrot ramienia w plaszczyznie pionowej
  glRotatef(obrotRamienia2, 1, 0, 0);
 
  //Rysowanie 'trzymatora' ramienia
  glPushMatrix();
  //glTranslatef(3.5/8.0, 0.0, 0.0);
  glScalef(4.0, 0.5, 1.0);
  glTranslatef(0, -0.5, 0.0);
  glutWireCube(1);
  glPopMatrix();
 
  //Modelowanie ramienia 1
  glPushMatrix();
  //glTranslatef(3.5/8.0, 0.0, 0.0);
  glTranslatef(2, -1,-1.625);
  gluCylinder(podstawaSciany, 0.5, 0.5, 6.25, 20, 4);
  glColor3f(1,0,0);
  gluDisk(podstawaDyskG, 0, 0.5, 4, 4);
  glColor3f(1,1,1);
  glPopMatrix();
 
 
  //modelowanie ramienia 2
  glPushMatrix();
  //glTranslatef(3.5/8.0, 0.0, 0.0);
  glTranslatef(-2, -1, -1.625);
  gluCylinder(podstawaSciany, 0.5, 0.5, 6.25, 20, 4);
  glColor3f(1,0,0);
  gluDisk(podstawaDyskG, 0, 0.5, 4, 4);
  glColor3f(1,1,1);
  glPopMatrix();
 
 
 
 
  // Posprzatanie na stosie macierzy modelowania
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
if(rotRamienia1>361.0) rotRamienia1=0;
rotRamienia1 += rozUchwytow;
   glTranslated(xx,yy,zz);
  // Wyznaczenie polozenia obserwatora (przeksztalcenie uladu wspolrzednych
  // sceny do ukladu wspolrzednych obserwatora).
  glTranslatef(0, 0, -rotGlowicy);
  glRotatef(rotObsX, 1, 0, 0);
  glRotatef(rotObsY,0,1,0);
  glRotatef(rotObsZ,0,0,1);
 
 
  // Generacja obrazu sceny w niewidocznym buforze ramki
  RysujRamieRobota(rotPodstawy, rotRamienia1, rotRamienia2, rotGlowicy, rozUchwytow);
 
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
  gluPerspective(30.0, (float)szerokosc/(float)wysokosc, 1.0, 1000.0);
 
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
      rotObsX = (rotObsX < 360.0) ? rotObsX + 1.0 : rotObsX;
      break;
 
    case GLUT_KEY_DOWN:
      rotObsX = (rotObsX > 0.0) ? rotObsX - 1.0 : rotObsX;
      break;
 
    case GLUT_KEY_LEFT:
      rotObsY = (rotObsY > -180.0) ? rotObsY - 1.0 : rotObsY;
      break;
 
    case GLUT_KEY_RIGHT:
      rotObsY = (rotObsY < 180.0) ? rotObsY + 1.0 : rotObsY;
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
      rotRamienia1 = (rotRamienia1 < 360.0) ? rotRamienia1 + 1 : rotRamienia1;
      break;
 
    case '@':
      rotRamienia1 = (rotRamienia1 > 0.0) ? rotRamienia1 - 1 : rotRamienia1;
      break;
 
   case '#':
      rotRamienia2 = (rotRamienia2 < 0.0) ? rotRamienia2 + 1.0 : rotRamienia2;
      break;
 
    case '3':
      rotRamienia2 = (rotRamienia2 > -90.0) ? rotRamienia2 - 1.0 : rotRamienia2;
      break;
 
    case '4':
      rotGlowicy = (rotGlowicy < 100) ? rotGlowicy + 1.0 : rotGlowicy;
      break;
 
    case '$':
      rotGlowicy = (rotGlowicy > 0.0) ? rotGlowicy - 1.0 : rotGlowicy;
      break;
 
   case '5':
      rotObsZ = (rotObsZ > -180.0) ? rotObsZ - 1.0 : rotObsZ;
      break;
 
    case '%':
      rotObsZ = (rotObsY < 180.0) ? rotObsZ + 1 : rotObsZ;
      break;
 
    case '+':
      rozUchwytow = (rozUchwytow < 1) ? rozUchwytow + 0.2 : rozUchwytow;
      break;
 
    case '-':
      rozUchwytow = (rozUchwytow > -1) ? rozUchwytow - 0.2 : rozUchwytow;
      break;
 
   case 'w':
      zz = (zz > -20) ? zz - 1 : zz;
      break;
 
   case 's':
      zz = (zz < 20) ? zz + 1 : zz;
      break;
 
   case 'a':
      xx = (xx > -20) ? xx - 1 : xx;
      break;
 
   case 'd':
      xx = (xx < 20) ? xx + 1 : xx;
      break;
 
   case 'q':
      yy = (yy > -20) ? yy - 1 : yy;
      break;
 
   case 'e':
      yy = (yy < 20) ? yy + 1 : yy;
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
  glutInitWindowSize(700, 700);
 
  // Utworzenie okna
  glutCreateWindow("-wyrzutnia");
 
  // Odblokowanie bufora glebokosci
  glEnable(GL_DEPTH_TEST);
 
  // Ustawienie funkcji wykonywanej na danych w buforze glebokosci
  glDepthFunc(GL_LEQUAL);
 
  // Ustawienie wartosci czyszczacej zawartosc bufora glebokosci
  glClearDepth(1000.0);
 
  // Ustawienie koloru czyszczenia bufora ramki
  glClearColor (0.3, 0.3, 0.3, 0.0);
 
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
  InicjujRamieRobota();
 
  // Obsluga glownej petli programu (wywolywanie zarejestrowanych callbackow
  // w odpowiedzi na odbierane zdarzenia lub obsluga stanu bezczynnosci)
  glutMainLoop();
 
  return 0;
}
