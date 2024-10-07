//
// Declaración de la clase 
//
#pragma once
#include <iostream>
#include "Ejemplar.h"
class Catalogo
{
private:
	Ejemplar* elems;
	size_t numElems;
	size_t capacidad;

public:
	Catalogo(std::istream&);
	~Catalogo();
	Ejemplar* buscaEjemplar(int) const;
	int insertaEjemplar(Ejemplar::Tipo, std::string);
	friend  std::ostream& operator<<(std::ostream&, const Catalogo&);
};

