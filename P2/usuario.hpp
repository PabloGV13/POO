#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <map>
#include <unordered_set>
#include <unordered_map>
class Numero;
class Tarjeta;
using namespace std;

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


class Usuario {

  public:
    typedef map <Numero , Tarjeta*> Tarjetas;
    typedef unordered_map <Articulo*,unsigned int> Articulos;

    class Id_duplicado {
    public:
      Id_duplicado(Cadena id);
      Cadena idd() const {return id_duplicado;}
    private:
      Cadena id_duplicado;

    };
    ~Usuario();
    Usuario(const Cadena& i, const Cadena& no, const Cadena& ap, const Cadena& dir, const Clave& pass);
    Usuario(const Usuario& u) = delete;
    Cadena id() const {return ident;}
    Cadena nombre() const {return nom;}
    Cadena apellidos() const {return dir_usuario;}

    const Tarjetas& tarjetas() const;

    void es_titular_de(const Tarjeta& t);
    void no_es_titular_de(const Tarjeta& t);
    void compra (Articulo& a,unsigned cant = 1);

    const Articulos& compra() const;
    size_t n_articulos() const;

  private:
    static std::unordered_set<Cadena> Usuarios;
    Cadena ident,nom,apell,dir_usuario;
    Clave password;
    Tarjetas tarjetas_;
    Articulos articulos_;

};




#endif
