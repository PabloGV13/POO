#ifndef TARJETA_H
#define TARJETA_H
#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"
#include "usuario.hpp"
#include "articulo.hpp"

bool luhn(const Cadena& numero);

class Numero {

  public:
    enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
    class Incorrecto{
      public:
        Incorrecto(Razon raz): r(raz){}
        Razon razon() const {return r;}
      private:
        Razon r;
    };
    Numero(Cadena n);
    operator Cadena() {return num;}
  private:
    Cadena num;

};

bool operator < (const Numero& n1, const Numero& n2);


class Tarjeta {
  public:
    enum Tipo {VISA, Mastercard, Maestro, JCB, AmericanExpress};
    class Caducada {
      public:
        Fecha cuando() const {return caducada;}
      private:
        Fecha caducada;
    };
    ~Tarjeta(){}
    Tarjeta(const Tarjeta& t) = delete;
    Tarjeta(Tipo tip, Numero num, Usuario u, Fecha f);
    Numero numero() const {return n;}
    Fecha caducidad() const {return cad;}
    Cadena titular_facial() const {return n_completo;}
    void anular_titular(Usuario& u) {}
    
  private:
    Tipo t;
    Numero n;
    Usuario* tit;
    Fecha cad;
    Cadena n_completo;

};








#endif
