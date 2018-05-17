#ifndef USUARIO_PEDIDO
#define USUARIO_PEDIDO
#include <set>
#include "pedido.hpp"
#include "usuario.hpp"



class Usuario_Pedido {
  public:
    typedef std::set<Pedido*> Pedidos;
    void asocia(Usuario& u, Pedido& pe)
    {
      usuario_pedidos_[&u].insert(&pe);
      pedido_usuario_[&pe] = &u;
    }

    void asocia(Pedido& pe, Usuario& u)
    {
      asocia(u,pe);
    }

    Pedidos pedidos(Usuario& u)
    {
      return usuario_pedidos_[&u];
    }

    Usuario* cliente(Pedido& pe)
    {
      return pedido_usuario_[&pe];
    }
  private:
    std::map<Usuario*, Pedidos> usuario_pedidos_;
	  std::map<Pedido*, Usuario*> pedido_usuario_;
};

#endif
