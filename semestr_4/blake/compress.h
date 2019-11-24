#ifndef COMPRESS_H_
#define COMPRESS_H_

class Compress 
{
	void wypiszhi1(unsigned int hi1[]);
	void wypisz_v (unsigned int v[][4]);
	void init( unsigned int v[][4],unsigned int t[], unsigned int* hi);
	void funkcjaG(int i, unsigned int v[][4], unsigned int m[], int r) ;
	void finalisation(unsigned int v[][4] ,unsigned int hi[], unsigned int hi1[]);

	public:
		unsigned int * compress( unsigned int m[], unsigned int *hi, unsigned int *t);
};


#endif 
