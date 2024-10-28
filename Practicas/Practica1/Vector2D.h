#pragma once
#include <string>
#include <fstream>
#include <iostream>

// Template para representar una clase de tipo T (genérica).
template <class T>
class Vector2D
{
private:
	T x;
	T y;

public:
	Vector2D() {
		x = 0;
		y = 0;
	}

	Vector2D(T _x, T _y) {
		x = _x;
		y = _y;
	}

	Vector2D<T> operator-(const Vector2D<T>& other) const { // Diferencia.
		return Vector2D(x - other.GetX(), this->y - other.GetY());
	}

	Vector2D<T> operator+(const Vector2D<T>& other) const { // Suma.
		return Vector2D(x + other.GetX(), this->y + other.GetY());
	}

	int operator*(const Vector2D<T>& other) const { // Producto vectorial.
		return (x * other.GetX + y * other.GetY);
	}

	Vector2D<T> operator*(const T e) const { // Producto por un escalar.
		return Vector2D(x * e, this->y *e);
	}

	bool operator==(const Vector2D<T>& other) const { // Igualdad.
		return (x == other.GetX() && this->y == other.GetY());
	}

	// Acceder a los valores x e y.
	T GetX() const { return this->x; }
	T GetY() const { return this->y; }

	// Setear valores x e y.
	void SetX(T otherX) { this->x = otherX; }
	void SetY(T otherY) { this->y = otherY; }

	// Entrada para leer x e y.
	friend std::istream& operator>>(std::istream& in, Vector2D& vec) {
		return (in >> vec.x >> vec.y);
	}
};

// Para llamar a Vector2D como Point2D.
template <class T>
using Point2D = Vector2D<T>;