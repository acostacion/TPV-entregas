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
	
	SetConsoleOutputCP(CP_UTF8);

	// 1. Carga el cat�logo y comprueba.
	std::ifstream entrada("catalogo.txt");
	if (!entrada.is_open()) {
		std::cout << "No se ha podido leer el archivo catalogo";
		return 1;
	}
	// crea �l cat�logo.
	Catalogo catalogo = Catalogo(entrada);
	entrada.close();

	// 2. Carga la lista de pr�stamos y comprueba.
	std::ifstream entrada2("prestamos.txt");
	if (!entrada2.is_open()) {
		std::cout << "No se ha podido leer el archivo prestamos";
		return 1;
	}
	// crea la lista de pr�stamos.
	ListaPrestamos prestamos = ListaPrestamos(entrada2, catalogo);
	prestamos.ordena();
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
		    // lee el tipo.
			std::cout << "�Es libro(L), audiovisual(A) o juego(J)? ";
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
					std::cout << "Letra no v�lida. Intente con L, J o A: ";
					std::cin >> letra;
					continue;
				}
				break;
			} while (!letraPuesta);

			// lee el t�tulo.
			std::cout << "\n" << "�Cu�l es su t�tulo?  ";
			std::string _nombre;
			std::cin.ignore(); // Limpiar el buffer antes de usar getline
			std::getline(std::cin, _nombre);

			// asigna codigo al ejemplar.
			int codigo = catalogo.insertaEjemplar(_tipo, _nombre);
			std::cout << "Insertado con c�digo " << codigo << "\n";
			break;
		}

		case 4: {

			// pide el c�digo del ejemplar.
			int idEjemplar;
			std::cout << "C�digo del ejemplar: ";
			std::cin >> idEjemplar;
			std::cout << "\n";

			// busca el ejemplar en el cat�logo.
			Ejemplar* ejemplar = catalogo.buscaEjemplar(idEjemplar);

			// si no apunta a nada, no existe.
			if (ejemplar == nullptr) {
				std::cout << "No existe ning�n ejemplar con c�digo " << idEjemplar << "\n";
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
					// Se crea otro pr�stamo y se inserta en la lista de pr�stamos.
					Prestamo nuevoPrestamo = Prestamo(ejemplar, fecha, idUser);
					prestamos.insertaPrestamo(nuevoPrestamo);
					std::cout << "Ejemplar prestado.\n";
				}
				else {
					std::cout << "El ejemplar no est� disponible.\n";
				}
			}
			prestamos.ordena();

			break;
		}

		case 5: {
			// Pide el c�digo del ejemplar.
			int idEjemplar;
			std::cout << "C�digo del ejemplar: ";
			std::cin >> idEjemplar;
			std::cout << "\n";

			// Busca el ejemplar en el cat�logo.
			Ejemplar* ejemplar = catalogo.buscaEjemplar(idEjemplar);

			// si no apunta a nada, no existe.
			if (ejemplar == nullptr) {
				std::cout << "No se ha encontrado un pr�stamo de ese ejemplar." << idEjemplar << "\n";
			}
			else {
				// si se ha devuelto el ejemplar.
				if (ejemplar->devuelve()) {

					// se quita el pr�stamo y queda devuelto.
					Prestamo quitarPrestamo = Prestamo(ejemplar, Date(), idEjemplar);
					prestamos.quitarPrestamo(quitarPrestamo);
					std::cout << "Ejemplar devuelto.\n";
				}
				else {
					std::cout << "No se ha encontrado un pr�stamo de ese ejemplar.\n";
				}
			}
			prestamos.ordena();

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