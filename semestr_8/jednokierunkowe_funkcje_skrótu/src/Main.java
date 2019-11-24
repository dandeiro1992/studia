import java.util.Random;

public class Main 
{

	public static void main(String[] args) 
	{
		Keccak keccak=new Keccak();
		///////////////// wykonujê dwie rundy keccaka aby dla zadanych bitów otrzymaæ jak¹kolwiek wiadomosc. 
		//Zastrzenia:
		//1 ostatni bit A[3,1] w lane ma byæ 1 (wynika to z paddingu)
		keccak.fill_state_init();
		keccak.show_slice(1);
		System.out.println("");
		////// wykonujê 2 funkcje rundy ¿eby uzyskaæ ci¹g znaków do badania
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
		//Mam teraz ci¹g wyjœciowy, mogê siê zaj¹æ liczeniem z rozdzia³u 6.1
		Keccak result=new Keccak();
		result.copy(keccak);
		////////////////////////////////////////////////////////////////////
		//Przechodze do ataku
		///////////////////////////////////////////////////////////////////
		//odwrócenie 320 bitów wyniku
		result.show_slice(0);
		
		result.invert_chi_tau(result.BC1);
		System.out.println();
		result.show_slice_tmp(0);
		// Mam ju¿ odwrócone wszystko w result.tmp, teraz przechodze do kroku drugiego

		Keccak test=new Keccak();
		do
		{
			//System.out.println("jeszcze nie znalaz³em");
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
