// María Eduarda Beckers, Carmen Gómez Becerra. Grupo 20.
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

	// Si está disponible, deja de estarlo porque se presta.
	if (disponible) {
		disponible = false;
		return true; // Prestado con éxito.
	}
	else {
		return false; // No prestado.
	}
}

bool Ejemplar::devuelve() {
	// Si no está disponible el ejemplar en el catálogo, lo devuelve.
	if (!disponible) {
		disponible = true;
		return true; // Devuelto con éxito.
	} return false; // No devuelto.

}

std::ostream& operator<<(std::ostream& out, const Ejemplar& ejemplar) {
	// Escribe del tipo "1927 L Amén, buenos días".
	return out << ejemplar.id << " " << ejemplar.tipo << " " << ejemplar.nombre;
}

std::istream& operator>>(std::istream& in , Ejemplar& ejemplar) {
	char t;

	// Lee el id y el tipo.
	in >> ejemplar.id >> t;

	// Clasifica el tipo.
	if (t == 'L') ejemplar.tipo = Ejemplar::L;
	if (t == 'A') ejemplar.tipo = Ejemplar::A;
	if (t == 'J') ejemplar.tipo = Ejemplar::J;
	else ejemplar.tipo == Ejemplar::Nada;

	// Lee el nombre.
	std::getline(in, ejemplar.nombre);

	return in; // Devuelve todo lo leído.
}