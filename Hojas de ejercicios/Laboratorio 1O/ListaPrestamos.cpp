#include "ListaPrestamos.h"

ListaPrestamos::ListaPrestamos(std::istream& in, const Catalogo& c) {
	
	in >> numElems;

	int codigo;


	for (int i = 0; i < numElems; i++) {
		in >> codigo;
	}
}

ListaPrestamos::~ListaPrestamos() {
	delete[] elems;
}

void ordena() {

}

void insertaPrestamo(const Prestamo& p) {
	
}

std::ostream& operator<<(std::ostream& out, const ListaPrestamos& p) {
	for (int i = 0; i < p.numElems; i++) {
		out << p.elems[i] << "\n";
	}
}
