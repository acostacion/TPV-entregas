#include "Ejemplar.h"
#include "Prestamo.h"
#include "Date.hpp"
#include "Listaprestamos.h"
#include <iostream>
#include <string>

Ejemplar::Ejemplar() {
	id = 0;
	tipo = Nada;
	nombre = " ";
	disponible = false;
}
Ejemplar::Ejemplar(int _id , Tipo _tipo, std::string _nombre) {
	id = _id;
	tipo = _tipo;
	nombre = _nombre;
	disponible = true;
}

bool Ejemplar::presta() {
	if (disponible) {
		disponible = false;
		return true;
	}
	else {
		return false;
	}
}

bool Ejemplar::devuelve() {
	if (!disponible) {
		disponible = true;
		return true;
	} return false;

}

std::ostream& operator<<(std::ostream& out, const Ejemplar& ejemplar) {
	return out << ejemplar.id << " " << ejemplar.tipo << " " << ejemplar.nombre;
}

std::istream& operator>>(std::istream& in , Ejemplar& ejemplar) {
	char t;
	in >> ejemplar.id >> t;
	if (t == 'L') ejemplar.tipo = Ejemplar::L;
	if (t == 'A') ejemplar.tipo = Ejemplar::A;
	if (t == 'J') ejemplar.tipo = Ejemplar::J;
	else ejemplar.tipo == Ejemplar::Nada;

	std::getline(in, ejemplar.nombre);

	return in;
}