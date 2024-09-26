// María Eduarda Beckers, Carmen Gómez Becerra.
#include <fstream>
#include <array>
#include <string>
#include <iostream>

struct Ejemplar { // 1 ejemplar.
	int id;
	char tipo;
	std::string nombre;
};

struct Catalogo { // Catálogo de ejemplares.
	int numElems;
	Ejemplar* elems;
};

bool leerCatalogo() {
	// Abrimos archivo y comprobamos si se ha leído bien.
	std::ifstream entrada("catalogo.txt");
	if (!entrada.is_open())return false;

	// Lee el nº de elementos del catálogo.
	Catalogo c;
	entrada >> c.numElems;

	// Va almacenando cada elemento.
	for (int i = 0; i < c.numElems; i++) {
		// Guarda el ID, el tipo(L,A,J) y el nombre.
		entrada >> c.elems[i].id >> c.elems[i].tipo;
		getline(entrada, c.elems[i].nombre);
	}

	entrada.close();
	return true;
}


bool leerPrestamos() {
	// Abrimos archivo y comprobamos si se ha leído bien.
	std::ifstream entrada("prestamos.txt");
	if (!entrada.is_open()) return false;

	Catalogo c;
	int npres; // Número de préstamos.
	entrada >> npres;
		for (int i = 0; i < npres; i++) {

	}
	Ejemplar* nprestamo = buscarEjemplar(c, );
	entrada.close();
	return true;

}

void ordenarPrestamos() {

}

Ejemplar* buscarEjemplar(Catalogo c, int codigo) {
	bool encontrado = false;
	int i = 0;

	// Busca si el ID del catálogo coincide con el código dado.
	while (!encontrado) {
		encontrado = c.elems[i].id == codigo;
		i++;
	}

	// Al encontrarlo devuelve el puntero a ese ID.
	if (encontrado) return &c.elems[i];
	return nullptr;
	
}

int main() {
	


}