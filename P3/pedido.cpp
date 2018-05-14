#include "pedido.hpp"
#include "../P1/fecha.hpp"
#include "../P2/tarjeta.hpp"
#include "../P2/articulo.hpp"
#include ""

Pedido::Pedido(Usuario_Pedido & usuario_pedidos,
              Pedido_Articulo& pedido_articulo,
              Usuario& u, const Tarjeta& t, const Fecha& fp)
:num_(N_pedidos + 1), tarjeta_(&t), fecha_(fp), total_(0)
{
  if (u.n_articulo() == 0) //¿Carrito vacio?
  {
    throw Vacio(u);
  }
  if (t.titular() != &u) //Falso hijo de perra
  {
    throw Impostor(u)
  };
  if (t.caducidad() < fp)
  {
    throw Tarjeta::Caducada(t.caducidad())
  };

  for (auto c : u.compra()) //c es pair<Articulo*, unsigned> (cantidad)
  {
    if(c.first->stock() < c.second) //No hay bastante en el armasen
    {
      const_cast<Usuario::Articulos&>(u.compra()) .clear();
      throw SinStock(*c.first); // Le pasamos el primer articulo del que no hay stock
    }
  }
  Usuario::Articulos Carro = u.compra();

  for (auto c : Carro)
  {
    Articulo* pa = c.first;
    unsigned int cantidad = c.second;
    double precio = pa->precio();
    pa->stock() -= cantidad;
    pedido_articulo.pedir(*this, *pa, precio, cantidad);
    total_ += precio * cantidad;
    u.compra(*pa,0);
  }
  usuario_pedidos.asocia(u, *this);
  ++N_pedidos;
}
