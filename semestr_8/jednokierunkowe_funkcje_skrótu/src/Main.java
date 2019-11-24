import java.util.Random;

public class Main 
{

	public static void main(String[] args) 
	{
		Keccak keccak=new Keccak();
		///////////////// wykonuj� dwie rundy keccaka aby dla zadanych bit�w otrzyma� jak�kolwiek wiadomosc. 
		//Zastrzenia:
		//1 ostatni bit A[3,1] w lane ma by� 1 (wynika to z paddingu)
		keccak.fill_state_init();
		keccak.show_slice(1);
		System.out.println("");
		////// wykonuj� 2 funkcje rundy �eby uzyska� ci�g znak�w do badania
		/////////////////////////////////////////////////////////////////////
		keccak.teta();
		keccak.ro();
		keccak.pi();
		keccak.chi_keccak();
		keccak.tau(keccak.BC0);
		// 2-a runda
		keccak.teta();
		keccak.ro();
		keccak.pi();
		keccak.chi_keccak();
		keccak.tau(keccak.BC1);
		//////////////////////////////////////////////////////////////////////
		keccak.show_slice(1);
		System.out.println("");
		//Mam teraz ci�g wyj�ciowy, mog� si� zaj�� liczeniem z rozdzia�u 6.1
		Keccak result=new Keccak();
		result.copy(keccak);
		////////////////////////////////////////////////////////////////////
		//Przechodze do ataku
		///////////////////////////////////////////////////////////////////
		//odwr�cenie 320 bit�w wyniku
		result.show_slice(0);
		
		result.invert_chi_tau(result.BC1);
		System.out.println();
		result.show_slice_tmp(0);
		// Mam ju� odwr�cone wszystko w result.tmp, teraz przechodze do kroku drugiego

		Keccak test=new Keccak();
		do
		{
			//System.out.println("jeszcze nie znalaz�em");
			test.generate();
			test.teta();
			test.ro();
			test.pi();
			test.chi_keccak();
			test.tau(test.BC0);
			test.teta();
			test.ro();
			test.pi();
		}
		while(test.compare(result)==0);
		
		
	}

}
