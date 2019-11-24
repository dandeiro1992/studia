package smo;

import smo.KoniecNiecierpliwienia;
import smo.Smo;
import smo.StartNiecierpliwienia;
import dissimlab.broker.INotificationEvent;
import dissimlab.broker.IPublisher;
import dissimlab.random.SimGenerator;
import dissimlab.simcore.BasicSimObj;
import dissimlab.simcore.SimControlException;

/**
 * Description: Klasa zgloszenia obs≥ugiwanego w gnieüdzie obs≥ugi.
 * 
 * @author Dariusz Pierzchala
 */

public class Zgloszenie extends BasicSimObj
{
    public double czasOdniesienia;
    static int nr=0;
    int tenNr;
    StartNiecierpliwienia startNiecierpliwienia;
    public KoniecNiecierpliwienia koniecNiecierpliwosci;
    public Smo smo;
    public int priorytet;
    private SimGenerator generator;
    

    public Zgloszenie(double Czas, Smo smo) throws SimControlException
    {
        czasOdniesienia = Czas;
        setTenNr();
        this.smo = smo;
        //startNiecierpliwienia = new StartNiecierpliwienia(this);
        generator = new SimGenerator();
        this.priorytet=generator.uniformInt(1,10);
    }

    @Override
    public void reflect(IPublisher publisher, INotificationEvent event) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public boolean filter(IPublisher publisher, INotificationEvent event) {
        // TODO Auto-generated method stub
        return false;
    }

    public void setTenNr() {
        this.tenNr = nr++;
    }

    public int getTenNr() {
        return tenNr;
    }
    
    public double getCzasOdniesienia()
    {
    	return czasOdniesienia;
    }

}

