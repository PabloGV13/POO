#ifndef CLAVE_H
#define CLAVE_H
#include <iostream>
#include <../P1/fecha.hpp>
#include <../P1/cadena.hpp>
#include <unistd.h>

class Clave {
public:
    enum Razon {CORTA,ERROR_CRYPT};
    class Incorrecta{
      public:

        Incorrecta(Razon a);
        Razon razon() const {return r;}
      private:
        Razon r;
    };
  Clave(const char* pass);
  Cadena clave() const {return password;}
  bool verifica (const char* pass);

private:
  Cadena password;

};






#endif
