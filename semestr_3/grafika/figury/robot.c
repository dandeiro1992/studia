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
GLfloat rotPodstawy = 0.0;
GLfloat rotRamienia1= 0.0;
GLfloat rotRamienia2= 0.0;
GLfloat rotGlowicy  = 0.0; 
GLfloat rozUchwytow = 0.5;
GLfloat odl			= -40.0;
GLfloat wys			= 0;

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
  glVertex3f(-100.0, 0.0, 0.0);
  glVertex3f(100.0, 0.0, 0.0);

  // Os Y
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0, -100.0, 0.0);
  glVertex3f(0.0, 100.0, 0.0);

  // Os Z
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0, 0.0, -100.0);
  glVertex3f(0.0, 0.0, 100.0);

  // Koniec tworzenia ukladu wspolrzednych
  glEnd();

  glColor3f(1.0,1.0,1.0);

  // Przygotowanie stosu macierzy modelowania
  //glPushMatrix();
////////////////////////////////////////////////////////////////////////////
///////////////////////////ESENCJA//////////////////////////////////////////


  //translacja punktu przesuwania
  glTranslatef(0.0, 0.0, -5.0);
  //odchylanie pionowe
  glRotatef(rotRamienia2, 1, 0, 0);
  //odchylanie poziome
  glRotatef(rotGlowicy, 0, 1, 0);
  //obracanie wkolo wlasnej osi
  glRotatef(rotRamienia1, 0, 0, 1);
  //translacja wstecz
  glTranslatef(0.0, 0.0, +5.0);

  

  //trzon samolotu
  glPushMatrix(); // ==========PUSH==========
  //sciany trzonu

  //cylinder
  glTranslatef(0.0, 0.0, -5.0);
  gluCylinder(podstawaSciany, 0.76, 0.76, 10.0, 45, 45);

  //zamkniecie cylindra tylnie dyskiem
  gluDisk(podstawaSciany, 0, 0.76, 35, 35);

  //zamkniecie cylindra przednie sfera
  glTranslatef(0.0, 0.0, 10.0);
  gluSphere(podstawaSciany, 0.75, 25, 25);

  glPopMatrix(); // ==========POP==========



  //wing
  glPushMatrix();// ==========PUSH==========
  glTranslatef(0.0, 0.76-0.125, 0.0);
  glScalef(8.0, 0.25, 3);
  glutWireCube(1);
  glPopMatrix();// ==========POP==========



  //ogon pionowy
  glPushMatrix();// ==========PUSH==========
  glTranslatef(0.0, 0.76+1, -5.0+0.75);
  glScalef(0.25, 2.0, 1.5);
  glutWireCube(1);
  glPopMatrix(); // ==========POP==========



  //ogonki poziome
  glPushMatrix();// ==========PUSH==========

  glTranslatef(0.76+1, 0.0, -5.0+0.75);
  glScalef(2.0, 0.25, 1.5);

  glutWireCube(1);

  glTranslatef(-(0.76+1), 0.0, 0.0);
  glutWireCube(1);

  glPopMatrix();// ==========POP==========

  //belka smigla
  glRotatef(rozUchwytow, 0, 0, 1);
  glPushMatrix();// ==========PUSH==========

  glTranslatef(0.0, 0.0, 5.0+0.75+0.125); // wysrodkowanie........
  glScalef(0.25, 4.0, 0.25);
  glutWireCube(1);

  glPopMatrix();// ==========POP==========


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

  //glPopMatrix();
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
  glTranslatef(0, wys, odl);
  glRotatef(40, 1, 0, 0);
  glRotatef(rotObsY,0,1,0);


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
      rotObsX = (rotObsX < 90.0) ? rotObsX + 1.0 : rotObsX;
      break;

    case GLUT_KEY_DOWN:
      rotObsX = (rotObsX > 0.0) ? rotObsX - 1.0 : rotObsX;
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
	case 'q':
      wys = (wys < 90.0) ? wys + 1.0 : wys;
      break;

    case 'Q':
      wys  = (wys > -40.0) ? wys - 1.0 : wys;
      break;
	case '1':
      odl = (odl < 5.0) ? odl + 1.0 : odl;
      break;

    case '!':
      odl  = (odl > -90.0) ? odl - 1.0 : odl;
      break;
	//BECZKA
    case '2':
      rotRamienia1 = (rotRamienia1 < 360.0) ? rotRamienia1 + 1.0 : rotRamienia1;
      break;

    case '@':
      rotRamienia1 = (rotRamienia1 > -360.0) ? rotRamienia1 - 1.0 : rotRamienia1;
      break;
	//PION
    case '3':
      rotRamienia2 = (rotRamienia2 < 360.0) ? rotRamienia2 + 1.0 : rotRamienia2;
      break;

    case '#':
      rotRamienia2 = (rotRamienia2 > -360.0) ? rotRamienia2 - 1.0 : rotRamienia2;
      break;
	// POZIOM
    case '4':
      rotGlowicy = (rotGlowicy < 360.0) ? rotGlowicy + 1.0 : rotGlowicy;
      break;

    case '$':
      rotGlowicy = (rotGlowicy > -360.0) ? rotGlowicy - 1.0 : rotGlowicy;
      break;

    case '5':
      rozUchwytow = (rozUchwytow < 3600.0) ? rozUchwytow + 4 : rozUchwytow;
      break;

    case '%':
      rozUchwytow = (rozUchwytow > -3600.0) ? rozUchwytow - 4 : rozUchwytow;
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
  glutInitWindowSize(1200, 800);

  // Utworzenie okna
  glutCreateWindow("Samolot");

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


