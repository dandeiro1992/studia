//////////////////////////////////////////////////////////////////////////////////////////
// Program demonstruje  skladanie transformacji przy modelowaniu zlozonych obiektow
// skladajacych sie z wielu elementow ruchomych (ramie robota). 

#include <glut.h>

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
GLfloat rotObsZ		= 0.0;
GLfloat rotPodstawy = 0.0;
GLfloat rotRamienia1= 40.0;
GLfloat rotRamienia2= -40.0;
GLfloat rotGlowicy  = 20.0; 
GLfloat rozUchwytow = 0.5;
GLfloat odlmin		= -80.0;
GLfloat odlmax		= -10.0;
GLfloat zmodl		= -40.0;
GLfloat wp			= 0.0;
GLfloat spin		= 0.0;
GLfloat wk			= 0.0;
GLfloat obrotWiezyczki = 0.0; 
GLfloat katLufy = 0.0;

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

  glColor3f(1.0,1.0,0.0);

  glTranslatef(0,0,0);


  // Przygotowanie stosu macierzy modelowania
  glPushMatrix();
  glTranslatef(0.0,0.0,-50.0);
  // Rysowanie podstawy ramienia (cylinder bez dolnej podstawy)
  glPushMatrix();
  // - sciany boczne
  glRotatef(-90.0, 1, 0, 0);
  gluCylinder(podstawaSciany, 3.0, 3.0, 1.0, 20, 4);
  
  // - gorna podstawa
  glTranslatef(0.0, 0.0, 1.0);
  gluDisk(podstawaDyskG, 0.0, 3.0, 20, 4);
  glPopMatrix();


  // Rysowanie dwoch wspornikow ramienia (prostopadlosciany)
  glPushMatrix();
  glScalef(3.0, 4.0, 1.0);
  glTranslatef(0.0, 3.0/4.0, 1.0);
  glutWireCube(1);
  glTranslatef(0.0, 0.0, -2.0);
  glutWireCube(1);  
  glPopMatrix();

  // Wyznaczenie osi obrotu ramienia w plaszczyznie pionowej
  glTranslatef(0.0, 4.0, 0.0);

  // Obrot ramienia w plaszczyznie pionowej
  glRotatef(obrotRamienia1, 0, 0, 1);

  // Modelowanie ramienia nr 1
  glPushMatrix();
  glScalef(8.0, 1.0, 1.0);
  glTranslatef(3.5/8.0, 0.0, 0.0);
  glutWireCube(1);
  glPopMatrix();
  
  // Wyznaczenie osi obrotu ramienia 2 w plaszczyznie pionowej
  glTranslatef(7.5, 0.0, 0.0);
  
  // Obrot ramienia 2 wzgledem ramienia 1
  glRotatef(obrotRamienia2, 0, 0, 1);

  // Modelowanie przegubu (walca z obiema podstawami)
  glPushMatrix();
  // - sciany boczne
  glTranslatef(0.0, 0.0, -0.5);
  gluCylinder(podstawaSciany, 1.0, 1.0, 1.0, 20, 4);
  
  // - gorna podstawa
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);

  // - dolna podstawa
  glTranslatef(0.0, 0.0, 1.0);
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);
  glPopMatrix();

  // Modelowanie ramienia nr 2
  glPushMatrix();
  glScalef(4.0, 1.0, 1.0);
  glTranslatef(2.0/4.0, 0.0, 0.0);
  glutWireCube(1);
  glPopMatrix();

  // Wyznaczenie osi obrotu glowicy
  glTranslatef(4.0, 0.0, 0.0);
  glRotatef(90, 0, 1, 0);
  glRotatef(obrotGlowicy, 0, 0, 1);

  // Modelowanie glowicy (walca z oboma podstawami)
  glPushMatrix();
  // - sciany boczne
  gluCylinder(podstawaSciany, 1.0, 1.0, 1.0, 20, 4);
  
  // - gorna podstawa
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);

  // - dolna podstawa
  glTranslatef(0.0, 0.0, 1.0);
  gluDisk(podstawaDyskG, 0.0, 1.0, 20, 4);
  glPopMatrix();

  // Modelowanie uchwytu (dwoch prostopadloscianow, ktore sie rozsuwaja i zsuwaja)
  glTranslatef(0.0, 0.0, 1.5);
  glScalef(0.5, 0.5, 2.0);
  glTranslatef(-rozstawUchwytow, 0.0, 0.25);
  glutWireCube(1);
  glTranslatef(rozstawUchwytow*2.0, 0.0, 0.0);
  glutWireCube(1);



  // Posprzatanie na stosie macierzy modelowania
  glPopMatrix();
}

void rysuj_zad1(){
	glPushMatrix();
	glTranslatef(-30.0,0.0,0.0);
	glPushMatrix();
	glRotatef(45.0,0,1.0,0);
	glTranslatef(0,5,0);
	glScalef(4.23,10,4.23);
	glColor3f(0,0,1.0);
	glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,11.5,0);
	glScalef(8.0,3.0,8.0);
	glColor3f(1.0,1.0,0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0,14.0,3.0);
	glScalef(2.0,2.0,2.0);
	glColor3f(0.3,0.3,0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0,14.0,-3.0);
	glScalef(2.0,2.0,2.0);
	glColor3f(0.3,0.3,0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0,14.0,-3.0);
	glScalef(2.0,2.0,2.0);
	glColor3f(0.3,0.3,0.3);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0,14.0,3.0);
	glScalef(2.0,2.0,2.0);
	glColor3f(0.3,0.3,0.3);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
}

void rysuj_zad2(){
	glPushMatrix();
	glTranslatef(30.0,0.0,0.0);
	glColor3f(0,0,1.0);
	glutSolidSphere(5.0,20,20);
	glRotatef(wp,0,1,0);
	glTranslatef(20,0,0);

	glPushMatrix();
	glRotatef(spin,0,1,0);
	glColor3f(1.0,1.0,0);
	glutSolidSphere(2.0,20,20);
	glPopMatrix();

	glColor3f(0.3,0.3,0.3);
	glRotatef(wk,0,1.0,0);
	glTranslatef(-5,0,0);
	glutSolidSphere(0.5,20,20);
	glPopMatrix();

	wp=wp-0.25;
	spin=spin+1;
	wk=wk+0.5;
}

void rysuj_bwp()
{
	glPushMatrix();			
    glScalef(10.0, 1.4, 2.0);
	glColor3f(1.0,1.0,1.0);	
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
	glColor3f(1.0,1.0,1.0);	
    glTranslatef(0,1.1,0);
    glScalef(10.0, 0.8, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5, -0.7, 1.0);
	glColor3f(0.0,0.0,0.0);	
    gluCylinder(glowicaDyskD, 1, 1, 1, 36, 36);
    gluDisk(glowicaDyskD, 0,1,10,10);
    glTranslatef(0,0,1);
    gluDisk(glowicaDyskD, 0,1,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5, -0.7, -2.0);
    gluCylinder(glowicaDyskD, 1, 1, 1, 36, 36);
    gluDisk(glowicaDyskD, 0,1,10,10);
    glTranslatef(0,0,1);
    gluDisk(glowicaDyskD, 0,1,10,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5, -0.7, 1.0);
    gluCylinder(glowicaDyskD, 1, 1, 1, 36, 36);
    gluDisk(glowicaDyskD,0,1,10,10);
    glTranslatef(0,0,1);
    gluDisk(glowicaDyskD,0,1,10,10);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(3.5, -0.7, -2.0);
    gluCylinder(glowicaDyskD, 1, 1, 1, 36, 36);
    gluDisk(glowicaDyskD,0,1,10,10);
    glTranslatef(0,0,1);
    gluDisk(glowicaDyskD,0,1,10,10);
    glPopMatrix();

	  
    glPushMatrix();
    glTranslatef(1.5, 1.5,0);
	glColor3f(1.0,1.0,1.0);	
    glRotatef(obrotWiezyczki, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(glowicaDyskD, 2.0, 1.0 , 1.1, 36, 36);


    glPushMatrix();
    glTranslatef(0, 0, 0.55);
	glColor3f(1.0,1.0,1.0);	
    glRotatef(katLufy, 0, 1, 0);
    glRotatef(-90, 0, 1, 0);
    gluCylinder(glowicaDyskD, 0.15, 0.15, 4.5, 36, 36);
    glPopMatrix();

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
  glTranslatef(0, 0, zmodl);
  glRotatef(rotObsX, 1, 0, 0);
  glRotatef(rotObsY, 0, 1, 0);
  glRotatef(rotObsZ, 0, 0, 1);


  // Generacja obrazu sceny w niewidocznym buforze ramki
  RysujRamieRobota(rotPodstawy, rotRamienia1, rotRamienia2, rotGlowicy, rozUchwytow);
  rysuj_zad1();
  rysuj_zad2();
  rysuj_bwp();

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
  glViewport(0, 0, szerokosc+10, wysokosc);

  // Przejscie w tryb modyfikacji macierzy rzutowania
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50.0, (float)szerokosc/(float)wysokosc, 1.0, 1000.0);

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
      rotObsX = rotObsX + 1.0;
      break;

    case GLUT_KEY_DOWN:
      rotObsX = rotObsX - 1.0;
      break;

    case GLUT_KEY_LEFT:
      rotObsY = rotObsY - 1.0;
      break;

    case GLUT_KEY_RIGHT:
      rotObsY = rotObsY + 1.0;
      break;

	case GLUT_KEY_PAGE_UP:
		rotObsZ = rotObsZ + 1.0;
		break;

	case GLUT_KEY_PAGE_DOWN:
		rotObsZ = rotObsZ - 1.0;	
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

    case '3':
      rotRamienia2 = (rotRamienia2 < 0.0) ? rotRamienia2 + 1.0 : rotRamienia2;
      break;

    case '#':
      rotRamienia2 = (rotRamienia2 > -90.0) ? rotRamienia2 - 1.0 : rotRamienia2;
      break;

    case '4':
      rotGlowicy = (rotGlowicy < 360.0) ? rotGlowicy + 1.0 : rotGlowicy;
      break;

    case '$':
      rotGlowicy = (rotGlowicy > 0.0) ? rotGlowicy - 1.0 : rotGlowicy;
      break;

    case '5':
      rozUchwytow = (rozUchwytow < 1.5) ? rozUchwytow + 0.1 : rozUchwytow;
      break;

    case '%':
      rozUchwytow = (rozUchwytow > 0.5) ? rozUchwytow - 0.1 : rozUchwytow;
      break;

	  case '6':
	  zmodl = (zmodl <= odlmax) ? zmodl + 1.0 : zmodl;
	  break;

	  case '^':
	  zmodl = (zmodl >= odlmin) ? zmodl - 1.0 : zmodl;
	  break;

	  case 'd':
      obrotWiezyczki+=1.0;
      break;

	  case 'a':
      obrotWiezyczki-=1.0;
      break;
 
      case 's':
      if (katLufy >= 0.0)
      katLufy-=1.0;
      break;
 
      case 'w':
      if (katLufy <= 90.0)
      katLufy+=1.0;
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
  glutCreateWindow("Robot");

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
