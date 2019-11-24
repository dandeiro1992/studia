import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class Main extends JFrame implements ActionListener
{

	

    JTextField tf1,tf2,tf3,tf4,tf5,tf6;
    JButton b1; 
    JCheckBox checkbox1, checkbox2;
    static JFrame f;
    volatile static boolean Go;
    volatile static boolean Greedy;
    volatile static boolean Exh;
    volatile static int a;
	volatile static int b;
	volatile static int c;
	volatile static int d;
	volatile static int g;
	volatile static int h;

    
    public Main()
    {
        
        Go=false;
        checkbox1 = new JCheckBox("Algorytm Heurystyczny");    
        checkbox1.setBounds(60,5, 180,20);
        checkbox2 = new JCheckBox("Algorytm Dokladny");    
        checkbox2.setBounds(60,30, 180,20);
        
        JLabel lab1=new JLabel("Liczba elementow");
        lab1.setBounds(30,70,120,20);
        JLabel lab2=new JLabel("Liczba zbiorow");
        lab2.setBounds(30,100,120,20);
        JLabel lab3=new JLabel("Liczba iteracji");
        lab3.setBounds(30,130,120,20);
        JLabel lab4=new JLabel("Liczba powtorzen");
        lab4.setBounds(30,160,120,20);
        
        JLabel lab5=new JLabel("Inkrementowane o");
        lab5.setBounds(220,70,130,20);
        JLabel lab6=new JLabel("Inkrementowane o");
        lab6.setBounds(220,100,130,20);

        
        f= new JFrame("Pokrycie zbioru");
        tf1=new JTextField("10");  
        tf1.setBounds(150,70,50,20);  
        tf2=new JTextField("5");  
        tf2.setBounds(150,100,50,20);  
        tf3=new JTextField("9");  
        tf3.setBounds(150,130,50,20);  
        tf4=new JTextField("7");  
        tf4.setBounds(150,160,50,20);     
        
        tf5=new JTextField("10");  
        tf5.setBounds(350,70,50,20);  
        tf6=new JTextField("1");  
        tf6.setBounds(350,100,50,20); 
        
        b1=new JButton("Uruchom");  
        b1.setBounds(90,200,100,50);    
        b1.addActionListener(this);    
        f.add(tf1);f.add(tf2);f.add(tf3);f.add(tf4);f.add(tf5);f.add(tf6);
        f.add(b1);  
        f.add(checkbox1); f.add(checkbox2);
        f.add(lab1); f.add(lab2); f.add(lab3); f.add(lab4); f.add(lab5); f.add(lab6);
        f.setSize(600,300);  
        f.setLayout(null);  
        f.setVisible(true);  

        
        

    }
	
	public void actionPerformed(ActionEvent e)
    {
	
		 if(checkbox1.isSelected()){
			 Greedy=true;
		 }
		 if(checkbox2.isSelected()){
			 Exh=true;
		 }
		 
		 
		 
		 String s1=tf1.getText();  
	     String s2=tf2.getText();
	     String s3=tf3.getText();  
	     String s4=tf4.getText();
	     String s5=tf5.getText();  
	     String s6=tf6.getText();
	     a=Integer.parseInt(s1);  
	     b=Integer.parseInt(s2);
	     c=Integer.parseInt(s3);  
	     d=Integer.parseInt(s4);
	     g=Integer.parseInt(s5);  
	     h=Integer.parseInt(s6);
		 
		 
		 
		 
		 if(e.getSource()==b1){
			 Go=true;
			 
		 }
		 

	             
	       
		 

		
	     
    }
	
	
	
	
	public static void main(String[] args) 
	{
	

		new Main();
	
		while(!Main.Go || (!Main.Greedy && !Main.Exh)) {
			
		}
		
		Main.f.dispose();
		
		System.out.println("Szukam pokrycia");
		Generator testing=new Generator(Main.a,Main.b,Main.c,Main.d,Main.g,Main.h, Main.Greedy, Main.Exh);

		testing.test();


	}

}
