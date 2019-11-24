package smo;
import java.util.LinkedList;

public class Kolejka
{
    LinkedList<Zgloszenie> m;
    boolean FIFO;
    boolean PRIORITY;
    int rozmiar;
    public Utylizer utylizer;
    public void sortuj()
    {
        
    }
    public Kolejka(LinkedList<Zgloszenie> m,boolean FIFO,boolean PRIORITY,int rozmiar )
    {
        this.m=m;
        this.FIFO=FIFO;
        this.PRIORITY=PRIORITY;
        utylizer = new Utylizer();
        if(rozmiar==(-1))
            this.rozmiar= 2147483647;
        else
            this.rozmiar=rozmiar;
        
    }
    public void dodaj_element(Zgloszenie e, LinkedList<Zgloszenie> m)
    {
        m.add(e);
    }
    public boolean push(Zgloszenie e)
    {
    	boolean dodanie_successfull=true;
        if(this.rozmiar>this.m.size())
        {
            if(this.PRIORITY==true)
            {
                if(this.FIFO==true)
                {
                    int i=0;
                    while((i<this.m.size() && (e.priorytet<=this.m.get(i).priorytet)))
                    {
                        i++;
                        //System.out.println("lol2");
                    }
                    if(i==this.m.size())
                        this.m.add(e);
                    else
                        this.m.add(i, e);
                }
                else
                {
                    int j=0;
                    while((j<this.m.size() && (e.priorytet<this.m.get(j).priorytet)))
                    {
                        j++;
                        //System.out.println("lol");
                    }
                    if(j==this.m.size())
                        this.m.add(e);
                    else
                        this.m.add(j, e);
                }
            }
            else
                this.m.add(e);
        }
        else
        {
        	 System.out.println("Nie mozna dodac do kolejki"+e.tenNr);
        	 dodanie_successfull=false;
        }
        return dodanie_successfull;
    }
    
    public void pop()
    {
            if(this.m.size()>0)
            {
                this.m.removeFirst();
            }
            else
                System.out.println("nie mo¿na usun¹æ");
    }
    
    public boolean usun_wskazane(int numer)
    {
        int i=0;
        while(this.m.get(i).tenNr!=numer)
        {
            i++;
        }
        if(i<this.m.size())
        {
            this.m.remove(i);
            utylizer.zwieksz();
            return true;
        }
        else
        {
            System.out.println("nie mozna usunac");
            return false;
        }
    }
    public void wypisz_liste()
    {
        for(int i=0;i<this.m.size();i++)
        {
            System.out.println("nr_zgloszenia "+this.m.get(i).tenNr+"    priorytet : "+this.m.get(i).priorytet);
        }
    }
    
    public int size()
    {
        return this.m.size();
    }
    
    public int wartosc_utylizer()
    {
    	return utylizer.get_utylizer();
    }
    
    
}