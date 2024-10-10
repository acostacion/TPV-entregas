// María Eduarda Beckers, Carmen Gómez Becerra. Grupo 20.
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
	ListaPrestamos(const ListaPrestamos&);
	~ListaPrestamos();
	ListaPrestamos& operator=(const ListaPrestamos&);
	void ordena();
	void insertaPrestamo(const Prestamo&);
	void quitarPrestamo(Prestamo&);
	friend std::ostream& operator<<(std::ostream&, const ListaPrestamos&);
};

