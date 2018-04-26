#include "tarjeta.hpp"


Numero::Numero (Cadena& n)
{
  Cadena aux;
  int j = 0;

  for (int i = 0; i < n.length(); i++)
  {
    if (n[i] != ' ')
    {
      aux[j] = n[i];
      for (int digit = 0; digit <=9; digit++)
      {
        if ((int)aux[j] != digit)
        {
          throw Incorrecto(DIGITOS);
        }
      }
      j++;
    }
  }

  if (aux.length()<13 || aux.length() > 19)
  {
    throw Incorrecto(LONGITUD);
  }

  if (!luhn(aux))
  {
    throw Incorrecto(NO_VALIDO);
  }
}

bool operator < (const Numero& n1, const Numero& n2)
{
  return (n1.num < n2.num);
}

Tarjeta::Tarjeta(Tipo tip, Numero num, Usuario u, Fecha f): t(tip), n(num), tit(&u), f_(f)
{
  Fecha actual;
  if (actual > f_) throw Caducada(f);
}
