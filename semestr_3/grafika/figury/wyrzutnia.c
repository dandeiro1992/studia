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
 
GLfloat odlObs      = -70.0;
GLfloat rotObsY     =  40.0;
GLfloat rotObsX     =  40.0;
GLfloat rotObsZ     =  0.0;
GLfloat rotPodstawy = 0.0;
GLfloat rotRamienia1= 0.0;
GLfloat rotRamienia2= -40.0;
GLfloat rotGlowicy  = 0.0;
GLfloat rozUchwytow = 0.5;
 
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
 
  glColor3f(0.0,0.0,0.0);
 
 
 
 
  // Przygotowanie stosu macierzy modelowania
  glPushMatrix();
 
  // Rysowanie podstawy ramienia (cylinder bez dolnej podstawy)
glTranslatef(0.0, 0.0, 0.0);
  glRotatef(0, 1, 0, 0);
  glRotatef(obrotGlowicy, 0, 1, 0);
 
  glPushMatrix();
  glTranslatef(0.0, 5.0, 0);
  glutWireSphere(1.5,20,20);
  glPopMatrix();
 
        // rura trzymajaca dzialo
        glPushMatrix();
  // - sciany boczne
        glTranslatef(0.0, 1.0, 0.0);
  glRotatef(-90.0, 1, 0, 0);
  gluCylinder(podstawaSciany, 1.0, 1.0, 3.0, 20, 4);
  glPopMatrix();
 
 
  // Wyznaczenie osi obrotu ramienia w plaszczyznie pionowej
  glTranslatef(0.0, 4.0, 0.0);
 
  // Obrot ramienia w plaszczyznie pionowej
  glRotatef(obrotRamienia1, 0, 0, 1);
 
  // Modelowanie ramienia nr 1
 // glPushMatrix();
 // glScalef(8.0, 1.0, 1.0);
 // glTranslatef(3.5/8.0, 0.0, 0.0);
 // glutWireCube(1);
 // glPopMatrix();
 
  // Wyznaczenie osi obrotu ramienia 2 w plaszczyznie pionowej
 // glTranslatef(7.5, 0.0, 0.0);
 
  // Obrot ramienia 2 wzgledem ramienia 1
 // glRotatef(obrotRamienia2, 0, 0, 1);
 
  // Modelowanie przegubu (walca z obiema podstawami)
 
 // - czubek
  glPushMatrix();
  glRotatef(-90.0, 1, 0, 0);
  glTranslatef(0.0, 0.0, 0.3);
  glScalef(1.25, 4.0, 0.5);
  glutWireCube(1.25);
  glTranslatef(0.0, 0.0, 1.0);
  glPopMatrix();
 
 
  // Modelowanie ramienia nr 2
  glPushMatrix();
  glScalef(4.0, 1.0, 1.0);
  glTranslatef(2.0/4.0, 1.5, 2.0);
    glPopMatrix();
       
  glPushMatrix();
  glRotatef(90.0, 0, 1, 0);
  glTranslatef(2.5, -1.0, 0);
  gluCylinder(podstawaSciany, 1.0, 1.0, 6.0, 20, 4);
  glTranslatef(0.0, 0.0, 0);
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);
  glPopMatrix();
 
  glPushMatrix();
  glRotatef(90.0, 0, 1, 0);
  glTranslatef(-2.5, -1.0, 0);
  gluCylinder(podstawaSciany, 1.0, 1.0, 6.0, 20, 4);
  glTranslatef(0.0, 0.0, 0);
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);
  glPopMatrix();
 
 
  // Wyznaczenie osi obrotu glowicy
 
glPopMatrix();
 
 glPushMatrix();
  // - sciany boczne
  glRotatef(-90.0, 1, 0, 0);
  gluCylinder(podstawaSciany, 2.5, 2.5, 1.0, 20, 4);
 
  // - gorna podstawa
  glTranslatef(0.0, 0.0, 1.0);
  gluDisk(podstawaDyskG, 0.0, 2.5, 20, 4);
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
 
 
  // Wyznaczenie polozenia obserwatora (przeksztalcenie uladu wspolrzednych sceny do ukladu wspolrzednych obserwatora).
  glTranslatef(0, 0, odlObs);
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
     rotObsX = (rotObsX > 0) ? rotObsX - 1.0 : rotObsX;
      break;
 
      case GLUT_KEY_DOWN:
      rotObsX = (rotObsX < 360.0) ? rotObsX + 1.0 : rotObsX;
      break;
 
     
      case GLUT_KEY_LEFT:
      rotObsY = (rotObsY > 0) ? rotObsY - 1.0 : rotObsY;
      break;
 
      case GLUT_KEY_RIGHT:
      rotObsY = (rotObsY < 360.0) ? rotObsY + 1.0 : rotObsY;
      break;
 
    }
 
}
 
//////////////////////////////////////////////////////////////////////////////////////////
// Funkcja obslugi klawiatury
void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{
 
  switch(klawisz)
    {
    case 'q':
      rotRamienia1 = (rotRamienia1 < 90.0) ? rotRamienia1 + 1.5 : rotRamienia1;
      break;
 
    case 'a':
      rotRamienia1 = (rotRamienia1 > 0.0) ? rotRamienia1 - 1.5 : rotRamienia1;
      break;
 
    case 'w':
      rotGlowicy = (rotGlowicy < 360.0) ? rotGlowicy + 1.0 : rotGlowicy;
      break;
 
    case 's':
      rotGlowicy = (rotGlowicy > 0.0) ? rotGlowicy - 1.0 : rotGlowicy;
      break;
 
         case 'e':
     
          odlObs = (odlObs < 0.0) ? odlObs + 1.0 : odlObs;
      break;
 
      case 'd':
     
          odlObs = (odlObs > -200.0) ? odlObs - 1.0 : odlObs;
      break;
 
           case 'r':
      rotObsZ = (rotObsZ > 0) ? rotObsZ - 1.0 : rotObsZ;
      break;
 
      case 'f':
      rotObsZ = (rotObsZ < 360.0) ? rotObsZ + 1.0 : rotObsZ;
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
  InicjujRamieRobota();
 
  // Obsluga glownej petli programu (wywolywanie zarejestrowanych callbackow
  // w odpowiedzi na odbierane zdarzenia lub obsluga stanu bezczynnosci)
  glutMainLoop();
 
  return 0;
}