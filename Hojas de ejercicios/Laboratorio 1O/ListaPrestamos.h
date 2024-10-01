//
// Declaración de la clase 
//
#pragma once
#include "Prestamo.h"
#include "Catalogo.h"
class ListaPrestamos
{
private:
	Prestamo* elems;
	size_t numElems;
	size_t capacidad;
public:
	ListaPrestamos(std::istream&, const Catalogo&);
	~ListaPrestamos();
	void ordena();
	void insertaPrestamo(const Prestamo&);
	friend std::ostream& operator<<(std::ostream&, const ListaPrestamos&);
};

