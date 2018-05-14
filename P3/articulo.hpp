
#ifndef ARTICULO_H
#define ARTICULO_H
#include <iostream>
#include <cstring>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
using namespace std;
class Articulo {

public:

  explicit Articulo(const Cadena& r,const Cadena& tit,const Fecha& fe, double pr, unsigned s):
  f(fe),cod_refer(r),t(tit),p(pr),num_ejemplares(s){}

  Fecha f_publi() const {return f;}
  Cadena referencia()const {return cod_refer;}
  Cadena titulo() const {return t;}
  double precio() const {return p;}
  unsigned stock() const {return num_ejemplares;}
  double& precio()  {return p;}
  unsigned& stock() {return num_ejemplares;}


private:
    Fecha f;
    Cadena cod_refer;
    Cadena t;
    double p;
    unsigned num_ejemplares;

};

ostream& operator << (ostream& os,const Articulo& art);

#endif
