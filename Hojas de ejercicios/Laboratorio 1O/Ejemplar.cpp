#include "Ejemplar.h"
#include <iostream>

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

void Ejemplar::presta() {

}

void Ejemplar::devuelve() {

}

std::ostream& operator<<(std::ostream& out, const Ejemplar& ejemplar) {
	return out << ejemplar.id << " " << ejemplar.tipo << " " << ejemplar.nombre;
}

std::istream& operator>>(std::istream& in , Ejemplar& ejemplar) {
	char c, t;
	
	in >> ejemplar.id >> c >> t >> c >> ejemplar.nombre;
	if (t == 'L') ejemplar.tipo = Ejemplar::L;
	if (t == 'A') ejemplar.tipo = Ejemplar::A;
	if (t == 'J') ejemplar.tipo = Ejemplar::J;
	else ejemplar.tipo == Ejemplar::Nada;

	return in;

}