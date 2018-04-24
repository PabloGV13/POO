#include "clave.hpp"


Clave::Clave(const char* pass)
{
  Cadena a = Cadena(pass);
  if (a.length() < 5){throw Incorrecta(CORTA);}

  char* s_char = "abcdefghijklemnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789./";
  char* salt = nullptr;

  salt[0] = s_char[rand()% 64];
  salt[1] = s_char[rand()% 64];

  password = crypt(pass,salt);
  if (password == NULL){throw Incorrecta(ERROR_CRYPT);}
}

bool Clave::verifica (const char* pass)
{
  Cadena a = Cadena(pass);
  char* salt;
  salt[0] = password[0];
  salt[1] = password[1];
  return (crypt(pass,salt) == password);
}
