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

GLfloat odlmin =10.0;
GLfloat odlmax = 100.0;
GLfloat odleglosc = 40.0;
GLfloat rotObsZ = 0.0;
GLfloat rotObsY     = 40.0;
GLfloat rotObsX     = 40.0;
GLfloat rotPodstawy = 0.0;
GLfloat rotRamienia1= 40.0;
GLfloat rotRamienia2= -40.0;
GLfloat rotGlowicy  = 0.0; 
GLfloat rozUchwytow = 0.5;
GLfloat wp = 0;
GLfloat spin = 0;
GLfloat wk = 0;
// samolot
GLfloat rotSmigla = 0.0;
GLfloat rotSmiglamax = 360.0;

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
  glVertex3f(-200.0, 0.0, 0.0);
  glVertex3f(200.0, 0.0, 0.0);

  // Os Y
  glColor3f(0.0,1.0,0.0);
  glVertex3f(0.0, -200.0, 0.0);
  glVertex3f(0.0, 200.0, 0.0);

  // Os Z
  glColor3f(0.0,0.0,1.0);
  glVertex3f(0.0, 0.0, -200.0);
  glVertex3f(0.0, 0.0, 200.0);

  // Koniec tworzenia ukladu wspolrzednych
  glEnd();

  glColor3f(1.0,1.0,1.0);

  // Przygotowanie stosu macierzy modelowania
  glPushMatrix();

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

//RYSOWANIE WIE¯Y

void RysujWieze()
{
	/*// Pocztaek tworzenia ukladu wspolrzednych
	glBegin(GL_LINES);

	// Os X - CZERWONA
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-80.0, 0.0, 0.0);
	glVertex3f(80.0, 0.0, 0.0);

	// Os Y - ZIELONA
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -80.0, 0.0);
	glVertex3f(0.0, 80.0, 0.0);

	// Os Z - NIEBIESKA
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -80.0);
	glVertex3f(0.0, 0.0, 80.0);

	// Koniec tworzenia ukladu wspolrzednych*/
	glEnd();
	//odleglosc = 100;
	glPushMatrix();
	glTranslatef(-50, 0, 0);
	//rysowanie podstawy
	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glTranslatef(0, 5, 0);
	glScalef(4.23, 10, 4.23);
	glColor3f(1, 0, 0);
	glutSolidCube(1);
	glPopMatrix(); //koniec rysowania podstawy
	glPushMatrix();//rysowanie srodka
	glTranslatef(0, 11.5, 0);
	glScalef(8, 3, 8);
	glColor3f(0, 1, 0);
	glutSolidCube(1);
	glPopMatrix(); //koniec wysowania srodka
	glPushMatrix();
	glTranslatef(3, 14, -3);
	glScalef(2, 2, 2);
	glColor3f(0, 0, 1);
	glutSolidCube(1);
	glTranslatef(-3, 0, 0);
	glutSolidCube(1);
	glTranslatef(0, 0, 3);
	glutSolidCube(1);
	glTranslatef(3, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}

void Orbita()
{
	glPushMatrix();
	glTranslatef(0, 30.0, 0);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glutSolidSphere(5, 20, 20);

	glRotatef(wp, 0, 1, 0);
	glTranslatef(20, 0, 0);
	glPushMatrix();
	glRotatef(spin, 0, 0, 1);
	glColor3f(0, 1, 1);
	glutSolidSphere(2, 20, 20);
	glPopMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(wk, 0, 1, 0);
	glTranslatef(-5, 0, 0);
	glutSolidSphere(0.5, 20, 20);

	glPopMatrix();
	wp = wp - 0.1;
	spin = spin + 1;
	wk = wk + 0.1;
	glPopMatrix();

}

void Samolot(GLfloat obrotPodstawy, GLfloat obrotRamienia1,
	GLfloat obrotRamienia2, GLfloat obrotGlowicy,
	GLfloat rozstawUchwytow)
{
	glBegin(GL_LINES);

	// Os X
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-20.0, 0.0, 0.0);
	glVertex3f(20.0, 0.0, 0.0);

	// Os Y
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -20.0, 0.0);
	glVertex3f(0.0, 20.0, 0.0);

	// Os Z
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -20.0);
	glVertex3f(0.0, 0.0, 20.0);

	// Koniec tworzenia ukladu wspolrzednych
	glEnd();


	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(rotGlowicy, 0, 1, 0);
	glRotatef(rotRamienia2, 1, 0, 0);
	glTranslatef(0.0, 0.0, +5.0);
	glRotatef(rotRamienia1, 0, 0, 1);

	//narysowanie bloku g³ównego samolotu
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	// - sciany boczne
	glTranslatef(0.0, 0.0, -5.0);
	gluCylinder(podstawaSciany, 0.76, 0.76, 10.0, 20, 5);
	//glTranslatef(0.0, 0.0, -5.0);
	gluDisk(podstawaSciany, 0, 0.76, 20, 5);
	glPopMatrix();

	//narysowanie ogona
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	// - sciany boczne
	glTranslatef(0.0, 0.76 + 1, -5.0 + 0.75);
	//glRotatef(rotRamienia2, 1, 0, 0);
	glScalef(0.25, 2.0, 1.5);
	glutWireCube(1);
	glPopMatrix();


	//narysowanie stateczika stateczników
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	// - sciany boczne
	glTranslatef(0.76 + 1, 0.0, -5.0 + 0.75);
	//glRotatef(rotRamienia2, 1, 0, 0);
	glScalef(2.0, 0.25, 1.5);
	glutWireCube(1);
	glTranslatef(-(0.76 + 1), 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();

	//narysowanie skrzyde³
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	// - sciany boczne
	glTranslatef(0.0, 0.76 - 0.125, 0.0);
	//glRotatef(rotRamienia2, 1, 0, 0);
	glScalef(8.0, 0.25, 3);
	glutWireCube(1);
	glPopMatrix();

	//narysowanie dzioba
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	// - sciany boczne
	glTranslatef(0.0, 0.0, 5.0);
	//glRotatef(rotRamienia2, 1, 0, 0);
	//glScalef(0.75, 0.75, 0.75);
	gluSphere(podstawaSciany, 0.75, 20, 20);
	glPopMatrix();


	glRotatef(rotSmigla, 0, 0, 1);

	//narysowanie smigla
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	// - sciany boczne
	glTranslatef(0.0, 0.0, 5.0 + 0.75 + 0.125);
	//glRotatef(rotRamienia2, 1, 0, 0);
	glScalef(0.25, 4.0, 0.25);
	glutWireCube(1);
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
  glTranslatef(0, 0, -odleglosc);
  glRotatef(rotObsZ, 0, 0, 1);
  glRotatef(rotObsX, 1, 0, 0);
  glRotatef(rotObsY,0,1,0);


  // Generacja obrazu sceny w niewidocznym buforze ramki
  // RysujRamieRobota(rotPodstawy, rotRamienia1, rotRamienia2, rotGlowicy, rozUchwytow);

  // Rysowanie wie¿yczki
  RysujWieze();

  // Rysowanie uk³adu planetarnego

  Orbita();

 // if (rotSmigla<360) rotSmigla += 0.5;
 // else rotSmigla = 0.0;

  Samolot(rotPodstawy, rotRamienia1, rotRamienia2, rotGlowicy, rozUchwytow);
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
	switch (klawisz)
	{
	case GLUT_KEY_UP:
		rotObsX = (rotObsX < 180.0) ? rotObsX + 1.0 : -179;
		break;

	case GLUT_KEY_DOWN:
		rotObsX = (rotObsX > -180.0) ? rotObsX - 1.0 : 179;
		break;

	case GLUT_KEY_LEFT:
		rotObsY = (rotObsY > -180.0) ? rotObsY - 1.0 : 179;
		break;

	case GLUT_KEY_RIGHT:
		rotObsY = (rotObsY < 180.0) ? rotObsY + 1.0 : -179;
		break;

	case GLUT_KEY_PAGE_DOWN:
		rotObsZ = (rotObsZ > -180.0) ? rotObsZ - 1.0 : 179;
		break;

	case GLUT_KEY_PAGE_UP:
		rotObsZ = (rotObsZ < 180.0) ? rotObsZ + 1.0 : -179;
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
	 odleglosc = (odleglosc > odlmin) ? odleglosc - 1 : odleglosc;
	  break;

	  case '7':
	  odleglosc = (odleglosc < odlmax) ? odleglosc + 1 : odleglosc;
	  break;
	  case '8':
		  rotSmigla = (rotSmigla < rotSmiglamax) ? rotSmigla + 1 : rotSmigla;
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
