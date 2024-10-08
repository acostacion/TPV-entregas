// Mar�a Eduarda Beckers, Carmen G�mez Becerra. Grupo 20.
#include "Catalogo.h"
#include "Ejemplar.h"

#include <string>
#include <array>
#include <fstream>
#include <iostream>

Catalogo::Catalogo(std::istream& entrada) {
	// Lee el n� de elementos del cat�logo.
	entrada >> numElems;
	elems = new Ejemplar[numElems];
	capacidad = numElems + 10; // Se establece esto como capacidad m�xima.

	// Va almacenando cada elemento.
	for (int i = 0; i < numElems; i++) {
		entrada >> elems[i];
	}
}

Catalogo::~Catalogo() {
	delete[] elems;
}


Ejemplar* Catalogo::buscaEjemplar(int codigo) const {
	int ini = 0, fin = numElems - 1;

	// Busca si el ID del cat�logo coincide con el c�digo dado.

	while (ini <= fin) {
		int mitad = (ini + fin) / 2;

		if (elems[mitad].getCodigo() == codigo) {
			return &elems[mitad]; // Encontrado
		}
		else if (elems[mitad].getCodigo() > codigo) {
			fin = mitad - 1; // mira la mitad izquierda
		}
		else {
			ini = mitad + 1; //mira la mitad derecha
		}
	}

	return nullptr; // si no encuentra
}

int Catalogo::insertaEjemplar(Ejemplar::Tipo _t, std::string _nombre) {
	
	// Si se ha llegado a la capacidad m�xima...
	if (numElems == capacidad) {
		capacidad += 10;
		Ejemplar* newElems = new Ejemplar[capacidad]; // ... se crea otro array auxiliar con mayor capacidad.

		for (size_t i = 0; i < numElems; i++) {
			// Se va pasando el contenido del viejo array al nuevo.
			newElems[i] = elems[i];
		}
		// Se borra el contenido del array original.
		delete[] elems;

		// Se mete el contenido del array aux en el original.
		elems = newElems;

	}
	// Se saca el codigo del �ltimo elemento y se suma 1.
	int id = elems[numElems - 1].getCodigo() + 1;

	// Se crea un nuevo ejemplar con nuevo id, con el tipo y nombre.
	Ejemplar nuevoEjem(id, _t, _nombre);
	numElems++;
	return id;
}

std::ostream& operator<<(std::ostream& out, const Catalogo& catalogo) {
	// Se escriben todos los elementos del cat�logo.
	for (int i = 0; i < catalogo.numElems; i++) {
		out << catalogo.elems[i] << "\n";
	}
	return out;
}
