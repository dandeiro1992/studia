
import java.util.HashSet;
import java.util.Set;


public class Greedy{
	
	private Set<Integer> GrandSet=new HashSet<Integer>();;
	private Set<Set<Integer>> Subsets=new HashSet<Set<Integer>>();;
	
	public Greedy(Set<Integer> Input, Set<Set<Integer>> Sets){
		

			GrandSet.addAll(Input);
			Subsets.addAll(Sets);
		
	}
	
	public long greedySetCover() {

		int MaxSize;
		int SubsetsInitSize=Subsets.size();
		Set<Integer> BestSet=new HashSet<Integer>(); 
		Set<Integer> Uncovered =new HashSet<Integer>();    //   U
		Set<Integer> Covered = new HashSet<Integer>();
		Covered.clear();
		
		Uncovered.addAll(GrandSet);
		
		while(!Uncovered.isEmpty()) {
			MaxSize=GrandSet.size();
			
			//Uncovered.addAll(GrandSet);

			for(Set<Integer> i : Subsets) {
				Uncovered.removeAll(i);
				
				if(Uncovered.size()<MaxSize) {	
					BestSet.clear();
					BestSet.addAll(i);
					MaxSize=Uncovered.size();
				}	
				Uncovered.addAll(i);
				
			}
			Uncovered.removeAll(BestSet);
			Covered.addAll(BestSet);
			Subsets.remove(BestSet);
		}
		//System.out.println("Znaleziono pokrycie Greed");
		return SubsetsInitSize-Subsets.size();
	}
	
	
	
}