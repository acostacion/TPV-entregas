// María Eduarda Beckers, Carmen Gómez Becerra.

#include <fstream>
#include <array>
#include <string>
#include <iostream>
#include <windows.h> 
#include <algorithm>

#include "Date.cpp" 


struct Ejemplar { // 1 ejemplar.
	int id;
	char tipo;
	std::string nombre;
};

struct Catalogo { // Catálogo de ejemplares.
	int numElems;
	Ejemplar* elems;
};

struct Prestamo {
	int codigoEjemplar;
	Date data;
	Ejemplar* ejemplarPtr;
	int idUsuario;
};

struct ListaPrestamos { // Catálogo de ejemplares.
	int numElems;
	Prestamo* elems;
};



Ejemplar* buscarEjemplar(Catalogo c, int codigo) {
	int ini = 0, fin = c.numElems -1;

	// Busca si el ID del catálogo coincide con el código dado.

	while (ini <= fin) {
		int mitad = (ini + fin) / 2;

		if (c.elems[mitad].id == codigo) {
			return &c.elems[mitad]; // Encontrado
		}
		else if (c.elems[mitad].id > codigo) {
			fin = mitad - 1; // mira la mitad izquierda
		}
		else {
			ini = mitad + 1; //mira la mitad derecha
		}
	}

	return nullptr; // si no encuentra

}


bool leerCatalogo(Catalogo& c) {
	// Abrimos archivo y comprobamos si se ha leído bien.
	std::ifstream entrada("catalogo.txt");
	if (!entrada.is_open())return false;

	// Lee el nº de elementos del catálogo.
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
void ordenarPrestamos(ListaPrestamos& p) {

	std::sort(p.elems, p.elems + p.numElems, [](const Prestamo& a, const Prestamo& b) {
		return a.data < b.data; // Ordenar por fecha
		});

}
int duracionPrestamo(char tipo) {
	if (tipo == 'L') return 30; // Libros
	else if (tipo == 'A') return 7; // Audio visual
	return 14; // Juegos
}

void mostrarPrestamos(const ListaPrestamos& p){
	for (int i = 0; i < p.numElems;i++) {
		if (p.elems[i].ejemplarPtr) { // si hay un prestamo
			Date fechaEntrega = p.elems[i].data;

			
			fechaEntrega += duracionPrestamo((p.elems[i].ejemplarPtr->tipo));
			
			
			int diasHastaEntrega = fechaEntrega.diff(Date());
			
			int penalizacion;
			if (diasHastaEntrega < 0) penalizacion = -diasHastaEntrega * 2;
			else penalizacion = 0;

			std::cout << fechaEntrega << " (en " << diasHastaEntrega << " días) " << p.elems[i].ejemplarPtr->nombre;

			if (penalizacion > 0) {
				std::cout << " (" << penalizacion << " días de penalización)";
			}
			std::cout << "\n";
		}
	}
}

bool leerPrestamos(ListaPrestamos& p,Catalogo& c) {
	// Abrimos archivo y comprobamos si se ha leído bien.
	std::ifstream entrada("prestamos.txt");
	if (!entrada.is_open()) return false;

	entrada >> p.numElems;
	p.elems = new Prestamo[p.numElems];

	for(int i = 0; i < p.numElems; i++) {
		entrada >> p.elems[i].codigoEjemplar >> p.elems[i].data >> p.elems[i].idUsuario;
		p.elems[i].ejemplarPtr = buscarEjemplar(c , p.elems[i].codigoEjemplar);
	}
	
	entrada.close();
	return true;

}



int main() {
	
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
	ordenarPrestamos(prestamos);
	mostrarPrestamos(prestamos);


	return 0;
}