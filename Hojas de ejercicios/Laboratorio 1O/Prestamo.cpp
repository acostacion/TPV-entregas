#include "Prestamo.h"

Prestamo::Prestamo() {
	ejemplar = nullptr;
	fecha = Date();
	usuario = 0;
}

Prestamo::Prestamo(Ejemplar* _ejemplar, Date _fecha, int _usuario) {
	ejemplar = _ejemplar;
	fecha = _fecha;
	usuario = _usuario;
}

Date Prestamo::getDevolucion() const {
	if (ejemplar->getTipo() == Ejemplar::Tipo::L) return fecha + 30; // Libros
	if (ejemplar->getTipo() == Ejemplar::Tipo::A) return fecha + 7; // Audiovisual
	return fecha + 14; // Juegos // Mejor usar switch o if-if-if.
}

bool Prestamo::operator<(const Prestamo& p) const {
	Date fechaEntrega1 = getDevolucion();
	Date fechaEntrega2 = p.getDevolucion();

	return fechaEntrega1 < fechaEntrega2;
}

Prestamo Prestamo::leePrestamo(std::istream& in , const Catalogo& c) {
	int codi;
	in >> codi;
	Ejemplar* ejemplo;
	Prestamo nuevoPrestamo;
	ejemplo = c.buscaEjemplar(codi);
	if (ejemplo != nullptr) {
		Date _fecha;
		int _usuario;
		in >> _fecha >> _usuario;
		nuevoPrestamo = Prestamo(c.buscaEjemplar(codi), _fecha, _usuario);
	}
	return nuevoPrestamo;
}

std::ostream& operator<<(std::ostream& out, const Prestamo& p) {
	std::cout << p.ejemplar << " " << p.fecha << " " << p.usuario;
	return out;
}