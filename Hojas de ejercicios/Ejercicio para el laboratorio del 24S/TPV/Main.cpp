#include <fstream>
#include <array>
#include <string>
#include <iostream>

struct Ejemplar {
	int id;
	char tipo;
	std::string nombre;
};

struct Catalogo {
	int numElems;
	Ejemplar* elems;
};

bool leerCatalogo() {
	std::ifstream entrada("catalogo.txt");
	if (!entrada.is_open())return false;
	Catalogo c;
	entrada >> c.numElems;
	std::string linea;

	for (int i = 0; i < c.numElems; i++) {
		entrada >> c.elems[i].id >> c.elems[i].tipo;
		getline(entrada, c.elems[i].nombre);
	}

	entrada.close();
	return true;
}


bool leerPrestamos() {

}

void ordenarPrestamos() {

}

Ejemplar* buscarEjemplar(Catalogo catalogo, int codigo) {
	bool encontrado = false;
	int i = 0;
	while (!encontrado) {
		encontrado = catalogo.elems[i].id == codigo;
		i++;
	}
	if (encontrado) return &catalogo.elems[i];
	return nullptr;
	
}

int main() {
	leerCatalogo(std:: catalogo);


}