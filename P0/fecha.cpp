#include <cstdio>
#include <ctime>
#include "fecha.hpp"
#include <clocale>
 
Fecha::Fecha (int dia, int mes, int anno) :d(dia),m(mes),a(anno)
{

	  	time_t tiempo_calendario = time(nullptr);
		tm* tiempo_descompuesto = localtime(&tiempo_calendario);
	
	if(dia == 0) 
	{
		d = tiempo_descompuesto->tm_mday;

	}

	else
	{
		d = dia; // tm_mon: 0 (ene)..11 (dic)
	}

	if(mes == 0)
	{
		m = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
	}

	else 
	{
		m = mes;
	}

	if(a == 0) 
	{
		a =  tiempo_descompuesto->tm_year + 1900; // tm_year: a~ nos desde 1900
	}
	
	else 
	{
		a = anno;
	}

}

Fecha::Fecha (const char* cad)
{
	time_t tiempo_calendario = std::time(nullptr);
	tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

	//sscan
	int dia,mes,anno;

	sscanf (cad, "%d/%d/%4d",&dia,&mes,&anno);

	if(dia == 0) 
	{
		d = tiempo_descompuesto->tm_mday;
	}

	else
	{
		d = dia; // tm_mon: 0 (ene)..11 (dic)
	}

	if(mes == 0)
	{
		m = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
	}

	else 
	{
		m = mes;
	}

	if(a == 0) 
	{
		a =  tiempo_descompuesto->tm_year + 1900; // tm_year: a~ nos desde 1900
	}
	else 
	{
		a = anno;
	}

}
//Contructor de copia 
/*
Fecha::Fecha (const Fecha& f)
{
	d = f.d;
	m = f.m;
	a = f.a;
}

*/

bool bisiesto(int a) 
{
	return (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0));
}

void Fecha::comprobaciones () const
{
	int dia_mes[13] = {0,31,28 + bisiesto(a),31,30,31,30,31,31,30,31,30,31};


	if ((d > dia_mes[m] || d <= 0)) 
	{
		throw (Invalida("ERROR: El dia no es valido"));
	}

	if ((m < 1 || m > 12)) 
	{
		throw (Invalida("ERROR: El mes no es valido"));
	}

	if ((a < AnnoMinimo || a > AnnoMaximo))
	{
		throw (Invalida("ERROR: El annio no es valido"));
	}

}

Fecha::Invalida::Invalida (const char* error)
{
	//e = error;
	int i;
	while (e[i] != '\0') 
	{
		e[i] = error[i];
		i++;
	}

}

char* Fecha::Invalida::por_que () const 
{
	return e;
}



Fecha& Fecha::operator + (int dia) 
{
	Fecha t;
	t = *this;
	return t += dia;

}

Fecha& Fecha::operator - (int dia)
{
	Fecha t;
	t = *this;
	return t += -dia;

}

Fecha& Fecha::operator ++ () 
{
	Fecha t;
	t = *this;
	return t+=1;

}

Fecha& Fecha::operator -- () 
{
	Fecha t;
	t = *this;
	return t+=1;

}


Fecha& Fecha::operator ++ (int )
{
	return *this += 1;
}

Fecha& Fecha::operator -- (int )
{
	return *this += -1;
}


Fecha& Fecha::operator += (int dia) 
{
	if (dia!=0)
	{
		tm hoy = {};

		hoy.tm_mday = this->d + dia;
		hoy.tm_mon = this->m - 1;
		hoy.tm_year = this->a - 1900;

		mktime(&hoy);

		this->d = hoy.tm_mday;
		this->m = hoy.tm_mon + 1;
		this->a = hoy.tm_year + 1900;
 
	}

	return *this ;
}

Fecha& Fecha::operator -= (int dia)
{
	return *this += dia;
}

Fecha& Fecha::operator = (Fecha& f)
{
	d = f.d;
	m = f.m;
	a = f.a;

}

bool operator > (const Fecha& f1, const Fecha& f2)
{
	return f2 < f1;
}

bool operator >= (const Fecha& f1, const Fecha& f2) 
{

	
}

bool operator < (const Fecha& f1, const Fecha& f2) 
{

	bool b = false;

	if (f1.anno() < f2.anno()) 
	{	
		b = true;
	}
	else 
	{
		if (f1.anno() == f2.anno() && f1.mes() < f2.mes()) 
		{	
			b = true;
		}		
		else
		{		
			if (f1.dia() < f2.dia()).
			{
				b = true;
			}
		}	
	}	

return b;

}

bool operator <= (const Fecha& f1, const Fecha& f2)
{

	bool b = false;

	if (a <= f.a) 
	{	
		b = true;
	}
	else 
	{
		if (m <= f.m) 
		{	
			b = true;
		}		
		else
		{		
			if (d <= f.d)
			{
				b = true;
			}
		}	
	}	

return b;

}

bool operator == (const Fecha& f1, const Fecha& f2)
{
	bool b = false;

	if (a == f.a && m == f.m && d == f.d) 
	{
		b = true;
	}

	return b;
}

Fecha::operator const char*() const
{

	tm hoy = {};
	char* cad = new char[40] ;

	hoy.tm_mday = this->d;
	hoy.tm_mon = this->m - 1;
	hoy.tm_year = this->a - 1900;
	
	std::setlocale(LC_TIME,"es_ES.UTF-8");
	mktime(&hoy);

	strftime(cad,40,"%A %d de %B de %Y",hoy);

	return cad;

}


printf("%s",a );
