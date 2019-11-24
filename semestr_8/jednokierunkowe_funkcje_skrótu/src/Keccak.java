import java.util.ArrayList;
import java.util.Random;

public class Keccak 
{
	public int[][][] state = new int[5][5][64];
	public int[][][] tmp =new int[5][5][64];
	public int[] BC0={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
	public int[] BC1= {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 ,0,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,0,0, 0,0,0,0, 1,0,0,0, 0,0,1,0};
	public int[] BC2= {1,0,0,0,0,0,0,0, 0,0,0,0, 0,0,0,0 ,0,0,0,0, 0,0,0,0 ,0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,0,0, 0,0,0,0, 1,0,0,0,1,0,1,0};

	
	public void fill_state()
	{
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{
					state[i][j][k]=1;//k*j*i+i;
				}
			}
		}
	}
	
	public void fill_state_init()
	{
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{
					state[i][j][k]=Math.floorMod(i+j+k,2);
				}
			}
		}
		state[3][4][60]=1;
		state[3][4][61]=0;
		state[3][4][62]=0;
		state[3][4][63]=1;
	}
	
	public void show_slice(int a)
	{
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				System.out.print(" "+state[4-i][j][a]);
			}
			System.out.println("");
		}
	}
	
	public void show_slice_tmp(int a)
	{
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				System.out.print(" "+tmp[4-i][j][a]);
			}
			System.out.println("");
		}
	}
	
	public void copy_to_tmp()
	{
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{
					tmp[i][j][k]=state[i][j][k];
				}
			}
		}
	}
	

	public void copy_to_state()
	{
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{
					state[i][j][k]=tmp[i][j][k];
				}
			}
		}
	}
	public void teta()
	{
		int[][] sum = new int[5][64];
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<64;j++)
			{
				sum[i][j]=0;
			}
		}
		for(int j=0;j<5;j++)
		{
			for (int k=0;k<64;k++)
			{
				for(int i=0;i<5;i++)
				{
					sum[j][k]=sum[j][k]^state[i][j][k];
				}
			}
		}
		
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{
					tmp[i][j][k]=state[i][j][k]^sum[Math.floorMod(j-1,5)][k]^sum[Math.floorMod(j-1,5)][Math.floorMod(k-1,5)];
				}
			}
		}
		
		copy_to_state();
	}
	
	public void ro()
	{
		copy_to_tmp();
		int[][] rotation = new int[][]{
			  { 153, 231, 3, 10, 171},
			  { 55, 276, 36, 300, 6},
			  { 28, 91, 0, 1, 190},
			  { 120, 78, 210, 66, 253},
			  { 21, 136, 105, 45, 15}};		
		
		copy_to_tmp();
		//rotacja
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{				
				state[4-i][j][k]=tmp[4-i][j][Math.floorMod(k-rotation[i][j],64)];
				}
			}
		}
	}
	
	public void pi()
	{
		copy_to_tmp();
		for(int k=0;k<64;k++)
		{
			state[2][0][k]=tmp[0][0][k];
			state[4][0][k]=tmp[0][1][k];
			state[1][0][k]=tmp[0][2][k];
			state[3][0][k]=tmp[0][3][k];
			state[0][0][k]=tmp[0][4][k];
			state[0][1][k]=tmp[1][0][k];
			state[2][1][k]=tmp[1][1][k];
			state[4][1][k]=tmp[1][2][k];
			state[1][1][k]=tmp[1][3][k];
			state[3][1][k]=tmp[1][4][k];
			state[3][2][k]=tmp[2][0][k];
			state[0][2][k]=tmp[2][1][k];
			state[2][2][k]=tmp[2][2][k];
			state[4][2][k]=tmp[2][3][k];
			state[1][2][k]=tmp[2][4][k];
			state[1][3][k]=tmp[3][0][k];
			state[3][3][k]=tmp[3][1][k];
			state[0][3][k]=tmp[3][2][k];
			state[2][3][k]=tmp[3][3][k];
			state[4][3][k]=tmp[3][4][k];
			state[4][4][k]=tmp[4][0][k];
			state[1][4][k]=tmp[4][1][k];
			state[3][4][k]=tmp[4][2][k];
			state[0][4][k]=tmp[4][3][k];
			state[2][4][k]=tmp[4][4][k];
		}
	}
	
	public void chi_keccak()
	{
		copy_to_tmp();
		for(int k=0;k<64;k++)
		{
			for(int i=0;i<5;i++)
			{
				for(int j=0;j<5;j++)
				{
					state[i][j][k]=tmp[i][j][k]^((tmp[i][Math.floorMod(j+1,5)][k]^1)&(tmp[i][Math.floorMod(j+2,5)][k]));
				}
			}
		}
	}
	
	public void tau(int []tab)
	{
		for(int k=0;k<64;k++)
		{
			state[0][0][k]=state[0][0][k]^tab[k];
		}
	}
	
	public void copy(Keccak a)
	{
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{
					this.state[i][j][k]=a.state[i][j][k];
				}
			}
		}
	}
	
	
	public void invert_chi_tau(int []tab)
	{
		int[][][] tmp_2 =new int[5][5][64];
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{
					tmp_2[i][j][k]=state[i][j][k];
				}
			}
		}
		
		for(int k=0;k<64;k++)
		{
			tmp_2[0][0][k]=state[0][0][k]^tab[k];
		}
		
		for(int k=0;k<64;k++)
		{
			for(int i=0;i<5;i++)
			{
				for(int j=0;j<5;j++)
				{
					tmp[i][j][k]=state[i][j][k]^((state[i][Math.floorMod(j+1,5)][k]^1)&((state[i][Math.floorMod(j+2,5)][k])^(((state[i][Math.floorMod(j+3,5)][k]^1)&(state[i][Math.floorMod(j+4,5)][k])))));
				}
			}
		}
	}
	
	public int compare(Keccak a)
	{
		int flag=0;
		for(int i=3;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{
					if(this.state[i][j][k]==a.tmp[i][j][k])
					{
						flag=1;
					}
					else
					{
						flag=0;
						break;
					}
				}
			}
		}
		return flag;
	}
	
	public void generate()
	{
		Random r= new Random();
		// najpierw zerowanie
		for(int i=0;i<5;i++)
		{
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<64;k++)
				{
					state[i][j][k]=0;
				}
			}
		}
		// uzupelnienie bitow
		for (int k=0;k<64;k++)
		{
			state[4][1][k]=r.nextInt((1)+1);
			state[3][1][k]=r.nextInt((1)+1);
			state[4][3][k]=r.nextInt((1)+1);
			state[3][3][k]=r.nextInt((1)+1);
			state[4][4][k]=r.nextInt((1)+1);
		}
		//A[3,1] ma byæ 1
		state[3][3][63]=1;
		int alfa_0=r.nextInt((1)+1);
		int alfa_2=r.nextInt((1)+1);
		
		for (int k=0;k<64;k++)
		{
			state[3][0][k]=state[4][0][k]^alfa_0;
			state[3][2][k]=state[4][2][k]^alfa_2;
		}
		
	}
}
