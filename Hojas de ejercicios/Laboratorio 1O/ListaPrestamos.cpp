// María Eduarda Beckers, Carmen Gómez Becerra. Grupo 20.
#include <algorithm>
#include <vector>
#include <array>
#include "ListaPrestamos.h"

ListaPrestamos::ListaPrestamos(std::istream& in, const Catalogo& c) {
	// Lee el número de elementos.
	in >> numElems;

	// Crea un array de préstamos de tamaño numElems.
	elems = new Prestamo[numElems];
	capacidad = numElems + 10; // Se establece esto como capacidad máxima.

	for (int i = 0; i < numElems; i++) {

		// Recorre el array leyendo y añadiendo préstamos a elems[].
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
	
	// Si se ha llegado a la capacidad máxima...
	if (numElems == capacidad) {
		capacidad += 10;
		Prestamo* newElems = new Prestamo[capacidad]; // ... se crea otro array auxiliar con mayor capacidad.

		for (size_t i = 0; i < numElems; i++) {
			// Se va pasando el contenido del viejo array al nuevo.
			newElems[i] = elems[i];
		}
		// Se borra el contenido del array original.
		delete[] elems;

		// Se mete el contenido del array aux en el original.
		elems = newElems;
	}
	
	// Se mete el préstamo en el array.
	elems[numElems] = p;
	numElems++; // Aumentamos índice.
}

void ListaPrestamos::quitarPrestamo(Prestamo& _prestamo) {
	int i = 0;
	bool encontrado = false;

	// Busca el préstamo en el array.
	while (!encontrado && i < numElems) {
		// Si el ejemplar del array coincide con el dado...
		if (elems[i].getEjemplar()->getCodigo() != _prestamo.getEjemplar()->getCodigo()) {
			// Se encuentra y se quita.
			encontrado = true;
			elems[i] = elems[numElems - 1];
			numElems--;
		}
		i++;
	}
}


std::ostream& operator<<(std::ostream& out, const ListaPrestamos& p) {
	// Se escriben todos los elementos de la lista de préstamos.
	for (int i = 0; i < p.numElems; i++) {
		out << p.elems[i] << "\n";
	}
	return out;
}
