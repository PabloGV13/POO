#include "usuario.hpp"
extern "C"{
  #include <unistd.h>
}
#include <random>
#include <ctime>
#include <cstring>

Clave::Clave(const char* pass)
{

  if (std::strlen(pass) < 5){throw Incorrecta(CORTA);}

  static const char *const s_char = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
  static const std::size_t longtd = sizeof(s_char) - 1;
  static std::random_device r;
  static std::uniform_int_distribution<std::size_t> distribucion(0,longtd -1);

  const char* salt = {s_char[distribucion(r)], s_char[distribucion(r)]};

  char* pcc = crypt(pass,salt);

  if (pcc == nullptr){throw Incorrecta(ERROR_CRYPT);}
  password = pcc;
}

bool Clave::verifica (const char* pass)
{
  if(const char* const pcc = crypt(pass,password.c_str()))
  {
    return password == pcc;
  }
  throw Incorrecta(ERROR_CRYPT);
}

Usuario::Usuario (const Cadena& i, const Cadena& no, const Cadena& ap, const Cadena& dir, const Clave& pass)
:ident(i),nom(no),apell(ap),dir(dir_usuario), password(pass)
{
  auto id = Usuarios.insert(i);
  if (!id.second)
  {
    throw Id_duplicado(i);
  }

}

void es_titular_de(const Tarjeta& t)
{
  tarjetas_.insert(t);
}
void no_es_titular_de(const Tarjeta& t)
{
  tarjetas_.erase(t);
}

Usuario::~Usuario()
{

}

void compra (Articulo& a,unsigned cant = 1)
{

}
