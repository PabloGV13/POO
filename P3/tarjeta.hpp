#ifndef TARJETA_H
#define TARJETA_H
#include <iostream>
#include <cstring>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include <cctype>

class Numero {

  public:

    enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
    Numero(Cadena n);
    operator const char*() const{return num.c_str();}
    friend bool operator < (const Numero& n1, const Numero& n2);

    struct EsDigito: public std::unary_function<char ,bool>
    {
      bool operator()(const unsigned char c) const {return std::isdigit(c);}
    };

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
std::ostream& operator << (std::ostream& os,const Tarjeta::Tipo& tip);
std::ostream& operator << (std::ostream& os,const Tarjeta& t);


#endif
