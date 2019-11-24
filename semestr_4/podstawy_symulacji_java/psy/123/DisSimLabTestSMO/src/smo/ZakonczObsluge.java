package smo;
/**
 * @author Dariusz Pierzchala
 * 
 * Description: Zdarzenie koñcowe aktywnoœci gniazda obs³ugi. Koñczy obs³ugê przez losowy czas obiektów - zg³oszeñ.
 */

import dissimlab.random.SimGenerator;
import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;
import dissimlab.simcore.SimEventSemaphore;
import dissimlab.simcore.SimParameters.SimDateField;

public class ZakonczObsluge extends BasicSimEvent<Smo, Zgloszenie>
{
    private Smo smoParent;
    private SimGenerator wrocic;
    
    ZakonczObsluge(Smo parent, double delay, Zgloszenie zgl) throws SimControlException
    {
    	super(parent, delay, zgl);
        this.smoParent = parent;
    }

    public ZakonczObsluge(Smo parent, SimEventSemaphore semafor, Zgloszenie zgl) throws SimControlException
    {
    	super(parent, semafor, zgl);
        this.smoParent = parent;
    }
    
	@Override
	protected void onInterruption() throws SimControlException {
		// TODO
	}

	@Override
	protected void onTermination() throws SimControlException {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected void stateChange() throws SimControlException {
  		smoParent.setWolne(true);
  		wrocic = new SimGenerator();
        System.out.println(simTime()+" - "+simDate(SimDateField.HOUR24)+" - "+simDate(SimDateField.MINUTE)+" - "+simDate(SimDateField.SECOND)+" - "+simDate(SimDateField.MILLISECOND)+": SMO- Koniec obs³ugi zgl. nr: " + transitionParams.getTenNr());
        if(!wrocic.probability(smoParent.get_pstwo()))
        {
        	System.out.println("dodaje"+transitionParams.getTenNr());
        	transitionParams.czasOdniesienia=simTime();
        	smoParent.dodaj(transitionParams);
        	System.out.println("Wchodze tutaj i bede dodawal");
        }
      	// Zaplanuj dalsza obs³uge w tym gnieŸdzie
      	if (smoParent.liczbaZgl() > 0)
       	{
      		smoParent.rozpocznijObsluge = new RozpocznijObsluge(smoParent);        	
       	}	
	}

	@Override
	public Object getEventParams() {
		// TODO Auto-generated method stub
		return null;
	}
}