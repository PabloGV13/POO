#ifndef CADENA_H
#define CADENA_H
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <iterator>
#include <functional>

using namespace std;




class Cadena
{

	public:

		~Cadena();
		explicit Cadena(unsigned tam = 0, char c = ' ');
		Cadena (const Cadena& cad);
		Cadena(Cadena&& cad);
		Cadena (const char* cad);
		Cadena substr (unsigned i,unsigned t) const ;

		Cadena& operator = (const Cadena& cad);
		Cadena& operator = (Cadena&& cad);
		Cadena& operator = (const char* cad);
		unsigned length() const noexcept{return tam_;};

		Cadena& operator += (const Cadena& cad);

		char& operator [] (unsigned i)noexcept;
		char operator [] (unsigned i) const noexcept;
		char at (unsigned i) const ;
		char& at (unsigned i);

		const char* c_str() const noexcept;

		//friend ostream& operator << (ostream& o,const Cadena& cad);
		//friend istream& operator >> (istream& i, Cadena& cad);
		//operator const char * () const noexcept;

		//Iteradores:

		typedef char* iterator;
		typedef const char* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		iterator begin() noexcept {return s_;};
		iterator end()noexcept {return s_+ tam_;};

		const_iterator begin() const noexcept {return s_;};
		const_iterator end() const noexcept {return s_ + tam_;};

		const_iterator cbegin() const noexcept {return begin();};
		const_iterator cend() const noexcept {return end();};

		reverse_iterator rbegin() noexcept{return reverse_iterator(end());};
		reverse_iterator rend() noexcept{return reverse_iterator(begin());};

		const_reverse_iterator rbegin() const noexcept{ return const_reverse_iterator(end());};
    const_reverse_iterator rend() const noexcept{ return const_reverse_iterator(begin()); };

		const_reverse_iterator crbegin() const noexcept{ return const_reverse_iterator(end()); };
		const_reverse_iterator crend() const noexcept{ return const_reverse_iterator(begin()); };

	private:
		char* s_;
		unsigned tam_;

};

ostream& operator << (ostream& o,const Cadena& cad) noexcept;
istream& operator >> (istream& i, Cadena& cad) noexcept;

Cadena operator + (const Cadena& cad1, const Cadena& cad2) noexcept;

bool operator == (const Cadena& c1, const Cadena& c2) noexcept;
bool operator != (const Cadena& c1, const Cadena& c2)noexcept;
bool operator > (const  Cadena& c1, const Cadena& c2)noexcept;
bool operator < (const Cadena& c1, const Cadena& c2)noexcept;
bool operator >= (const Cadena& c1, const Cadena& c2)noexcept;
bool operator <= (const Cadena& c1, const Cadena& c2)noexcept;

namespace std {
template <> struct hash<Cadena> {
size_t operator()(const Cadena& cad) const
{ // conversión const char* ->string
return hash<string>{}(cad.c_str());
}
};
}

#endif
