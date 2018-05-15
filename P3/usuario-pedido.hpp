#ifndef USUARIO_PEDIDO
#define USUARIO_PEDIDO
#include "pedido.hpp"
#include "usuario.hpp"


class Usuario_Pedido {
  public:
    
  private:
    std::map<Usuario*, Pedidos> usuario_pedidos_;
	  std::map<Pedido*, Usuario*> pedido_usuario_;
};

#endif
