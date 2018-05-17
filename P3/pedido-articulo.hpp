#ifndef PEDIDO_ARTICULO
#define PEDIDO_ARTICULO
#include "articulo.hpp"
#include "pedido.hpp"

/////////////////////////////////////////CALSE LineaPedido //////////////////////////////////////////////////
class LineaPedido{
  public:
    explicit LineaPedido(double p_venta, unsigned q = 1): precio_venta_(p_venta),cantidad_(q){}
    double precio_venta() const {return precio_venta_;}
    unsigned cantidad() const {return cantidad_;}
  private:
    double precio_venta_;
    unsigned cantidad_;
};

std::ostream& operator << (std::ostream& os, const LineaPedido& lin_ped);

/////////////////////////////////////////CALSE Pedido_Articulo //////////////////////////////////////////////////
class OrdenaArticulos:std::binary_function <Articulo*,Articulo*,bool>
{
  public:
    bool operator() (Articulo* art1, Articulo* art2) const {return art1->referencia() < art2->referencia();}
};


class OrdenaPedidos:std::binary_function <Pedido*,Pedido*,bool>
{
  public:
    bool operator() (Pedido* pe1, Pedido* pe2) const {return pe1->numero() < pe2->numero();}
};

class Pedido_Articulo{
  public:
    void pedir(Pedido& pe, Articulo& art, double precio, unsigned q = 1);
    void pedir(Articulo& art, Pedido& pe, double precio, unsigned q = 1);
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    ItemsPedido& detalle(Pedido& pe);
    Pedidos& ventas(Articulo& art); //&?
    std::ostream& mostrarDetallePedidos(std::ostream&);
    std::ostream& mostrarVentasArticulos(std::ostream&);

  private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> pedido_articulo_;
    std::map<Articulo*, Pedidos, OrdenaArticulos> articulo_pedido_;
};

std::ostream& operator << (std::ostream& os,const Pedido_Articulo::ItemsPedido& items_pedidos);
std::ostream& operator << (std::ostream& os,const Pedido_Articulo::Pedidos& pedidos_);



#endif
