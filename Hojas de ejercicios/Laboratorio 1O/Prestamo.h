//
// Declaración de la clase 
//
#pragma once

#include <iostream>
#include "Ejemplar.h"
#include "Date.hpp"
#include "Catalogo.h"

class Prestamo
{
private:
	Ejemplar* ejemplar;
	Date fecha;
	int usuario;
public:

	Prestamo(); Prestamo(Ejemplar*, Date, int);
	Ejemplar* getEjemplar() { return ejemplar; };
	Date getFecha() { return fecha; };
	int getUsuario() const { return usuario; };
	Ejemplar* getDevolucion() const { return ejemplar; };
	bool operator<(const Prestamo&) const;
	bool leePrestamo(const Catalogo&);
	friend std::ostream& operator<<(std::ostream&, const Prestamo&);
};

