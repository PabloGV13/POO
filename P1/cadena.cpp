#include "cadena.hpp"

Cadena::Cadena (unsigned tam, char c) :s_(new char [tam+1]), tam_(tam)
{
	for(unsigned i = 0; i < tam; ++i)
	{
		s_[i] = c;
	}

	s_[tam]='\0';
}

Cadena::Cadena (const Cadena& cad): s_(new char [cad.tam_+1]),tam_(cad.tam_)
{
	strcpy(s_, cad.s_);
}

Cadena::Cadena (const char* cad): s_(new char [strlen(cad)+1]), tam_(strlen(cad))
{
	//tam_ = cad.length; //Hay q calcular el tamaño de la cadena
	 strcpy(s_, cad);
}

Cadena::Cadena (Cadena&& cad): s_(cad.s_),tam_(cad.tam_)
{
	cad.tam_ = 0;
	cad.s_= nullptr;
}

Cadena::~Cadena(){
        delete[] s_;
}

Cadena& Cadena::operator = (const Cadena& cad)
{
	if (this != &cad)
	{
		delete [] s_;
		tam_ = strlen(cad.c_str());
		s_ = new char[tam_ + 1];
		strcpy(s_,cad.s_);

	}

	return *this;
}

Cadena& Cadena::operator = (const char* cad)
{
	delete [] s_;
	tam_ = strlen(cad);
	s_ = new char[tam_ + 1];
	strcpy(s_,cad);
	return *this;
}

Cadena& Cadena::operator = (Cadena&& cad)
{
    delete[] s_;
    tam_ = cad.tam_;
    s_= cad.s_;
    cad.s_ = nullptr;
    cad.tam_ = 0;
    return *this;
}

Cadena& Cadena::operator += (const Cadena& cad)
{
	Cadena c_aux = *this;
	tam_ = c_aux.tam_+ cad.tam_;
	delete [] s_;
	s_ = new char[tam_+1];
	strcpy(s_,c_aux.s_);
	strcat(s_,cad.s_);
	return *this;
}


Cadena operator + (const Cadena& cad1, const Cadena& cad2)noexcept
{
	return Cadena(cad1) += cad2;
}

bool operator == (const Cadena& c1, const Cadena& c2)noexcept
{
	 return (strcmp(c1.c_str(), c2.c_str()) == 0);
}

bool operator != (const Cadena& c1, const Cadena& c2)noexcept
{

	return !(c1 == c2);

}

bool operator > (const Cadena& c1, const Cadena& c2)noexcept
{
	return (strcmp(c1.c_str(),c2.c_str()) > 0 );
}

bool operator < (const Cadena& c1, const Cadena& c2)noexcept
{
	return !(c1 == c2) && !(c1 > c2);
}

bool operator >= (const Cadena& c1, const Cadena& c2)noexcept
{
	return (c1 == c2) || (c1 > c2);
}

bool operator <= (const Cadena& c1, const Cadena& c2) noexcept
{
	return !(c1 > c2);
}

char& Cadena::operator [] (unsigned i) noexcept
{

	return s_[i];

}

char Cadena::operator [] (unsigned i) const noexcept
{
	return s_[i];
}

char& Cadena::at (unsigned i)
{
	if (i >= tam_)
	{
		throw  std::out_of_range("Error");
	}
		return (*this)[i];
}


char Cadena::at (unsigned i) const
{
	if (i >= tam_)
	{
		throw  std::out_of_range("Error");
	}
		return (*this)[i];
}

Cadena Cadena::substr (unsigned i,unsigned t) const //Devuelve Cadena&
{


	if (i >= this->length() || (t + i) > this->length() || (t + i) < i)
	{
		throw std::out_of_range("Error");
	}
	char* tmp = new char[t+1];
  std::strncpy(tmp, s_+ i,t);
  tmp[t]='\0';
  Cadena cad(tmp);
  delete [] tmp;
  return cad;
}

const char* Cadena::c_str() const noexcept
{
	return s_;
}

ostream& operator << (ostream& o,const Cadena& cad)noexcept
{
	o << cad.c_str();
	return o;
}

istream& operator >> (istream& is, Cadena& cad)noexcept
{
	char* tmp = new char[33];
  int i = 0;
  char aux;
  while(isspace(is.get()) && is.good()){}
  is.unget();
  while (i < 32 && !isspace(is.peek()) && is.good() && is.peek() != '\n' && is.peek()!='\0') {
    aux=is.get();
    if(is.good()) tmp[i++]=aux;
  }
  tmp[i]='\0';
  cad = tmp;
  delete[] tmp;
  return is;

}
