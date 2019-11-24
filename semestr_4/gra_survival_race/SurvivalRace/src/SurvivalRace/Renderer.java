package SurvivalRace;

import java.awt.Graphics;

import javax.swing.JPanel;
/**
 * Renderer to klasa, kt�ra rozszerza klas� JPanel. Oznacza to, �e posiada ona wszystkie 
 * metody, kt�re zawiera JPanel.
 * @author Damian
 *@param serialVersionUID ustawia na default
 */
public class Renderer extends JPanel
{
	
	private static final long serialVersionUID = 1L;
/**
 * Metoda ta wywo�ywana jest zawsze wtedy gdy wyst�puje zjawisko przemalowania istniej�cej grafiki g podawanej jako parametr
 * 
 * @param graphics g
 */
	protected void paintComponent(Graphics g) 
	{
		this.setDoubleBuffered(true);
		super.paintComponent(g);
		SurvivalRace.survivalrace.repaint(g);
	}
}
