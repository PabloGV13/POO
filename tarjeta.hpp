#ifndef TARJETA_H
#define TARJETA_H
#include <iostream>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include <cstring>

using namespace std;
class Numero {

  public:

    enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
    Numero(Cadena n);
    friend bool operator < (const Numero& n1, const Numero& n2);
    operator const char*() {return num.c_str();}

    class Incorrecto{
      public:
        Incorrecto(Razon raz): r(raz){}
        Razon razon() const {return r;}
      private:
        Razon r;
    };
  private:
    Cadena num;

};


class Usuario;

class Tarjeta {
  public:
    enum Tipo {VISA, Mastercard, Maestro, JCB, AmericanExpress};
    class Caducada {
      public:
        Caducada(const Fecha& cad): caducada(cad){}
        Fecha cuando() const {return caducada;}
      private:
        Fecha caducada;
    };

    Tarjeta(Tipo tip, const Numero& num, Usuario& u,const Fecha& f);

    Tarjeta(const Tarjeta& t) = delete;
    Tarjeta& operator = (const Tarjeta&) = delete;


    Tipo tipo() const {return t;}
    Numero numero() const {return n;}
     const Usuario* titular() const{ return tit;}
    Fecha caducidad() const {return cad;}
    Cadena titular_facial() const {return n_completo;}

    void anula_titular() {tit = nullptr;}

    ~Tarjeta();
  private:
    Tipo t;
    Numero n;
    const Usuario* tit;
    Fecha cad;
    Cadena n_completo;


};

bool operator < (const Tarjeta& t1, const Tarjeta& t2);
ostream& operator << (ostream& os, Tarjeta::Tipo& tip);
ostream& operator << (ostream& os, Tarjeta& t);


#endif
