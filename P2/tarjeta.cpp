#include "tarjeta.hpp"


Numero::Numero (Cadena n)
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


Tarjeta::Tarjeta(Tipo tip, Numero num, Usuario u, Fecha f)
{
  
}
