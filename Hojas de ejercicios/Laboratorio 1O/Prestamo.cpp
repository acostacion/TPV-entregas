#include "Prestamo.h"

Prestamo::Prestamo() {
	ejemplar = nullptr;
	fecha = { 0, 0, 0 };
	usuario = 0;
}

Prestamo::Prestamo(Ejemplar* _ejemplar, Date _fecha, int _usuario) {
	ejemplar = _ejemplar;
	fecha = _fecha;
	usuario = _usuario;
}

bool Prestamo::operator<(const Prestamo& p) const {
	// Con qué otro préstamo se compara?
}

bool leePrestamo(const Catalogo& c) {

	// A MEDIAS.
	int ejemplar;
	std::cin >> ejemplar;
	c.buscaEjemplar(ejemplar);
}

std::ostream& operator<<(std::ostream& out, const Prestamo& p) {
	std::cout << p.ejemplar << " " << p.fecha << " " << p.usuario;
}