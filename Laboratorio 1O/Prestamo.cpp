// María Eduarda Beckers, Carmen Gómez Becerra. Grupo 20.
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

Prestamo::Prestamo(const Prestamo& otro) {
	if (otro.ejemplar != nullptr) {
		// Realizar una copia profunda del objeto al que apunta el puntero
		ejemplar = new Ejemplar(*otro.ejemplar);
	}
	else {
		ejemplar = nullptr;
	}

	fecha = otro.fecha;
	usuario = otro.usuario;
}

Date Prestamo::getDevolucion() const {
	// Según el tipo devuelve fecha + penalización a la hora de hacer una devolución.
	if (ejemplar->getTipo() == Ejemplar::Tipo::L) return fecha + 30; // Libros
	if (ejemplar->getTipo() == Ejemplar::Tipo::A) return fecha + 7; // Audiovisual
	return fecha + 14; // Juegos 
}

bool Prestamo::operator<(const Prestamo& p) const {

	// Saca la fecha del préstamo global y la del préstamo del método.
	Date fechaEntrega1 = getDevolucion();
	Date fechaEntrega2 = p.getDevolucion();

	// Compara fechas de global < local.
	return fechaEntrega1 < fechaEntrega2;
}

Prestamo& Prestamo::operator=(const Prestamo& otro) {

	if (ejemplar != nullptr) {
		delete ejemplar; // lo eliminamos si es diferente de nullptr
	}
	if (otro.ejemplar != nullptr) { // Si no es nullptr
		// Realizar una copia profunda del objeto al que apunta el puntero
		ejemplar = new Ejemplar(*otro.ejemplar);
	} else {
		ejemplar = nullptr; 
	}
	fecha = otro.fecha;
	usuario = otro.usuario;
	return *this;
}

Prestamo Prestamo::leePrestamo(std::istream& in , const Catalogo& c) {
	// Lecturas y creaciones de punteros y variables.
	int id;
	in >> id;
	Ejemplar* ejemplarPTR;
	Date _fecha;
	int _usuario = 0;

	// Se busca el ejemplar con ese id y se apunta con ejemplarPTR.
	ejemplarPTR = c.buscaEjemplar(id);

	// Si no está vacío se lee la fecha y el usuario
	if (ejemplarPTR != nullptr) in >> _fecha >> _usuario;
		
	// Devuelve el préstamo con id al que apunta, fecha y usuario.
	return Prestamo(c.buscaEjemplar(id), _fecha, _usuario);
}

std::ostream& operator<<(std::ostream& out, const Prestamo& p) {
	// Se escribe tipo "1292 10/10/2010 223".
	std::cout << p.ejemplar->getCodigo() << " " << p.fecha << " " << p.usuario;
	return out;
}