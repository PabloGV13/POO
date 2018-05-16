#include "pedido-articulo.hpp"

std::ostream& operator << (std::ostream& os, const LineaPedido& lin_ped)
{
  os << std::fixed << std::setprecision(2) << lin_ped.cantidad() << " €\t";
}

void Pedido_Articulo::pedir(const Pedido& pe, const Articulo& art, double precio, unsigned q)
{
  pedido_articulo_[&pe].insert(std::make_pair(&art,LineaPedido(precio,q)));
  articulo_pedido_[&art].insert(std::make_pair(&pe,LineaPedido(precio,q)));
}
void Pedido_Articulo::pedir(const Articulo& art, const Pedido& pe, double precio, unsigned q)
{
  pedir(pe, art,precio,q);
}
std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream&)
{

}
std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream&)
{

}

std::ostream& operator << (std::ostream& os,const Pedido_Articulo::ItemsPedido& items_pedidos)
{

}
std::ostream& operator << (std::ostream& os,const Pedido_Articulo::Pedidos& pedidos_)
{
  os << "[Pedidos: " << pedidos_.size() << "]" << std::endl
    << "==================================================================" << std::endl
    << " PVP\tCantidad\tFecha de venta" << std::endl
    << "==================================================================" << std::endl;
    for(auto iter: pedidos_)//Recorre el map
    {

    }
}
