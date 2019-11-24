package smo;
/**
 * @author Dariusz Pierzchala
 * 
 * Description: Description: Klasa gniazda obs³ugi obiektów - zg³oszeñ 
 */

import java.util.LinkedList;

import smo.RozpocznijObsluge;
import smo.ZakonczObsluge;
import smo.Zgloszenie;
import dissimlab.broker.INotificationEvent;
import dissimlab.broker.IPublisher;
import dissimlab.monitors.MonitoredVar;
import dissimlab.random.SimGenerator;
import dissimlab.simcore.BasicSimObj;
import dissimlab.simcore.SimEventSemaphore;
import dissimlab.simcore.SimControlException;



public class Smo extends BasicSimObj
{
    //private LinkedList <Zgloszenie> kolejka;
    private Kolejka kolejka;
    LinkedList<Zgloszenie> m=new LinkedList<Zgloszenie>();
    private boolean wolne = true;
    public RozpocznijObsluge rozpocznijObsluge;
    public ZakonczObsluge zakonczObsluge;
    private double prawdopodobienstwo;
    public int dlugosc;
    public MonitoredVar CzasOczekiwania;
    public MonitoredVar LiczbaZgloszen;
    
    /** Creates a new instance of Smo
     * @throws SimControlException */
    public Smo() throws SimControlException
    {
        // Utworzenie wewnêtrznej listy w kolejce
        //kolejka = new LinkedList <Zgloszenie>();
    	dlugosc=10;
        kolejka=new Kolejka(m,true,false,dlugosc);
        this.ustaw_prawdopodobienstwo(0.5);
        CzasOczekiwania=new MonitoredVar();
        LiczbaZgloszen=new MonitoredVar();
        LiczbaZgloszen.setValue(0.0);
    }

    // Wstawienie zg³oszenia do kolejki
    public int dodaj(Zgloszenie zgl)
    {
        if(kolejka.push(zgl)==true)
        {
        	
        	try
        	{
        		//zgl.startNiecierpliwienia = new StartNiecierpliwienia(zgl);
        		System.out.println("dodalem");
        		LiczbaZgloszen.setValue(LiczbaZgloszen.getValue()+1);
        	}
        	catch(Exception e)
        	{
        		System.out.println("no nie dodalem");
        	}
        }
        else
        {
        	System.out.println("Za mala kolejka nie moglem dodac!"+zgl.tenNr);
        }
        return kolejka.size();
    }

    // Pobranie zg³oszenia z kolejki
    public Zgloszenie usun()
    {
        Zgloszenie zgl = null;
        //Zgloszenie zgl = (Zgloszenie) kolejka.removeFirst();
        if(kolejka.size()>0)
        {
            zgl=(Zgloszenie) kolejka.m.getFirst();
            kolejka.pop();
            LiczbaZgloszen.setValue(LiczbaZgloszen.getValue()-1);
            CzasOczekiwania.setValue(simTime()-zgl.getCzasOdniesienia());
            return zgl;
        }
        else
        {
            System.out.println("nie mozna usunac z kolejki");
            return null;
        }
    }

    // Pobranie zg³oszenia z kolejki
    public boolean usunWskazany(Zgloszenie zgl)
    {
        //Boolean b= kolejka.remove(zgl);
        Boolean b= kolejka.usun_wskazane(zgl.tenNr);
        LiczbaZgloszen.setValue(LiczbaZgloszen.getValue()-1);
        return b;
    }
    
    public int liczbaZgl()
    {
        return kolejka.size();
    }

    public boolean isWolne() {
        return wolne;
    }

    public void setWolne(boolean wolne) {
        this.wolne = wolne;
    }
    
    public Kolejka get_Kolejka()
    {
    	return kolejka;
    }
    
    public void ustaw_prawdopodobienstwo(double p)
    {
    	this.prawdopodobienstwo=p;
    }
    
    public double get_pstwo()
    {
    	return this.prawdopodobienstwo;
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
    
    public boolean isfull()
    {
    	int size= kolejka.size();
    	if(size==this.dlugosc)
    		return true;
    	else
    		return false;
    }
}