#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <cstring>
class Numero;
class Tarjeta;
using namespace std;
//////////////////////////////////CLAVE/////////////////////////////////
class Clave {
public:
    enum Razon {CORTA,ERROR_CRYPT};
    Clave(const char* pass);
    const Cadena& clave() const {return password;}
    bool verifica (const char* pass) const;
    class Incorrecta{
      public:
        Incorrecta(Razon a):r(a){}
        Razon razon() const {return r;}
      private:
        Razon r;
    };
private:
  Cadena password;

};

/////////////////////////////////USUARIO/////////////////////////////////////
class Usuario {

  public:

    typedef map <Numero, Tarjeta*> Tarjetas;
    typedef unordered_set<Cadena> Usuarios;
    typedef unordered_map <Articulo*,unsigned > Articulos;

    class Id_duplicado {//
    public:
      Id_duplicado(const Cadena& id): id_duplicado(id){}
      Cadena idd() const {return id_duplicado;}
    private:
      Cadena id_duplicado;
    };

    Usuario(const Cadena& i, const Cadena& no, const Cadena& ap, const Cadena& dir, const Clave& pass);//
    Usuario(const Usuario& u) = delete; //Copia borrada
    Usuario& operator=(const Usuario&) = delete;
    //Metodos observadores:
    Cadena id() const {return ident;}
    Cadena nombre() const {return nom;}
    Cadena apellidos() const {return apell;}
    Cadena direccion() const {return dir_usuario;}

    size_t n_articulos() const {return articulos_.size();}


    const Tarjetas& tarjetas() const {return tarjetas_;}
    const Articulos& compra() const {return articulos_;}

    friend ostream& operator << (ostream& os,const Usuario& user);

    //Asociacion con la clase Tarjeta:
    void es_titular_de( Tarjeta& t);
    void no_es_titular_de( Tarjeta& t);
    void compra (Articulo& a,unsigned cant);

    ~Usuario();

  private://

    Cadena ident,nom,apell,dir_usuario;
    Clave password;
    Tarjetas tarjetas_;
    Articulos articulos_;
    static Usuarios usuarios_;

};

ostream& mostrar_carro (ostream& os, Usuario& u);


#endif
