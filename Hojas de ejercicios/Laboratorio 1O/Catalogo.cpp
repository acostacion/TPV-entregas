#include "Catalogo.h"
#include "Ejemplar.h"

#include <string>
#include <array>
#include <fstream>
#include <iostream>

Catalogo::Catalogo(std::istream& entrada) {
	// Lee el nº de elementos del catálogo.
	entrada >> numElems;
	elems = new Ejemplar[numElems];
	capacidad = numElems + 10;

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

	// Busca si el ID del catálogo coincide con el código dado.

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
	
	if (numElems == capacidad) {
		capacidad += 10;
		Ejemplar* newElems = new Ejemplar[capacidad];

		for (size_t i = 0; i < numElems; i++) {
			newElems[i] = elems[i];
		}
		delete[] elems;
		elems = newElems;

	}
	int cod = elems[numElems - 1].getCodigo() + 1;
	Ejemplar nuevoEjem(cod, _t, _nombre);
	numElems++;
	return cod;
}

std::ostream& operator<<(std::ostream& out, const Catalogo& catalogo) {
	for (int i = 0; i < catalogo.numElems; i++) {
		out << catalogo.elems[i] << "\n";
	}
	return out;
}
