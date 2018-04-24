#include "articulo.hpp"

ostream& operator << (ostream& os,const Articulo& art)
{
  os << "[" << art.referencia() << "] \"" << art.titulo() << "," << art.f_publi().anno() << " ." << art.stock() << " €";

   return os;;
}
