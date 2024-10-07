//
// Declaraci�n de la clase 
//
#pragma once
#include <iostream>
#include "Prestamo.h"
#include "Catalogo.h"

class ListaPrestamos
{
private:
	Prestamo* elems;
	int numElems;
	int capacidad;
public:
	ListaPrestamos(std::istream&, const Catalogo&);
	~ListaPrestamos();
	void ordena();
	void insertaPrestamo(const Prestamo&);
	void quitarPrestamo(Prestamo&);
	friend std::ostream& operator<<(std::ostream&, const ListaPrestamos&);
};

