import java.util.ArrayList;
import java.util.Collection;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;

import javax.print.attribute.standard.NumberUpSupported;

public class Graph 
{
	public int number_of_vertices;
	public ArrayList<ArrayList<Integer>> adjacency_matrix=new ArrayList<ArrayList<Integer>>();
	public int m;
	ArrayList<ArrayList<Integer>> coordinates=new ArrayList<ArrayList<Integer>>();
	
	public void insert_data()
	{
		   Scanner scanner=new Scanner(System.in);  
		   System.out.println("Wprowadz ilosc wiercholkow ");
		   number_of_vertices=scanner.nextInt();
		   System.out.println("Wprowadz ile-diagnozowalny jest system (m?): ");
		   m=scanner.nextInt();
		   System.out.println("Wprowadz macierz s¹siedztwa");
		   for(int i=0; i<number_of_vertices;i++)
		   {
			   ArrayList<Integer> temp=new ArrayList<Integer>();
			   adjacency_matrix.add(temp);
			   for(int j=0;j<number_of_vertices;j++)
			   {
				   adjacency_matrix.get(i).add(scanner.nextInt());
			   }
		   }
		   System.out.println("Zakonczy³em wprowadzanie danych");
		   scanner.close();
	}
	public void insert_data_2()
	{
		   Scanner scanner=new Scanner(System.in);  
		   System.out.println("Wprowadz ilosc wiercholkow ");
		   number_of_vertices=scanner.nextInt();
		   System.out.println("Wprowadz ile-diagnozowalny jest system (m?): ");
		   m=scanner.nextInt();
		   for(int i=0;i<number_of_vertices;i++)
		   {
			   System.out.println("podaj z iloma wierzcho³kami po³¹czony jest "+(i+1) +"  wierzcho³ek");
			   int number_of_connections=scanner.nextInt();
			   System.out.println("Z którym wierzcho³kiem po³¹czony jest "+(i+1) +"  wierzcho³ek?  Podaj tylko wieksze numery");
			   ArrayList<Integer> list_of_numbers=new ArrayList<Integer>();
			   ArrayList<Integer> temp=new ArrayList<Integer>();
			   adjacency_matrix.add(temp);
			   for(int j=0;j<number_of_connections;j++)
			   {
				   list_of_numbers.add(scanner.nextInt());
			   }
			   for(int k=0;k<number_of_vertices;k++)
			   {
				   if (list_of_numbers.contains(k+1))
				   		{
					   		adjacency_matrix.get(i).add(1);
						}
				   else
				   {
					   adjacency_matrix.get(i).add(0);
				   } 
			   }			   
		   }
		   //na koniec jeszcze uzupe³nienie dolnej
		   for(int n=1;n<number_of_vertices;n++)
		   {
			   for(int p=0;p<=n-1;p++)
			   {
				   System.out.println("n=: "+n+" p=: "+p + " adjacency_matrix.get(p).get(n)=: "+ adjacency_matrix.get(p).get(n));
				   adjacency_matrix.get(n).set(p,adjacency_matrix.get(p).get(n));
			   }
		   }
		   System.out.println("Zakonczy³em wprowadzanie danych");
		   scanner.close();
	}
	public void display_matrix()
	{
		for(int i=0; i<number_of_vertices;i++)
		{
			System.out.println();
			for(int j=0; j<number_of_vertices;j++)
			{
				System.out.print(" "+adjacency_matrix.get(i).get(j));
			}
		}
		System.out.println();
	}
	
	/////////////////////////////////////////////////////////////
	/// logika odnoœnie sprawdzania warunków ////
	/////////////////////////////////////////////////////////////
	
	//warunek konieczny nr 1 - Liczba wierzcho³ków wiêksza ni¿ m+2
	
	public boolean condition_1()
	{
		if(number_of_vertices>=m+2)
		{
			//System.out.println("Warunek pierwszy spe³niony");
			return true;
			
		}
		else
		{
			//System.out.println("Warunek pierwszy nie jest spe³niony");
			return false;
		}
	}
	
	// warunek konieczny nr 2 - dla ka¿dego wierzcho³ka pytamy, 
	// czy stopieñ wejœciowy do tego wierzcho³ka jest >=m;
	
	public boolean condition_2()
	{
		boolean flag=true;
		int sum;
		for(int j=0;j<number_of_vertices;j++)
		{
			sum=0;
			for(int i=0;i<number_of_vertices;i++)
			{
				sum+=adjacency_matrix.get(i).get(j);
			}
			//System.out.println("wartoœæ dla "+j+" kolumny wynosi: "+sum);
			if(sum<m)
			{
				flag=false;
				break;
			}
				
		}
		//System.out.println(flag);
		return flag;
	}
	
	/////////////////////////////////////////////////
	//// logika do condition 3 //////////////////////
	/////////////////////////////////////////////////
	
	
	public ArrayList<Integer> successors(int vertex)
	{
		//System.out.println("successors");
		ArrayList<Integer> ro=new ArrayList<Integer>();
		for(int i=0;i<number_of_vertices;i++)
		{
			if(adjacency_matrix.get(vertex).get(i)==1)
			{
				ro.add(i);
			}
		}
		
		for(int j=0;j<ro.size();j++)
		{
			//System.out.print(" "+ro.get(j)+" ");
		}
		return ro;
	}
	
	public ArrayList<Integer> precessors(int vertex)
	{
		//System.out.println("precessors");
		ArrayList<Integer> ro_minus=new ArrayList<Integer>();
		for(int i=0;i<number_of_vertices;i++)
		{
			if(adjacency_matrix.get(i).get(vertex)==1)
			{
				ro_minus.add(i);
			}
			
		}
		for(int j=0;j<ro_minus.size();j++)
		{
			//System.out.print(" "+ro_minus.get(j)+" ");
		}
		return ro_minus;
	}
	
	public ArrayList<Integer> set_substraction(ArrayList<Integer> a,Integer b)
	{
		if(a.contains(b))
			a.remove(b);
		return a;
	}
	
	public static boolean set_comparison(ArrayList<Integer> list_one,ArrayList<Integer> list_two)
	{
		Collection<Integer> list_one_collection=new ArrayList<Integer>(list_one);
		Collection<Integer> list_two_collection=new ArrayList<Integer>(list_two);
		ArrayList<Integer> list_one_minus_list_two=new ArrayList<Integer>(list_one);
		ArrayList<Integer> list_two_minus_list_one=new ArrayList<Integer>(list_two);
		list_one_minus_list_two.removeAll(list_two_collection);
		list_two_minus_list_one.removeAll(list_one_collection);
		if((list_one_minus_list_two.size()==list_two_minus_list_one.size())&&(list_one_minus_list_two.size()!=0))
		{
			if(list_one_minus_list_two.contains(list_two_minus_list_one.get(0)))
			{
				//System.out.println(false);
				return false;
			}
		}
		else if ((list_one_minus_list_two.size()==list_two_minus_list_one.size())&&(list_one_minus_list_two.size()==0))
		{
			//System.out.println(true);
			return true;
		}
		else
		{
			//System.out.println(false);
			return false;	
		}
		
		//System.out.println(false);
		return false;
	}
	
	public int mi_minus(int a)
	{
		int sum=0;
		for(int i=0;i<number_of_vertices;i++)
		{
			sum+=adjacency_matrix.get(i).get(a);
		}
		//System.out.println("mi_minus");
		return sum;
	}
	
	////////////////////////////////////////////////////////////
	/// sprawdzenie warunku wystarczaj¹cego/////////////////////
	////////////////////////////////////////////////////////////
	
	public boolean condition_3()
	{
		String binary="";
		for (int i=0; i<(int)(Math.pow((double)2,(double)(number_of_vertices))); i++) 
		{
			binary=Integer.toBinaryString(i);
			if(binary.length()<number_of_vertices)
			{
				int tmp=number_of_vertices-binary.length();
				for(int j=0;j<tmp;j++)
				{
					binary="0"+binary;
				}
			}
			int[] table_of_indexes= {0,0};
			int counter=0;
			int index=0;
			for (int k=0;k<number_of_vertices;k++)
			{
				if(binary.charAt(k)=='1')
				{
					counter++;
					table_of_indexes[index]=k;
					index=(index+1)%2;
				}
			}
			if(counter==2)
			{	
				//System.out.println(binary);
				if((mi_minus(table_of_indexes[0])==m)&&(mi_minus(table_of_indexes[1])==m))
				{
					if(set_comparison(set_substraction(precessors(table_of_indexes[0]), table_of_indexes[1]), set_substraction(precessors(table_of_indexes[1]), table_of_indexes[0])))
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	
	public void copy (Graph b)
	{ 
		   b.number_of_vertices=this.number_of_vertices;
		   b.m=this.m;
		   for(int i=0; i<number_of_vertices;i++)
		   {
			   ArrayList<Integer> temp=new ArrayList<Integer>();
			   b.adjacency_matrix.add(temp);
			   for(int j=0;j<number_of_vertices;j++)
			   {
				   b.adjacency_matrix.get(i).add(this.adjacency_matrix.get(i).get(j));
			   }
		   }
	}
	
	public ArrayList<ArrayList<Integer>> coordinates()
	{
		int counter=0;
		for(int i=0; i<number_of_vertices;i++)
		   {
				if(mi_minus(i)>m)
				{
					for(int j=0;j<number_of_vertices;j++)
					{
						if(adjacency_matrix.get(j).get(i)==1)
						{
							ArrayList<Integer> temp=new ArrayList<Integer>();
							coordinates.add(temp);
							coordinates.get(counter).add(counter);
							coordinates.get(counter).add(j);
							coordinates.get(counter).add(i);
							counter++;
						}
					}
				}
		   }
		//System.out.println("rozmiar coordinates:  "+coordinates.size());
		return coordinates;
	}
	
	public void display_coordinates()
	{
		//System.out.println("Coordinates size "+coordinates.size());
		for(int k=0;k<coordinates.size();k++)
		{
			System.out.println("");
			for(int l=0;l<3;l++)
			{
				System.out.print(coordinates.get(k).get(l));
			}
		}
	}
	
	public int sum_ones(String a)
	{
		int counter = 0;
		for(int i=0;i<a.length();i++)
		{
			if (a.charAt(i)=='1')
			{
				counter++;
			}
		}
		return counter;
	}
	
	public void optimalize() throws InterruptedException
	{
		int number_of_ones=number_of_vertices*number_of_vertices;
		ArrayList<ArrayList<Integer>> adjacency_matrix_2=new ArrayList<ArrayList<Integer>>();
		String binary="";
		int number_of_positions = coordinates.size();
		for (int i=0; i<(int)(Math.pow((double)2,(double)(number_of_positions))); i++) 
		{
			binary=Integer.toBinaryString(i);
			if(binary.length()<number_of_positions)
			{
				int tmp=number_of_positions-binary.length();
				for(int j=0;j<tmp;j++)
				{
					binary="0"+binary;
				}
			}
			//System.out.println(binary);
			for(int k=0;k<number_of_positions;k++)
			{
				if(binary.charAt(k)=='1')
				{
					adjacency_matrix.get(coordinates.get(k).get(1)).set(coordinates.get(k).get(2),1);
				}
				else
				{
					adjacency_matrix.get(coordinates.get(k).get(1)).set(coordinates.get(k).get(2),0);
				}
			}
			if((condition_1()) && (condition_2()) && (condition_3()))
			{
				//display_matrix();
				//System.out.println("liczba jedynek= "+sum_ones(binary));
				if(sum_ones(binary)<=number_of_ones)
				{
					System.out.println(binary);
					display_matrix();
					System.out.println("liczba jedynek= "+sum_ones(binary));
					number_of_ones=sum_ones(binary);
					adjacency_matrix_2=adjacency_matrix;
				}
			}
			//TimeUnit.SECONDS.sleep(3);
		}
		/*
		for(int i=0; i<number_of_vertices;i++)
		{
			System.out.println();
			for(int j=0; j<number_of_vertices;j++)
			{
				System.out.print(" "+adjacency_matrix_2.get(i).get(j));
			}
		}
		System.out.println();*/
	}
	
}
