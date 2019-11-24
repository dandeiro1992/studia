#ifndef COUNTER_H_
#define COUNTER_H_
class Counter {
	private:
		unsigned long long int len0;
		bool dodano_nowy_blok;
		unsigned long long int* L;
		unsigned long long int ileblokow;
	public:
		Counter(unsigned long long int len0,bool dodano_nowy_blok);
		~Counter();
		// desktruktor fala counter delete [ L]
		unsigned int* operator[] (unsigned long long int indeks);
};

#endif
