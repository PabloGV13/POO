#include "pedido-articulo.hpp"


//LineaPedido
std::ostream& operator << (std::ostream& os, const LineaPedido& lin_ped)
{
  os << std::fixed << std::setprecision(2) << lin_ped.precio_venta() << " €\t" << lin_ped.cantidad();
  return os;
}


//Pedido_Articulo
void Pedido_Articulo::pedir(Pedido& pe, Articulo& art, double precio, unsigned q)
{
  pedido_articulo_[&pe].insert(std::make_pair(&art,LineaPedido(precio,q)));
  articulo_pedido_[&art].insert(std::make_pair(&pe,LineaPedido(precio,q)));
}

void Pedido_Articulo::pedir(Articulo& art,Pedido& pe, double precio, unsigned q)
{
  pedir(pe, art,precio,q);
}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& pe)
{
  return pedido_articulo_[&pe];
}
Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& art)
{
  return articulo_pedido_[&art];
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
  double total = 0.0;
  for (auto iter: pedido_articulo_)
  {
    os << "Pedido núm. " << iter.first->numero() << std::endl
    << "Cliente: " << iter.first->tarjeta()->titular()->nombre() << "\t"
    << "Fecha: " << iter.first->fecha() << std::endl
    << iter.second << std::endl;
    total+=iter.first->total();
  }
  os<<std::endl << "TOTAL VENTAS\t" << std::fixed << std::setprecision(2) << total << " €" <<
  std::endl << std::endl;
  return os;
}
std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
  for(auto iter : articulo_pedido_)
  {
    os<<"Ventas de "<<"["<<iter.first->referencia()<<"] "<<"\""
    <<iter.first->titulo()<<"\""
    <<iter.second;
  }
  return os;
}

std::ostream& operator << (std::ostream& os,const Pedido_Articulo::ItemsPedido& items_pedidos)
{
  double total=0.0;
  os<<"  PVP       Cantidad        Artículo"<<std::endl
  <<"================================================="<<std::endl;
  for(auto iter : items_pedidos)
  {
    os << iter.second << "           " << "[" << iter.first->referencia()
    << "] " << "\"" << iter.first->titulo() << "\"" << std::endl;
    total=total+iter.second.cantidad()*iter.second.precio_venta();
  }
  os<<"================================================="<<std::endl;
  os<<"    Total"<<"  "<<std::setprecision(2)<<total<<" €"<<std::endl;

  return os;
}
std::ostream& operator << (std::ostream& os,const Pedido_Articulo::Pedidos& pedidos_)
{
  double total = 0.0;
  int cont = 0;
  os << "[Pedidos: " << pedidos_.size() << "]" << std::endl
    << "==================================================================" << std::endl
    << " PVP\tCantidad\tFecha de venta" << std::endl
    << "==================================================================" << std::endl;
    for(auto iter = pedidos_.begin(); iter!= pedidos_.end(); iter++)//Recorre el map
    {
      os << iter->second << "\t\t"<<iter->first->fecha() << std::endl;
      total += iter->second.cantidad()*iter->second.precio_venta();
      cont += iter->second.cantidad();

    }
    os << "==================================================================" << std::endl
      <<  std::fixed << std::setprecision(2) << total << " €\t\t" << cont << std::endl << std::endl;

    return os;
}
