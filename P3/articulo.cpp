#include <iomanip>
#include "articulo.hpp"

ostream& operator << (ostream& os,const Articulo& art)
{
  os << "[" << art.referencia() << "] \""
    << art.titulo() << "\", " << art.f_publi().anno()
    << ". " << fixed << setprecision(2)<< art.precio()
    << " €" << endl;

   return os;
}
