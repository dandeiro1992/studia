import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;
import ptolemy.plot.Plot;
import ptolemy.plot.PlotApplication;

public class Generator 
{

	
	ArrayList<Long> time_results_exact=new ArrayList<Long>();
	ArrayList<Long> time_results_greedy=new ArrayList<Long>();
	ArrayList<Long> memory_results_exact=new ArrayList<Long>();
	ArrayList<Long> memory_results_greedy=new ArrayList<Long>();
	ArrayList<Long> size_results_exact=new ArrayList<Long>();
	ArrayList<Long> size_results_greedy=new ArrayList<Long>();
	
	Set<Integer> GrandSet=new HashSet<Integer>(); 
	Set<Set<Integer>> SubSets=new HashSet<Set<Integer>>(); ; 
	
	
	boolean CoverPossible;
	boolean Greed;
	boolean Exhaust;
	int number_of_tests; // 
	static int number_of_sets; 
	int number_of_elements; // poczatkowo jak duzy zbior
	int CoKtoryElement=3; // co ktory dodawany do podzbioru
	int NumberOfTries;  // z ilu prob srednia
	int Interval=10;  // o ile elementow zwiekszamy co probe
	int IntervalSet=1;
	
	public Generator(int a, int b, int c, int d, int g, int h, boolean G, boolean E) {
		number_of_elements=a;
		number_of_sets=b;
		number_of_tests=c;
		NumberOfTries=d;
		Interval=g;
		IntervalSet=h;
		Greed=G;
		Exhaust=E;
	}
	
	
	
	
	
	public void generateSet() {
		
		GrandSet.clear();
		SubSets.clear();
		CoverPossible=false;
		
		while(GrandSet.size()<=number_of_elements) {
		//for(int i=0; i<number_of_elements; i++) { // generuj zbior
		GrandSet.add((int)(Math.random()*100*number_of_elements)%(number_of_elements*2));
		//System.out.println(GrandSet.size()+"   "+number_of_elements);
		}
			
		
		do {
			SubSets.clear();
		for(int i =0; i<number_of_sets; i++) {     //   generuj podzbiory
			Set<Integer> Set = new HashSet<Integer>();
			
			for(Integer j : GrandSet){ // tyle elementów
				if((int)(Math.random()*1000)%(CoKtoryElement)==0)
				Set.add(j);
			}
			SubSets.add(Set);
		}
		

		Set<Integer> Clone=new HashSet<Integer>();
		Clone.clear();
		Clone.addAll(GrandSet);
		for(Set<Integer> i : SubSets) {   ////     Sprawdz czy podzbiorem mozna pokryc
			Clone.removeAll(i);
		}
			if(Clone.isEmpty()) {				
				CoverPossible=true;
				}
		
		}while(!CoverPossible);
		
		
		//System.out.println("Zbior: " + GrandSet.toString());
		//System.out.println("Podzbiory: " + SubSets.toString());
		
		
		
	
	}
	
	
	public void test() {
		
		for(int j=0; j<number_of_tests; j++) {
			
		//System.out.println("Numer testu: "+ (j+1));
		
		long start;
		long end;
		long GreedyTime=0;
		long ExhTime=0;
		long ExhSize=0;
		long GreedSize=0;
		number_of_elements=number_of_elements+Interval;
		number_of_sets=number_of_sets+IntervalSet;
		generateSet();
		
		
		for(int i=0; i<NumberOfTries; i++) {

			
			if(Exhaust) {
				Exhaustive exh=new Exhaustive(GrandSet, SubSets);
				start = System.nanoTime();
				ExhSize=exh.ExhaustSearch();
				end = System.nanoTime();
				ExhTime=ExhTime+(end-start);
			}
			
			if(Greed) {
				Greedy greed= new Greedy(GrandSet, SubSets);
				start = System.nanoTime();
				GreedSize=greed.greedySetCover();
				end = System.nanoTime();
				GreedyTime=GreedyTime+(end-start);
			}
			
			
		}
		
		
		if(Exhaust) { 
			time_results_exact.add(ExhTime/NumberOfTries);
			memory_results_exact.add((long)(2*number_of_elements+number_of_sets*(number_of_elements+number_of_sets+1)/2));
			size_results_exact.add(ExhSize);
		}
		if(Greed) {
			time_results_greedy.add(GreedyTime/NumberOfTries);
			memory_results_greedy.add((long)(2*number_of_elements+(2*number_of_elements+number_of_sets+1)/2));
			size_results_greedy.add(GreedSize);
		}
		
		
		
		}
		
		draw();
	}
	
	
	
	
	
	
	
	/*
	public void generate()
	{
		for(int i=0;i<number_of_tests;i++)
		{
			for (int k=0;k<(i+1)*number_of_sets+1;k++)
			{
				ArrayList<Integer> row=new ArrayList<Integer>();
				table.list.add(row);
			}
			for(int j=1;j<number_of_numbers*(int)Math.pow(2, i);j++)
			{
				table.list.get(0).add(j);
				table.list.get(1 + (int)(Math.random() * ((((i+1)*number_of_sets) - 1) + 1))).add(j);
			}
			for(int l=0;l<table.list.get(0).size();l++)
		    {
		    	table.entry_data.add(table.list.get(0).get(l));
		    }
			//System.out.println("size of the list 1:   "+table.list.size());
			//table.show_list();
			//////////////exact algorithm
			start = System.nanoTime();
			table.exact_algorithm();
			end = System.nanoTime();
			time_results_exact.add(end-start);
			///////////////// greedy_set_cover
			start = System.nanoTime();
			table.greedy_set_cover();
			end = System.nanoTime();
			time_results_greedy.add(end-start);
			
			
			table.list.clear();
			table.entry_data.clear();
			table.list.clear();
			//System.out.println("size of the list 2:   "+table.list.size());
			
		}
		System.out.println("times for exact:   "+time_results_exact.toString());
		System.out.println("times for greedy:   "+time_results_greedy.toString());
		draw(time_results_exact,time_results_greedy);
	}
	*/
	
	
	
	
	
	public void draw() //ArrayList<Long> time_results_exact2,ArrayList<Long> time_results_greedy2)
	{
		Plot myPlot = new Plot();
		myPlot.setTitle("algorithm time measures");
        myPlot.setXLabel("try number");
        myPlot.setYLabel("time");
        myPlot.setMarksStyle("dots", 0);
        
        Plot memoryPlot = new Plot();
        memoryPlot.setTitle("algorithm memory measures");
        memoryPlot.setXLabel("try number");
        memoryPlot.setYLabel("memory");
        memoryPlot.setMarksStyle("dots", 0);
        
        Plot sizePlot = new Plot();
        sizePlot.setTitle("algorithm result size measures");
        sizePlot.setXLabel("try number");
        sizePlot.setYLabel("result size");
        sizePlot.setMarksStyle("dots", 0);
        
        for(int i=0;i<number_of_tests;i++)
        {
        	if(Exhaust) {
        		myPlot.addPoint(0, (double)i, (double)time_results_exact.get(i), true);
        		memoryPlot.addPoint(0, (double)i, (double)memory_results_exact.get(i), true);
        		sizePlot.addPoint(0, (double)i, (double)size_results_exact.get(i), true);
        	}
        	if(Greed) {
        		myPlot.addPoint(1, (double)i, (double)time_results_greedy.get(i),true);
        		memoryPlot.addPoint(1, (double)i, (double)memory_results_greedy.get(i), true);
        		sizePlot.addPoint(1, (double)i, (double)size_results_greedy.get(i), true);
        	}
        }
        PlotApplication app = new PlotApplication(myPlot);
        app.setSize(800, 400);
        app.setLocation(100, 100);
        app.setTitle("Time");
        
        PlotApplication ap = new PlotApplication(memoryPlot);
        ap.setSize(800, 400);
        ap.setLocation(100, 500);
        ap.setTitle("Memory");
        
        PlotApplication a = new PlotApplication(sizePlot);
        a.setSize(800, 400);
        a.setLocation(900, 100);
        a.setTitle("Size");
        
        if(Exhaust)System.out.println(time_results_exact.toString());
        if(Greed)System.out.println(time_results_greedy.toString());
	}

}
