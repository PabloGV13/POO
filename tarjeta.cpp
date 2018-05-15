#include "tarjeta.hpp"
#include <algorithm>
#include <cctype>
#include <iomanip>

#define REMOVE remove_if(num.begin(),num.end(),[](unsigned char x){return isspace(x);})
#define COUNT count_if(num.begin(),num.end(),static_cast<int(*)(int)>(isdigit))


bool luhn(const Cadena& numero);

Numero::Numero (Cadena n)
{
  if (n.length() == 0) throw Incorrecto(Razon::LONGITUD);
  n = n.substr(0,REMOVE - n.begin());
  if(COUNT != n.length()) throw Incorrecto(Razon::DIGITOS);
  if(n.length()< 13 || n.length() > 19) throw Incorrecto(Razon::LONGITUD);
  if(!luhn(n))throw Incorrecto(Razon::NO_VALIDO);
  num = n;
}

Tarjeta::Tarjeta(Tipo tip,const Numero& num, Usuario& u,const Fecha& f):
t(tip), n(num), tit(&u), cad(f), n_completo(u.nombre()+" "+u.apellidos())
{
  Fecha actual;
  if (actual > cad) throw Caducada(cad);
  u.es_titular_de(*this);
}

Tarjeta::~Tarjeta()
{
  if(Usuario* u = const_cast<Usuario*>(tit))
      u->no_es_titular_de(*this);
}

bool operator < (const Tarjeta& t1, const Tarjeta& t2)
{
  return (t1.numero() < t2.numero());
}

ostream& operator << (ostream& os, Tarjeta::Tipo& tip)
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

ostream& operator << (ostream& os, Tarjeta& t)
{
  os<<t.tipo()<<endl;
  os<<t.numero()<<endl;
  os<<t.titular_facial()<<endl;
  os<< "Caduca: "<< setfill('0') << setw(2) << t.caducidad().mes() << '/' << setw(2) << (t.caducidad().anno() % 100);
  return os;
}
