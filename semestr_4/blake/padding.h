#ifndef PADDING_H_
#define PADDING_H_

class Padding {
	private:
		
		char* msg0;
		char* msgpad;
		unsigned long long int msgpadsize;//rozmiar padmsg w bitach
		bool dodano_nowy_blok;

	public:
		
		Padding(char* msg0);
		void padmsg();
		void wyswietl();
		char* getmsgpad();
		~Padding();
		unsigned long long int getlen0();
		bool get_dodano_nowy_blok();
};

#endif 
