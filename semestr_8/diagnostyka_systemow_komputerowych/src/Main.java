import java.util.ArrayList;

public class Main 
{
	public static void main(String[] args) throws InterruptedException 
	{
		Graph graph=new Graph();
		graph.insert_data();
		System.out.println("macierz wyjsciowa:");
		graph.display_matrix();
		/*graph.condition_1();
		graph.condition_2();
		graph.precessors(2);
		graph.successors(2);*/
		/*ArrayList<Integer> ro=new ArrayList<Integer>();
		ro.add(1);
		ro.add(3);
		ro.add(5);
		
		ArrayList<Integer> ro_2=new ArrayList<Integer>();
		ro_2.add(1);
		ro_2.add(3);
		ro_2.add(5);
		
		Graph.set_comparison(ro, ro_2);*/
		//System.out.println(graph.mi_minus(2));
		if((graph.condition_1()) && (graph.condition_2()) && (graph.condition_3()))
		{
			System.out.println("system jest m- diagnozowalny");
			Graph test=new Graph();
			graph.copy(test);
			//test.display_matrix();
			
			test.coordinates();
			//test.display_coordinates();
			test.optimalize();
		}
		else
			System.out.println("system nie jest m-diagnozowalny - uruchom program jeszcze raz z innymi danymi");
		
		////////////////////////////////////////////////////////////
		/// Przechodziny do zagadnienia szukania optymalnego systemu. 
		/// Optymalny w tym przypadku oznacza taki, dla którego najmniej jest krawêdzi.
		/// Zauwa¿amy, ¿e warunek konieczny mówi, ¿e stopieñ wejœciowy do wêz³a powinien byæ >=m
		/// Dlatego nasze przeszukanie i optymalizacje ograniczymy do usuwania 1 
		/// tylko z kolumn, które maj¹ wiêcej ni¿ m jedynek.
		/////////////////////////////////////////////////////////////
	}
}
