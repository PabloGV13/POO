#include <cstdio>
#include "fecha.hpp"


using namespace std;

Fecha::Fecha (int dia, int mes, int anno) :d(dia),m(mes),a(anno)
{


	  time_t tiempo_calendario = time(nullptr);
		tm* tiempo_descompuesto = localtime(&tiempo_calendario);

	if(d == 0)
	{
		d = tiempo_descompuesto->tm_mday;
	}
	if(m == 0)
	{
		m = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
	}
	if(a == 0)
	{
		a =  tiempo_descompuesto->tm_year + 1900; // tm_year: a~ nos desde 1900
	}
	comprobaciones();
}

Fecha::Fecha (const char* cad)
{
	time_t tiempo_calendario = std::time(nullptr);
	tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

	//sscan

	if (std::sscanf (cad, "%d/%d/%d",&d,&m,&a) == 3 )
	{
		if(d == 0)
		{
			d = tiempo_descompuesto->tm_mday;
		}
		if(m == 0)
		{
			m = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
		}
		if(a == 0)
		{
			a =  tiempo_descompuesto->tm_year + 1900; // tm_year: a~ nos desde 1900
		}
		comprobaciones();
	}
	else
	{
		throw Invalida("Error");
	}


}

int bisiesto(int a)
{
	return (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0));
}

void Fecha::comprobaciones () const
{
	static const int dia_mes[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};


	if ((d > dia_mes[m] + bisiesto(a) || d < 1))
	{
		throw Invalida("ERROR: El dia no es valido");
	}

	if ((m < 1 || m > 12))
	{
		throw Invalida("ERROR: El mes no es valido");
	}

	if ((a < AnnoMinimo || a > AnnoMaximo))
	{
		throw Invalida("ERROR: El annio no es valido");
	}

}

//Sobrearga operadores aritmeticos

Fecha Fecha::operator + (int dia) const
{

	return Fecha(*this)+= dia;

}

Fecha Fecha::operator - (int dia)const
{
	return Fecha(*this)+= -dia;

}

Fecha Fecha::operator ++ (int )
{
	Fecha t = *this;
	*this += 1;
	return t;

}

Fecha Fecha::operator -- (int )
{

	Fecha t = *this;
	*this += -1;
	return t;

}

Fecha& Fecha::operator ++ ()
{
	return *this += 1;
}

Fecha& Fecha::operator -- ()
{
	return *this += -1;
}


Fecha& Fecha::operator += (int dia)
{
	if (dia!=0)
	{
		tm hoy = {0};

		hoy.tm_mday = this->d + dia;
		hoy.tm_mon = this->m - 1;
		hoy.tm_year = this->a - 1900;

		mktime(&hoy);

		this->d = hoy.tm_mday;
		this->m = hoy.tm_mon + 1;
		this->a = hoy.tm_year + 1900;

		comprobaciones();
	}

	return *this ;
}

Fecha& Fecha::operator -= (int dia)
{
	return *this += -dia;
}
ostream& operator << (ostream& o,const Fecha& f)
{
	o << f.cadena();
	return o;
}

istream& operator >> (istream& is, Fecha& f)
{
	char tmp[11];
  is.getline(tmp,11);
  try{
    f = Fecha(tmp);
  }catch(const Fecha::Invalida& e){
    is.setstate(std::ios_base::failbit);
    throw;
  }
  return is;
}

const char* Fecha::cadena()const
{

	static char B[50];
  std::tm tiempo_descompuesto;
  tiempo_descompuesto={0};
  tiempo_descompuesto.tm_mday=this->d;
  tiempo_descompuesto.tm_mon=this->m-1;
  tiempo_descompuesto.tm_year=this->a-1900;
  std::setlocale(LC_TIME, "es_ES.UTF-8");
  mktime(&tiempo_descompuesto);
  strftime(B,50,"%A %d de %B de %Y",&tiempo_descompuesto);
  return (const char*)B;

}


//Sobrecarga operadores logicos
bool operator > (const Fecha& f1, const Fecha& f2) noexcept
{
  return (f2 < f1);
}

bool operator >= (const Fecha& f1, const Fecha& f2)noexcept
{
  return !(f1 < f2);
}

bool operator < (const Fecha& f1, const Fecha& f2) noexcept
{
	if (f1.anno() < f2.anno())
	{
		return true;
	}
	else if (f1.anno() > f2.anno()){
		return false;
	}
	if (f1.mes() < f2.mes())
	{
		return true;
	}
	else if (f1.mes() > f2.mes())
	{
		return false;
	}
	return f1.dia() < f2.dia();
}

bool operator <= (const Fecha& f1, const Fecha& f2) noexcept
{

	return ((f1 < f2)||(f1 == f2));

}

bool operator == (const Fecha& f1, const Fecha& f2) noexcept
{
	bool b = false;

	if (f1.anno() == f2.anno() && f1.mes() == f2.mes() && f1.dia() == f2.dia())
	{
		b = true;
	}

	return b;
}

bool operator != (const Fecha& f1, const Fecha& f2) noexcept
{
	return !(f1==f2);
}
