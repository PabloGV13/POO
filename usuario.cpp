#include "usuario.hpp"
extern "C"{
  #include <unistd.h>
}
#include <random>
#include <iomanip>


Clave::Clave(const char* pass)
{

  if (std::strlen(pass) < 5){throw Incorrecta(CORTA);}

  static const char *const s_char = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
  static const std::size_t longtd = sizeof(s_char) - 1;

  static std::random_device r;
  static std::uniform_int_distribution<size_t> distrib(0,longtd -1);

  const char salt[] = {s_char[distrib(r)], s_char[distrib(r)]};

  char* pcc = crypt(pass,salt);

  if (pcc == nullptr){throw Incorrecta(ERROR_CRYPT);}
  password = pcc;
}

bool Clave::verifica (const char* pass) const
{
  if(const char* const pcc = crypt(pass,password.c_str()))
  {
    return password == pcc;
  }
  throw Incorrecta(ERROR_CRYPT);
}

Usuario::Usuarios Usuario::usuarios_;

Usuario::Usuario (const Cadena& i, const Cadena& no, const Cadena& ap, const Cadena& dir, const Clave& pass)
:ident(i),nom(no),apell(ap),dir_usuario(dir), password(pass)
{
  auto id = usuarios_.insert(i);
  if (!id.second)
  {
    throw Id_duplicado(i);
  }

}

void Usuario::es_titular_de( Tarjeta& t)
{
  if(this == t.titular())
  {
    tarjetas_.insert(make_pair(t.numero(),&t));
  }
}
void Usuario::no_es_titular_de(Tarjeta& t)
{
  t.anula_titular();
  tarjetas_.erase(t.numero());
}

Usuario::~Usuario()
{
  auto i = this->tarjetas_.begin();
  while (i !=this->tarjetas_.end())
  {
    i->second->anula_titular();
    i++;
  }
  usuarios_.erase(ident);
}

void Usuario::compra (Articulo& a,unsigned cant)
{
  if(cant == 0)
  {
    articulos_.erase(&a);
  }
  else {
    articulos_[&a] = cant;
  }
}

ostream& operator << (ostream& os,const Usuario& user)
{
  os << user.ident << "[" << user.password.clave().c_str() << "]" << user.nom << user.apell
  << endl << user.dir_usuario << endl << "Tarjetas:"<< endl;
  auto i = user.tarjetas().begin();
  while (i != user.tarjetas().end())
  {
    os << *i->second << endl;
    i++;
  }
  return os;
}

ostream& mostrar_carro (ostream& os, Usuario& u)
{
  os << "Carrito de compra de " << u.id() << " [Artículos: "
     << u.n_articulos() << "]" << std::endl
     << " Cant. Artículo" << std::endl;
  os << Cadena(70,'=') << std::endl;
    for (auto const& i : u.compra())
        {
           os << std::setw(4) << i.second << "   "
              << (*i.first);
        }
return os;
}
