package SurvivalRace;
/**
 * importuje biblioteki.
 */
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.util.ArrayList;
import java.util.Random;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.Timer;
/**
 * Klasa ta implementuje obiekt, który jest gr¹ SurvivalRace
 * @author Damian
 *@version 1.0
 */
public class SurvivalRace implements ActionListener, MouseListener, KeyListener {
	
	/**
	 * zmienne odpowiadaj¹ce obrazkom do³¹czonym do grafiki
	 */
	public Image boki, droga, samochod, przeszkody;
	public Image race;
	public static SurvivalRace survivalrace;

	public boolean odbij = false;
	/**
	 * ustalam wysokoœæ i szerokoœæ ramki.
	 */
	public final int WIDTH = 800, HEIGHT = 900;

	public Renderer renderer;

	/**
	 * pocz¹tkowa prêdkoœæ.
	 */
	public int speed = 3,tmp=40;
	int counter=0;
	/**
	 * zmienna dzielnik odnosi siê do szybkoœci zmiany prêdkoœci 
	 */
	
	//public final int dzielnik=10;
	/**
	 * prostok¹ty odpowiadaj¹ce samochodowi i bocznym banerom.
	 */
	public Rectangle car, boklewy, bokprawy;

	/**
	 * zmienne pomocnicze
	 */
	public int ticks, yMotion, score, best_score;

	public int move = 40;

	/**
	 * flagi wp³ywaj¹ce na metodê repaint.
	 */
	public boolean deletion, sciana, gameOver, started;

	/**
	 * Lista przeszkód
	 */
	public ArrayList<Rectangle> columns;

	/**
	 * zmienne potrzebne dla muzyki
	 */
	public Clip clip,clip2;
	/**
	 * zmienne ustawiaj¹ce wartoœæ randomow¹
	 */
	public Random rand;
	JFrame jframe;
/**
 * Ten konstruktor tworzy obiekty typu JFrame, czyli tworzy nam ramkê na której bêdzie wyœwietlana 
 * gra. Powo³uje nam on Timer, który bêdzie automatycznie co jednostkê czasu wykonywa³ to co jest podane w jego argumencie na drugim miejscu  (czyli ActionListener)
 * 
 */
	public SurvivalRace() {
		race = new ImageIcon("res/img/flag.png").getImage();
		jframe = new JFrame();
		Timer timer = new Timer(20, this);
	
		renderer = new Renderer();
		rand = new Random();
		jframe.setTitle("Survival Race");

		jframe.setIconImage(race);
		jframe.add(renderer);
		/**
		 * ustawienia dla ramki
		 */
		jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jframe.setResizable(false);
		jframe.setSize(WIDTH, HEIGHT);
		
		/**
		 * dodanie obs³ugi zdarzeñ
		 */
		jframe.addMouseListener(this);
		jframe.addKeyListener(this);
		jframe.setVisible(true);
		jframe.isDoubleBuffered();
		
		/**
		 * pocz¹tkowa inicjalizacja wyœwietlanych obrazków
		 */
		car = new Rectangle(WIDTH / 2 - 10, HEIGHT - 250, 20, 20);
		boklewy = new Rectangle(0, 0, 50 * jframe.getWidth() / WIDTH, jframe.getHeight());
		bokprawy = new Rectangle(WIDTH - 50 * jframe.getWidth() / WIDTH, 0, 50 * jframe.getWidth() / WIDTH,jframe.getHeight());
		System.out.println("" + car.x + car.y);
		columns = new ArrayList<Rectangle>();
		addColumn(true);
		addColumn(true);
		timer.start();
		
		/**
		 * w³aczenie muzyki.
		 */
		playSound();

	}

	/**
	 * Metoda obrazki() powo³uje nam do ¿ycia grafikê pobieran¹ z folderu res/img.
	 */
	public void obrazki() {
		boki = new ImageIcon("res/img/boki.jpg").getImage();
		droga = new ImageIcon("res/img/droga.jpg").getImage();
		samochod = new ImageIcon("res/img/samochod.png").getImage();
		przeszkody = new ImageIcon("res/img/obstacle.jpg").getImage();

	}

	/**
	 * Metoda ta rysuje obrazki, które zosta³y za³adowane w metodzie obrazki();
	 * @param g - grafika, w której narysowane bêd¹ obrazki
	 */
	public void ladujobrazki(Graphics g) {
		g.drawImage(boki, 0, 0, 50 * jframe.getWidth() / WIDTH, jframe.getHeight(), renderer);
		g.drawImage(droga, 50 * jframe.getWidth() / WIDTH, 0, WIDTH - 2 * (50 * jframe.getWidth() / WIDTH),
				jframe.getHeight(), renderer);
		g.drawImage(boki, WIDTH - 50 * jframe.getWidth() / WIDTH, 0, 50 * jframe.getWidth() / WIDTH, jframe.getHeight(),
				renderer);
		g.drawImage(samochod, car.x - 20, car.y - 5, 60, 60, renderer);

	}

	/**
	 * Metoda ta ustawia pacho³ki na grafice g, czyli ustawia przeszkody, które bêd¹ wystêpowa³y przed pojazdem
	 * @param g - grafika, w której narysowane bêd¹ przeszkody
	 */
	public void rysujprzeszkody(Graphics g) {
		for (Rectangle kolumny : columns) {
			int ilenaprzeszkode;
			int ilosc = (int) kolumny.getWidth() / 100;
			int dlugosc = (int) kolumny.getWidth();
			if (ilosc != 0)
				ilenaprzeszkode = (dlugosc / ilosc)/2;
			else
				ilenaprzeszkode = 1;

			System.out.println("" + dlugosc);
			// column.x, column.y, column.width, column.height
			for (int i = 0; i < ilosc*2; i++) {

				g.drawImage(przeszkody, kolumny.x + i * ilenaprzeszkode, kolumny.y, ilenaprzeszkode, 100, renderer);
			}

			// g.drawImage(przeszkody, kolumny.x+ilosc*100,
			// kolumny.y,dlugosc-ilosc*100,100, renderer);

		}
	}

	/**
	 * Metoda ta dodaje w grze grunt pod przeszkody. Zapewnia ona sta³e pojawianie siê przeszkód oraz w przypadku nie u¿ywania ju¿ starych przeszkód nadzoruje ich usuniecie.
	 * @param start - zmienna typu boolean mówi¹ca o tym czy gra siê zaczê³a czy nie.
	 */
	public void addColumn(boolean start) {
		// int space=300;
		int szerokosc = 50 + rand.nextInt(600);
		int wysokosc = 100;
		int przerwa = 150;

		if (start) {
			columns.add(new Rectangle(50, -columns.size() * 300, szerokosc - 100, wysokosc));
			columns.add(new Rectangle(50 + szerokosc + przerwa, -(columns.size() - 1) * 300,
					WIDTH - szerokosc - przerwa - 100, wysokosc));
		} else {
			columns.add(new Rectangle(50, columns.get(columns.size() - 1).y - 400, szerokosc - 100, wysokosc));
			columns.add(new Rectangle(50 + szerokosc + przerwa, columns.get(columns.size() - 1).y,
					WIDTH - szerokosc - przerwa - 100, wysokosc));
		}
	}

	/**
	 * Metoda odnosz¹ca siê do ActionListener, któa w zale¿noœci od tego jakie poœrednio flagi zosta³y podniesione lub opuszczone, steruje p³ynnoœci¹ gry -
	 *  wywo³uje metodê repaint.
	 */
	public void actionPerformed(ActionEvent e) {

		if (started && !gameOver) {
			for (int i = 0; i < columns.size(); i++) {
				Rectangle column = columns.get(i);
				column.y += speed;
			}

			/**
			 * usuwanie ju¿ niepotrzebnych przeszkód
			 */
			for (int i = 0; i < columns.size(); i++) {
				Rectangle column = columns.get(i);
				if (column.y > HEIGHT) {
					columns.remove(column);
					deletion = true;
					addColumn(false);
				}
			}

		}

		/**
		 * jeœli przeszkoda wyjdzie poza jakiœ zakres, wtedy zwiêkszana jest punktacja zale¿na oid iloœci przeszkód i szybkoœci
		 */
		for (Rectangle column : columns) {
			if (column.x == 50 && car.y + car.height / 2 > column.y + column.height / 2 - speed
					&& car.y + car.height / 2 < column.y + column.height / 2 +speed) {
				score++;
			}
		}

		/**
		 * jeœli samochód uderzy w przeszkodê, wtedy siê zatrzymuje
		 */
		for (Rectangle column : columns) {
			if (column.intersects(car)) {
				gameOver = true;
				car.y = column.y + column.height;
			}
		}

		/**
		 * jeœli samochód uderzy w œcianê, wtedy podnoszona jest flaga odbij i wyœwietlany komunikat odjedŸ od œciany
		 */
		if (boklewy.intersects(car)) {
			car.x = boklewy.x + boklewy.width;
			odbij = true;
		} else if (bokprawy.intersects(car)) {
			car.x = bokprawy.x - car.width;
			odbij = true;
		} else {
			odbij = false;
		}

		/**
		 * postêpowanie samochodu na wypadek wyjazdu poza ramkê
		 */
		if (car.y >= HEIGHT - car.height) {
			car.y = HEIGHT - car.height;
		}

		if (car.x < 50 || car.x > WIDTH - 50) {
			sciana = true;
		}

		if (deletion) {
			deletion = false;
			acceleration();
		}
		
		if(car.x<boklewy.width)
			
		{
			car.x=boklewy.width;
			sciana=true;
		}
	
		if(car.x>jframe.getWidth()-bokprawy.width)
			
		{
			car.x=jframe.getWidth()-bokprawy.width-car.width;
			sciana=true;
		}

		renderer.repaint();
	}

	/**
	 *  powoduje zwiêkszenie szybkoœci przesuwania siê pojazdu(poprzez przesuwanie obiektów w dó³) o jednostkê szybciej.
	 */
	public void acceleration() {
		if(counter==5)
		{
			speed += 1;
			counter=0;
		}
		else
			counter++;
	}

	/**
	 * metoda ta pozwala na poruszanie siê samochodu w lewo.
	 */
	/*public void move_left() {
		if (!started) {
			started = true;
		} else {
			car.x = car.x - move;
		}
	}
	*/
	public void move_left()
	{
		if(gameOver)
		{
			car=new Rectangle(WIDTH/2-10,HEIGHT/2-10,20,20);
			columns.clear();
			score=0;
			move=40;
			speed=3;
			counter=0;
			addColumn(true);
			addColumn(true);
			addColumn(true);
			addColumn(true);
			gameOver=false;
		}
		if(!started)
		{
			started=true;
		}
		else if(!gameOver)
		{
			car.x = car.x - move;
		}
	}
	/**
	 * metoda ta pozwala na poruszanie siê samochodu do przodu.
	 */
	public void move_forward() {
		if (!started) {
			started = true;
		} else {
			car.y = car.y - move;
		}
	}

	/**
	 * metoda ta pozwala na poruszanie siê samochodu do ty³u.
	 */
	public void move_back() {
		if (!started) {
			started = true;
		} else {
			car.y = car.y + move;
		}
	}

	/**
	 * metoda ta pozwala na poruszanie siê samochodu w prawo.
	 */
	public void move_right() {
		if (!started) {
			started = true;
		} else {
			car.x = car.x + move;
		}
	}

	/**
	 * metoda ta pozwala rozpoczêcie gry.
	 */
	public void launch() {
		if (!started) {
			started = true;
		}
		if (gameOver) {

		}
	}

	/**
	 * metoda ta daje mo¿liwoœæ dwa razy szybszego poruszania siê samochodu w ka¿dym kierunku.
	 */
	public void extra_power() {
		move = 2 * move;
	}

	/**
	 * metoda ta przywraca pierwotn¹ szybkoœæ samochodu.
	 */
	public void normal_power() {
		
		move = tmp;
	}

	/**
	 * metoda ta rysuje prostok¹ty odpowiadaj¹ce gruntowi zrobionemu pod przeszkody.
	 */
	public void paintColumn(Graphics g, Rectangle column) {

		g.setColor(Color.gray.darker());
		g.fillRect(column.x, column.y, column.width, column.height);
		rysujprzeszkody(g);
	}


	/**
	 * Metoda ta zapewnia aktualizacjê okna gry wyœwietlanego u¿ytkownikowi.
	 * @param g - grafika która jest poddawana aktualizacji
	 */
	public void repaint(Graphics g) {
		obrazki();
		g.setColor(Color.green);
		g.fillRect(0, 0, WIDTH, HEIGHT);
		ladujobrazki(g);
		g.setColor(Color.red);
		// g.fillRect(car.x, car.y, car.width, car.height);

		for (Rectangle column : columns) {
			paintColumn(g, column);
		}
/**
 * ustawianie koloru tekstu i czcionki.
 */
		g.setColor(Color.white);
		g.setFont(new Font("Arial", 1, 25));

		if (!started) {
			g.drawString("Press space to launch", 75, HEIGHT / 2 - 50);
		}
		g.setFont(new Font("Arial", 1, 100));
		if (gameOver) {
			g.drawString("Game Over", 100, HEIGHT / 2 - 50);
			if(best_score<score)
			{
				best_score=score;
			}
			g.setFont(new Font("Arial", 1, 20));
			g.drawString("Best score is: "+best_score, 100, HEIGHT / 2 );
			g.drawString("Press 4 to start again", 100, HEIGHT / 2 + 30 );
		}

		if (!gameOver && started) {
			g.setColor(Color.black.darker());
			g.drawString(String.valueOf(score), WIDTH / 2 - 25, 100);
		}

		if (odbij) {
			g.setFont(new Font("Arial", 1, 20));
			g.drawString("Odjedz od sciany", WIDTH / 2 - 100, 20);
			// odbij=false;
		}

	}

	/**
	 * metoda do odtwarzania muzyki w czasie trwania gry.
	 */
	public void playSound() {
		try {
			AudioInputStream audioInputStream = AudioSystem
					.getAudioInputStream(new File("res/music/music1.wav").getAbsoluteFile());
			Clip clip = AudioSystem.getClip();
			clip.open(audioInputStream);
			clip.start();
			
		} catch (Exception ex) {
			System.out.println("Error with playing sound.");
			ex.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		survivalrace = new SurvivalRace();
	}

	/**
	 * metoda odnosz¹ca siê do sterowania samochodem, obs³uga klawiatury za pomoc¹ KeyListenera
	 */
	public void keyPressed(KeyEvent e) {

		if (e.getKeyCode() == KeyEvent.VK_S || e.getKeyCode() == KeyEvent.VK_NUMPAD5) {
			move_back();
		} else if (e.getKeyCode() == KeyEvent.VK_W || e.getKeyCode() == KeyEvent.VK_NUMPAD8) {
			move_forward();
		} else if (e.getKeyCode() == KeyEvent.VK_A || e.getKeyCode() == KeyEvent.VK_NUMPAD4) {
			move_left();
		} else if (e.getKeyCode() == KeyEvent.VK_D || e.getKeyCode() == KeyEvent.VK_NUMPAD6) {
			move_right();
		} else if (e.getKeyCode() == KeyEvent.VK_SPACE) {
			launch();
		} else if (e.getKeyCode() == KeyEvent.VK_CONTROL) {
			extra_power();
		}

	}

	@Override
	public void keyReleased(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_CONTROL) {
			normal_power();
		}
	}

	@Override
	public void keyTyped(KeyEvent arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseClicked(MouseEvent e) {

	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub

	}

}
