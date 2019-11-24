package smo;

import dissimlab.monitors.Diagram;
import dissimlab.monitors.Statistics;

/**
 * @author Dariusz Pierzchala
 * 
 * Description: Klasa g³ówna. Tworzy dwa SMO, inicjalizuje je.Startuje symulacjê. Wyœwietla statystyki.
 * 
 * Wersja testowa.
 */

import dissimlab.simcore.SimControlEvent;
import dissimlab.simcore.SimControlException;
import dissimlab.simcore.SimManager;
import dissimlab.simcore.SimParameters.SimControlStatus;

public class AppSMO {
	public static void main(String[] args) {
		try {
			SimManager model = SimManager.getInstance();
			// Powo³anie Smo 
			Smo smo = new Smo();
			// Utworzenie otoczenia
			Otoczenie generatorZgl = new Otoczenie(smo);
			// Dwa sposoby zaplanowanego koñca symulacji
			//model.setEndSimTime(10000);
			// lub
			//SimControlEvent stopEvent = new SimControlEvent(1000.0, SimControlStatus.STOPSIMULATION);
			SimControlEvent stopEvent = new SimControlEvent(2000.0, SimControlStatus.STOPSIMULATION);
			// Uruchomienie symulacji za poœrednictwem metody "startSimulation" 
			model.startSimulation();

			System.out.println("Czas oczekiwania:"); // statystyka czasu oczekiwania w kolejce
			System.out.println("-odchylenie standardowe: " + Statistics.standardDeviation(smo.CzasOczekiwania));
			System.out.println("-srednia: " + Statistics.arithmeticMean(smo.CzasOczekiwania));

			Diagram d1= new Diagram(Diagram.DiagramType.HISTOGRAM, "Czas oczekiwania"); // histogram
			d1.add(smo.CzasOczekiwania, java.awt.Color.RED);
			d1.show();
			
			System.out.println("Liczba elementow w kolejce:"); //statystyka liczba elementow w kolejce
			System.out.println("-odchylenie standardowe: " + Statistics.standardDeviation(smo.LiczbaZgloszen));
			System.out.println("-srednia: " + Statistics.arithmeticMean(smo.LiczbaZgloszen));
			
			Diagram d2= new Diagram(Diagram.DiagramType.HISTOGRAM, "Liczba elementów w kolejce");  // histogram
			d2.add(smo.LiczbaZgloszen, java.awt.Color.BLACK);
			d2.show();
			
			
		} catch (SimControlException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}
