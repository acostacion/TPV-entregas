// María Eduarda Beckers, Carmen Gómez Becerra. Grupo 20.
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
	Date getDevolucion() const;
	bool operator<(const Prestamo&) const;
	Prestamo leePrestamo(std::istream&, const Catalogo&);
	friend std::ostream& operator<<(std::ostream&, const Prestamo&);
};

