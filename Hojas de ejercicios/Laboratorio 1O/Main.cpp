// María Eduarda Beckers, Carmen Gómez Becerra. Grupo 20.

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

int main() {
	
	SetConsoleOutputCP(CP_UTF8);

	// 1. Carga el catálogo y comprueba.
	std::ifstream entrada("catalogo.txt");
	if (!entrada.is_open()) {
		std::cout << "No se ha podido leer el archivo catalogo";
		return 1;
	}
	// crea él catálogo.
	Catalogo catalogo = Catalogo(entrada);
	entrada.close();

	// 2. Carga la lista de préstamos y comprueba.
	std::ifstream entrada2("prestamos.txt");
	if (!entrada2.is_open()) {
		std::cout << "No se ha podido leer el archivo prestamos";
		return 1;
	}
	// crea la lista de préstamos.
	ListaPrestamos prestamos = ListaPrestamos(entrada2, catalogo);
	prestamos.ordena();
	entrada2.close();
	int n;

	do {
		std::cout << "Elige una opción:\n"
			<< "\n"
			<< "  1. Mostrar el catálogo.\n"
			<< "  2. Mostrar préstamos.\n"
			<< "  3. Registrar ejemplar.\n"
			<< "  4. Prestar un ejemplar.\n"
			<< "  5. Devolver un ejemplar.\n"
			<< "  6. Salir.\n"
			<< "\n"
			<< "Opción: ";
		std::cin >> n;

		switch (n) {
		case 1:
			std::cout << "\n";
			std::cout << catalogo;
			break;

		case 2:
			std::cout << "\n";
			std::cout << prestamos;
			break;

		case 3: {
		    // lee el tipo.
			std::cout << "¿Es libro(L), audiovisual(A) o juego(J)? ";
			char letra;
			std::cin >> letra;

			Ejemplar::Tipo _tipo;
			std::cout << "\n";
			bool letraPuesta = false;

			do{
				switch (tolower(letra)) {
				case 'l': _tipo = Ejemplar::Tipo::L; letraPuesta = true; break;
				case 'j': _tipo = Ejemplar::Tipo::J; letraPuesta = true; break;
				case 'a': _tipo = Ejemplar::Tipo::A; letraPuesta = true; break;
				default:
					std::cout << "Letra no válida. Intente con L, J o A: ";
					std::cin >> letra;
					continue;
				}
				break;
			} while (!letraPuesta);

			// lee el título.
			std::cout << "\n" << "¿Cuál es su título?  ";
			std::string _nombre;
			std::cin.ignore(); // Limpiar el buffer antes de usar getline
			std::getline(std::cin, _nombre);

			// asigna codigo al ejemplar.
			int codigo = catalogo.insertaEjemplar(_tipo, _nombre);
			std::cout << "Insertado con código " << codigo << "\n";
			break;
		}

		case 4: {

			// pide el código del ejemplar.
			int idEjemplar;
			std::cout << "Código del ejemplar: ";
			std::cin >> idEjemplar;
			std::cout << "\n";

			// busca el ejemplar en el catálogo.
			Ejemplar* ejemplar = catalogo.buscaEjemplar(idEjemplar);

			// si no apunta a nada, no existe.
			if (ejemplar == nullptr) {
				std::cout << "No existe ningún ejemplar con código " << idEjemplar << "\n";
			}
			else {
				// dice el nombre del ejemplar.
				std::cout << " -> " << ejemplar->getNombre() << "\n";

				// se escribe el usuario.
				int idUser;
				std::cout << "Usuario al que se presta: ";
				std::cin >> idUser;

				// si se ha prestado el ejemplar...
				if (ejemplar->presta()) {
					Date fecha;
					// Se crea otro préstamo y se inserta en la lista de préstamos.
					Prestamo nuevoPrestamo = Prestamo(ejemplar, fecha, idUser);
					prestamos.insertaPrestamo(nuevoPrestamo);
					std::cout << "Ejemplar prestado.\n";
				}
				else {
					std::cout << "El ejemplar no está disponible.\n";
				}
			}
			prestamos.ordena();

			break;
		}

		case 5: {
			// Pide el código del ejemplar.
			int idEjemplar;
			std::cout << "Código del ejemplar: ";
			std::cin >> idEjemplar;
			std::cout << "\n";

			// Busca el ejemplar en el catálogo.
			Ejemplar* ejemplar = catalogo.buscaEjemplar(idEjemplar);

			// si no apunta a nada, no existe.
			if (ejemplar == nullptr) {
				std::cout << "No se ha encontrado un préstamo de ese ejemplar." << idEjemplar << "\n";
			}
			else {
				// si se ha devuelto el ejemplar.
				if (ejemplar->devuelve()) {

					// se quita el préstamo y queda devuelto.
					Prestamo quitarPrestamo = Prestamo(ejemplar, Date(), idEjemplar);
					prestamos.quitarPrestamo(quitarPrestamo);
					std::cout << "Ejemplar devuelto.\n";
				}
				else {
					std::cout << "No se ha encontrado un préstamo de ese ejemplar.\n";
				}
			}
			prestamos.ordena();

			break;
		}

		case 6:
			std::cout << "Saliendo...\n";
			return 0;

		default:
			std::cout << "Opción no válida. Inténtelo de nuevo.\n";
			break;
		}

		std::cout << "\n";

	} while (n != 6);

	return 0;
}