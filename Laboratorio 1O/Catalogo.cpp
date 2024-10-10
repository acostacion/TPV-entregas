// María Eduarda Beckers, Carmen Gómez Becerra. Grupo 20.
#include "Catalogo.h"
#include "Ejemplar.h"

#include <string>
#include <array>
#include <fstream>
#include <iostream>

Catalogo::Catalogo(std::istream& entrada) {
	// Lee el nº de elementos del catálogo.
	entrada >> numElems;
	capacidad = numElems * 2;// Se establece esto como capacidad máxima.
	elems = new Ejemplar[capacidad];

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

	// Se saca el codigo del último elemento y se suma 1.
	int id = (numElems > 0) ? elems[numElems - 1].getCodigo() + 1 : 1;

	// Se crea un nuevo ejemplar con nuevo id, con el tipo y nombre.
	Ejemplar nuevoEjem (id, _t, _nombre);
	
	elems[numElems] = nuevoEjem;

	numElems++;

	// Si se ha llegado a la capacidad máxima...
	if (numElems == capacidad) {
		capacidad = capacidad*2;
		Ejemplar* newElems = new Ejemplar[capacidad]; // ... se crea otro array auxiliar con mayor capacidad.
		
		// Se mete el contenido del array aux en el original.
		for (int i = 0; i < numElems; i++) {
			// Se va pasando el contenido del viejo array al nuevo.
			newElems[i] = elems[i];
		}

		// Se borra el contenido del array original.
		delete[] elems;
		elems = newElems;
	}
	return id;
}

std::ostream& operator<<(std::ostream& out, const Catalogo& catalogo) {
	// Se escriben todos los elementos del catálogo.
	out << "   Id  Tipo         Nombre" << "\n";

	for (int i = 0; i < catalogo.numElems; i++) {
		out << catalogo.elems[i] << "\n";
	}
	return out;
}
