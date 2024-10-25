#pragma once
#include <string>
#include <fstream>
#include <iostream>
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

	Vector2D<T> operator-(const Vector2D<T>& other) const {
		return Vector2D(x - other.GetX(), this->y - other.GetY());
	}



	Vector2D<T> operator+(const Vector2D<T>& other) const {
		return Vector2D(x + other.GetX(), this->y + other.GetY());
	}

	int operator*(const Vector2D<T>& other) const {
		return (x * other.GetX + y * other.GetY);
	}

	Vector2D<T> operator*(const T e) const {
		return Vector2D(x * e, this->y *e);
	}

	T GetX() const { return this->x; }
	T GetY() const { return this->y; }


	friend std::istream& operator>>(std::istream& in, Vector2D& vec) {
		return (in >> vec.x >> vec.y);
	}
};

template <class T>
using Point2D = Vector2D<T>;