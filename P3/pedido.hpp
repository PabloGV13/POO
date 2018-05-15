#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include <iomanip>
#include <iostream>
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido {
  public:
    Pedido(Usuario_Pedido & usuario_pedidos,Pedido_Articulo& pedido_articulo,Usuario& u, const Tarjeta& t, const Fecha& fp);
    int numero() const {return num_;}
    const Tarjeta* tarjeta()const {return tarjeta_;}
    Fecha fecha() const{return fecha_;}
    double total() const{return total_;};
    class Vacio{
      public:
        Vacio(Usuario& u): usuario_(&u){}
        const Usuario& usuario() const {return *usuario_;}
      private:
        Usuario* usuario_;
    };
    class Impostor{
      public:
        Impostor(Usuario& u):usuario_(&u){}
        const Usuario& usuario()const {return *usuario_;}
      private:
        Usuario* usuario_;
    };
    class SinStock{
      public:
        SinStock(Articulo& ar): articulo_(&ar){}
        const Articulo& articulo() const {return *articulo_;}
      public:
        Articulo* articulo_;

    };
  private:
    static int N_pedidos;
    int num_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double total_;
  };

std::ostream& operator <<(std::ostream& os, const Pedido& pe);

#endif

//pedido //usuario_pedido.hpp // lineapedido //
