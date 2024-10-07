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

int main() {
	// 1. Carga el cat�logo y la lista de pr�stamos
	SetConsoleOutputCP(CP_UTF8);

	std::ifstream entrada("catalogo.txt");
	if (!entrada.is_open()) {
		std::cout << "No se ha podido leer el archivo catalogo";
		return 1;
	}
	Catalogo catalogo = Catalogo(entrada);
	entrada.close();

	std::ifstream entrada2("prestamos.txt");
	if (!entrada2.is_open()) {
		std::cout << "No se ha podido leer el archivo prestamos";
		return 1;
	}
	ListaPrestamos prestamos = ListaPrestamos(entrada2, catalogo);
	entrada2.close();
	int n;

	do {
		std::cout << "Elige una opci�n:\n"
			<< "\n"
			<< "  1. Mostrar el cat�logo.\n"
			<< "  2. Mostrar pr�stamos.\n"
			<< "  3. Registrar ejemplar.\n"
			<< "  4. Prestar un ejemplar.\n"
			<< "  5. Devolver un ejemplar.\n"
			<< "  6. Salir.\n"
			<< "\n"
			<< "Opci�n: ";
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
			std::cout << "�Es libro(L), audiovisual(A) o juego(J)? ";
			char letra;
			std::cin >> letra;

			Ejemplar::Tipo _tipo;
			std::cout << "\n";
			while (true) {
				switch (tolower(letra)) {
				case 'l': _tipo = Ejemplar::Tipo::L; break;
				case 'j': _tipo = Ejemplar::Tipo::J; break;
				case 'a': _tipo = Ejemplar::Tipo::A; break;
				default:
					std::cout << "Letra no v�lida. Intente con L, J o A: ";
					std::cin >> letra;
					continue;
				}
				break;
			}

			std::cout << "\n" << "�Cu�l es su t�tulo?  ";
			std::string _nombre;
			std::cin.ignore(); // Limpiar el buffer antes de usar getline
			std::getline(std::cin, _nombre);

			int codigo = catalogo.insertaEjemplar(_tipo, _nombre);
			std::cout << "Insertado con c�digo " << codigo << "\n";
			break;
		}

		case 4: {
			int codEjemplar;
			std::cout << "C�digo del ejemplar: ";
			std::cin >> codEjemplar;
			std::cout << "\n";
			Ejemplar* ejem = catalogo.buscaEjemplar(codEjemplar);
			if (ejem == nullptr) {
				std::cout << "No existe ning�n ejemplar con c�digo " << codEjemplar << "\n";
			}
			else {
				std::cout << " -> " << ejem->getNombre() << "\n";
				int idUsu;
				std::cout << "Usuario al que se presta: ";
				std::cin >> idUsu;

				if (ejem->presta()) {
					Date fecha;
					Prestamo nuevoPrestamo = Prestamo(ejem, fecha, idUsu);
					prestamos.insertaPrestamo(nuevoPrestamo);
					std::cout << "Ejemplar prestado.\n";
				}
				else {
					std::cout << "El ejemplar no est� disponible.\n";
				}
			}
			break;
		}

		case 5: {
			int codEjemplar;
			std::cout << "C�digo del ejemplar: ";
			std::cin >> codEjemplar;
			std::cout << "\n";
			Ejemplar* ejem = catalogo.buscaEjemplar(codEjemplar);
			if (ejem == nullptr) {
				std::cout << "No se ha encontrado un pr�stamo de ese ejemplar." << codEjemplar << "\n";
			}
			else {
				if (ejem->devuelve()) {
					Prestamo quitarPrestamo = Prestamo(ejem, Date(), codEjemplar);
					prestamos.quitarPrestamo(quitarPrestamo);
					std::cout << "Ejemplar devuelto.\n";
				}
				else {
					std::cout << "No se ha encontrado un pr�stamo de ese ejemplar.\n";
				}
			}
			break;
		}

		case 6:
			std::cout << "Saliendo...\n";
			return 0;

		default:
			std::cout << "Opci�n no v�lida. Int�ntelo de nuevo.\n";
			break;
		}

		std::cout << "\n";

	} while (n != 6);

	return 0;
}