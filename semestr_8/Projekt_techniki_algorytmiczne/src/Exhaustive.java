import java.util.HashSet;
import java.util.Set;

public class Exhaustive{
	
	private Set<Integer> GrandSet=new HashSet<Integer>();
	private Set<Set<Integer>> Subsets=new HashSet<Set<Integer>>();
	
	public Exhaustive(Set<Integer> Input, Set<Set<Integer>> Sets) {
		
		GrandSet.addAll(Input);
		Subsets.addAll(Sets);
		
	}
		
	public long ExhaustSearch() {	
		int ones=0;
		
		for(int i=0; i < Subsets.size(); i++) {// tyle jedynek ile licznosc zbioru
			ones=Integer.rotateLeft(ones,1);
			ones=ones|1;
		}
		
		
		
		
		Set<Set<Integer>> temp = new HashSet<Set<Integer>>();
		Set<Set<Integer>> BestSubsets = new HashSet<Set<Integer>>();
		Set<Integer> Clone=new HashSet<Integer>();
		
		int MinNumber=Generator.number_of_sets+1;
		
		for(int j=1; j<= ones; j++) {    ////////          generuj wszystkie mozliwe kombinacje podzbiorow
			temp.clear();               //  ty czysc
			int number=0;
			for(Set<Integer> i : Subsets) {
				if((j&(Integer.rotateLeft(1,number)))!=0) {
					temp.add(i);
					
				}
				number++;
				
			}
			
			
			Clone.clear();
			Clone.addAll(GrandSet);
			
			for(Set<Integer> i : temp) {
				//if(j.size()==1) {
					//System.out.println("s: "+ j);
				//}
				Clone.removeAll(i);
			
			if(Clone.isEmpty() && temp.size()<MinNumber) {	
				BestSubsets.clear();
				MinNumber=temp.size();
				BestSubsets.addAll(temp);
				}
			}
			
		}
	//	for(Set<Integer> i : BestSubsets)
		//	System.out.println("e:  :  "+i);
		
		
		//System.out.println("Znaleziono pokrycie Exh");
		return BestSubsets.size();
		}
		
	
	/*
		/// Redukcja zbiorow niepokrywajacych
		Set<Integer> Clone=new HashSet<Integer>();
		
		for(Set<Set<Integer>> i : Subsets) { 
		
			
			//	System.out.println(i);
			Clone.clear();
			Clone.addAll(GrandSet);
			
			for(Set<Integer> j : i) {
				//if(j.size()==1) {
					//System.out.println("s: "+ j);
				//}
				Clone.removeAll(j);
			}
			
			if(!Clone.isEmpty()) {				
				Subsets.remove(i);
				System.out.println("usuwam");
				}
		}
		
		System.out.println(Subsets.size());
		}
		*/
		
		
	

}