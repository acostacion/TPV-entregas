// Mar�a Eduarda Beckers, Carmen G�mez Becerra. Grupo 20.

#include <windows.h> 
#include <fstream>
#include <array>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include "Date.hpp" 
#include "Catalogo.h" 
#include "Prestamo.h" 
#include "ListaPrestamos.h" 
#include "Ejemplar.h" 



int duracionPrestamo(char tipo) {
	if (tipo == 'L') return 30; // Libros
	if (tipo == 'A') return 7; // Audiovisual
	return 14; // Juegos // Mejor usar switch o if-if-if.
}

Date FechaEntrega( const Prestamo& p) {
	return p.fecha + duracionPrestamo((p.ejemplarPtr->tipo));
}

bool operator<(const Prestamo& izdo, const Prestamo& dcho) {
	Date fechaEntrega1;
	Date fechaEntrega2;

	fechaEntrega1 = FechaEntrega( izdo);
	fechaEntrega2 = FechaEntrega( dcho);

	return fechaEntrega1 < fechaEntrega2;
}


#pragma region Methods
Ejemplar* buscarEjemplar(Catalogo c, int codigo) { // Habr�a que pasarlo por referencia. Quieres acceder al cat�logo pero no quieres ni modificarlo ni copiarlo, sino acceder a �l.
	

}

bool leerCatalogo(Catalogo& c) {
	// Abrimos archivo y comprobamos si se ha le�do bien.
	std::ifstream entrada("catalogo.txt");
	if (!entrada.is_open())return false;

	// Lee el n� de elementos del cat�logo.
	entrada >> c.numElems;

	c.elems = new Ejemplar[c.numElems];

	// Va almacenando cada elemento.
	for (int i = 0; i < c.numElems; i++) {
		// Guarda el ID, el tipo(L,A,J) y el nombre.
		entrada >> c.elems[i].id >> c.elems[i].tipo;
		std::getline(entrada, c.elems[i].nombre);
	}

	entrada.close();
	return true;
}



void mostrarPrestamos(const ListaPrestamos& p){
	for (int i = 0; i < p.numElems;i++) {
		if (p.elems[i].ejemplarPtr) { // si hay un prestamo
			Date fechaEntrega;

			fechaEntrega = FechaEntrega(inp.elems[i]);
			
			int diasHastaEntrega = fechaEntrega.diff(Date());
			
			int penalizacion;
			if (diasHastaEntrega < 0) penalizacion = -diasHastaEntrega * 2;
			else penalizacion = 0;

			std::cout << fechaEntrega << " (en " << diasHastaEntrega << " d�as) " << p.elems[i].ejemplarPtr->nombre;

			if (penalizacion > 0) {
				std::cout << " (" << penalizacion << " d�as de penalizaci�n)";
			}
			std::cout << "\n";
		}
	}
}

bool leerPrestamos(ListaPrestamos& p,Catalogo& c) {
	// Abrimos archivo y comprobamos si se ha le�do bien.
	std::ifstream entrada("prestamos.txt");
	if (!entrada.is_open()) return false;

	entrada >> p.numElems;
	p.elems = new Prestamo[p.numElems];

	for(int i = 0; i < p.numElems; i++) {
		entrada >> p.elems[i].codigoEjemplar >> p.elems[i].fecha >> p.elems[i].idUsuario;
		p.elems[i].ejemplarPtr = buscarEjemplar(c , p.elems[i].codigoEjemplar);
	}
	
	entrada.close();
	return true;

}
#pragma endregion



int main() {
	
	// 1. Carga el cat�logo y la lista de pr�stamos
	SetConsoleOutputCP(CP_UTF8);

	Catalogo catalogo;
	ListaPrestamos prestamos;

	if (!leerCatalogo(catalogo)) {
		std::cout << "No se ha podido leer el archivo";
		return 1;
	}
	if (!leerPrestamos(prestamos, catalogo)) {
		std::cout << "No se ha podido leer el archivo";
		return 1;
	}

	
	std::sort(prestamos.elems, prestamos.elems + prestamos.numElems);
	mostrarPrestamos(prestamos);


	return 0;
}