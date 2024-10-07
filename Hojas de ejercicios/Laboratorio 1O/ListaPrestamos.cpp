#include <algorithm>
#include <vector>
#include <array>
#include "ListaPrestamos.h"

ListaPrestamos::ListaPrestamos(std::istream& in, const Catalogo& c) {

	in >> numElems;
	elems = new Prestamo[numElems];
	capacidad = numElems + 10; 
	int codigo, idUsuario;
	Date _fecha;
	for (int i = 0; i < numElems; i++) {
		Prestamo nuevoPrestamo;
		nuevoPrestamo = nuevoPrestamo.leePrestamo(in, c);
		elems[i] = nuevoPrestamo;
	}
}

ListaPrestamos::~ListaPrestamos() {
	delete[] elems;
}

void ListaPrestamos::ordena() {
	std::sort(elems, elems + numElems);
}

void ListaPrestamos::insertaPrestamo(const Prestamo& p) {
	
	if (numElems == capacidad) {
		capacidad += 10;
		Prestamo* newElems = new Prestamo[capacidad];

		for (size_t i = 0; i < numElems; i++) {
			newElems[i] = elems[i];
		}
		delete[] elems;
		elems = newElems;
	}

	elems[numElems] = p;
	numElems++;
}

void ListaPrestamos::quitarPrestamo(Prestamo& _prestamo) {
	int i = 0;
	bool encontrado = false;
	while (!encontrado && i < numElems) {
		if (elems[i].getEjemplar()->getCodigo() != _prestamo.getEjemplar()->getCodigo()) {
			encontrado = true;
			elems[i] = elems[numElems - 1];
			numElems--;
		}
		i++;
	}
}


std::ostream& operator<<(std::ostream& out, const ListaPrestamos& p) {
	for (int i = 0; i < p.numElems; i++) {
		out << p.elems[i] << "\n";
	}
	return out;
}
