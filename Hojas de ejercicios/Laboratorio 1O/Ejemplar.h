//
// Declaración de la clase 
//
#include <iostream>
#pragma once
class Ejemplar
{
public:
	enum Tipo {
		Nada,
		L,
		A,
		J
	};
	Ejemplar();
	Ejemplar(int, Tipo, std::string);
	int getCodigo() { return id; };
	Tipo getTipo() { return tipo; };
	std::string getNombre() const { return nombre; };

	void presta();

	void devuelve();

	friend std::ostream& operator<<(std::ostream&, const Ejemplar&);

	friend std::istream& operator>>(std::istream&, Ejemplar&);

private:
	int id;
	Tipo tipo;
	std::string nombre;
	bool disponible;


};

