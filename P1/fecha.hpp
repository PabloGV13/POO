#ifndef FECHA_H
#define FECHA_H
#include <iostream>
#include <cstring>
#include <ctime>
#include <stdexcept>
#include <cstdio>


using namespace std;

class Fecha
{

public:

	 	class Invalida
	  	{
	  		public:
	  			explicit Invalida(const char* error):e(error){};
	  			const char* por_que() const{return e;};
				private:
					const char* e;
	 	};


		static const int AnnoMinimo = 1902;
		static const int AnnoMaximo = 2037;

    explicit Fecha (int dia = 0, int mes = 0, int anno = 0);
    Fecha (const char* cad);
  	//Fecha (const Fecha& f);
  	//Fecha(const Fecha& f):d(f.d),m(f.m),a(f.a){};
		const char* cadena() const;

  	Fecha operator + (int dia) const ;
  	Fecha operator - (int dia) const ;
  	Fecha& operator += (int dia);
  	Fecha& operator -= (int dia) ;
  	Fecha& operator ++ () ;
  	Fecha& operator -- () ;
  	Fecha operator ++ (int ) ;
  	Fecha operator -- (int );


    int dia() const noexcept{
      return d;
    }
    int mes() const noexcept{
      return m;
    }
    int anno() const noexcept{
      return a;
    }
  	//operator const char*() const;



	private:

  		int d;
  		int m;
  		int a;

			void comprobaciones () const;
};

	ostream& operator << (ostream& o,const Fecha& f);
	istream& operator >> (istream& i, Fecha& f);

	bool operator != (const Fecha&, const Fecha&) noexcept;
  bool operator > (const Fecha&, const Fecha& ) noexcept;
  bool operator >= (const Fecha&, const Fecha& ) noexcept;
  bool operator < (const Fecha&, const Fecha& ) noexcept;
  bool operator <= (const Fecha&, const Fecha& ) noexcept;
  bool operator == (const Fecha&, const Fecha& ) noexcept;

#endif
