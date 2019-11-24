package smo;

import dissimlab.simcore.BasicSimEvent;
import dissimlab.simcore.SimControlException;
import dissimlab.simcore.SimParameters.SimDateField;

/**
 * 
 * @author Dariusz Pierzchala

 */
public class KoniecNiecierpliwienia extends BasicSimEvent<Zgloszenie, Object>
{
    private Zgloszenie parent;

    public KoniecNiecierpliwienia(Zgloszenie parent, double delay) throws SimControlException
    {
    	super(parent, delay);
        this.parent = parent;
    }

    public KoniecNiecierpliwienia(Zgloszenie parent) throws SimControlException
    {
    	super(parent);
        this.parent = parent;
    }
    
	@Override
	protected void onInterruption() throws SimControlException {
        System.out.println(simTime()+" - "+simDate(SimDateField.HOUR24)+" - "+simDate(SimDateField.MINUTE)+" - "+simDate(SimDateField.SECOND)+" - "+simDate(SimDateField.MILLISECOND)+": Przerwanie niecierpliwoœci zgl. nr: " + parent.getTenNr());
	}

	@Override
	protected void onTermination() throws SimControlException {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected void stateChange() throws SimControlException {
        System.out.println(simTime()+" - "+simDate(SimDateField.HOUR24)+" - "+simDate(SimDateField.MINUTE)+" - "+simDate(SimDateField.SECOND)+" - "+simDate(SimDateField.MILLISECOND)+": Koniec niecierpliwoœci zgl. nr: " + parent.getTenNr());
        if (parent.smo.usunWskazany(parent)){
            System.out.println(simTime()+" - "+simDate(SimDateField.HOUR24)+" - "+simDate(SimDateField.MINUTE)+" - "+simDate(SimDateField.SECOND)+" - "+simDate(SimDateField.MILLISECOND)+": Usuniêto z kolejki zgl. nr: " + parent.getTenNr() + " usunieto juz: " +parent.smo.get_Kolejka().wartosc_utylizer());
        }
        else
            System.out.println(simTime()+" - "+simDate(SimDateField.HOUR24)+" - "+simDate(SimDateField.MINUTE)+" - "+simDate(SimDateField.SECOND)+" - "+simDate(SimDateField.MILLISECOND)+": Problem z usuniêciem z kolejki zgl. nr: " + parent.getTenNr());       	
	}

	@Override
	public Object getEventParams() {
		// TODO Auto-generated method stub
		return null;
	}
}