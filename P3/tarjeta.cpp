#include <algorithm>
#include <functional>
#include <iomanip>
#include "tarjeta.hpp"

#define REMOVE std::remove_if(n.begin(),n.end(),[](unsigned char x){return isspace(x);})
#define FIND std::find_if(n.begin(),n.end(),std::not1(EsDigito()))


bool luhn(const Cadena& numero);

Numero::Numero ( Cadena n)
{
  if (n.length() == 0) throw Incorrecto(Razon::LONGITUD);
  n = n.substr(0,REMOVE - n.begin());
  if(FIND != n.end()) throw Incorrecto(Razon::DIGITOS);
  if(n.length()< 13 || n.length() > 19) throw Incorrecto(Razon::LONGITUD);
  if(!luhn(n))throw Incorrecto(Razon::NO_VALIDO);
  num = n;
}


Tarjeta::Tarjeta(Tipo tip,const Numero& num, Usuario& u,const Fecha& f):
t(tip), n(num), tit(&u), cad(f), n_completo(u.nombre()+" "+u.apellidos())
{

  if (Fecha() > cad) throw Caducada(cad);
  u.es_titular_de(*this);
}

Tarjeta::~Tarjeta()
{
  if(Usuario* u = const_cast<Usuario*>(tit))
      u->no_es_titular_de(*this);
}

bool operator < (const Numero& n1,const Numero& n2){return n1.num < n2.num;}

bool operator < (const Tarjeta& t1, const Tarjeta& t2)
{
  return (t1.numero() < t2.numero());
}

std::ostream& operator << (std::ostream& os,const Tarjeta::Tipo& tip)
{
  switch (tip) {
    case Tarjeta::Tipo::VISA:
      os << "VISA";
      break;
		case Tarjeta::Tipo::Mastercard:
      os << "Mastercard";
      break;
		case Tarjeta::Tipo::Maestro:
      os << "Maestro";
      break;
		case Tarjeta::Tipo::JCB:
      os << "JCB";
      break;
		case Tarjeta::Tipo::AmericanExpress:
      os << "AmericanExpress";
      break;
  }
return os;
}

std::ostream& operator << (std::ostream& os,const Tarjeta& t)
{
  os<<t.tipo()<<endl;
  os<<t.numero()<<endl;
  os<<t.titular_facial()<<endl;
  os<< "Caduca: "<< setfill('0') << setw(2) << t.caducidad().mes() << '/' << setw(2) << (t.caducidad().anno() % 100);
  return os;
}
