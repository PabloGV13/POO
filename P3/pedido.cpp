#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido & usuario_pedidos,
              Pedido_Articulo& pedido_articulo,
              Usuario& u, const Tarjeta& t, const Fecha& fp)
:num_(N_pedidos + 1), tarjeta_(&t), fecha_(fp), total_(0)
{
  if (u.n_articulos() == 0) //¿Carrito vacio?
  {
    throw Vacio(u);
  }
  if (t.titular() != &u) //Falso hijo de perra
  {
    throw Impostor(u);
  };
  if (t.caducidad() < fp)
  {
    throw Tarjeta::Caducada(t.caducidad());
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

std::ostream& operator <<(std::ostream& os, const Pedido& pe)
{
  os << "Núm. pedido: " << pe.numero() << std::endl
    << "Fecha: " << pe.fecha() << std::endl
    << "Pagado con: " << *pe.tarjeta() << std::endl
    << "Importe: " << std::fixed << std::setprecision(2) << pe.total() << " €";

    return os;
}
