#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include "Usuario_pedido.hpp"
#include "Pedido_Articulo.hpp"
#include "../P2/Tarjeta.hpp"
#include "../P1/Fecha.hpp"

class Pedido {
  public:
    Pedido(Usuario_Pedido & usuario_pedidos,Pedido_Articulo& pedido_articulo,Usuario& u, const Tarjeta& t, const Fecha& fp);

  private:
    int num_;
    Tarjeta& tarjeta_;
    Usuario& u;
  }

















};


#endif

//pedido //usuario_pedido.hpp // lineapedido //
