#pragma once
#include <iostream>
template<typename T>
class Vector2D
{
private:
	T x;
	T y;
public:
	Vector2D() : x(), y() {}
	Vector2D(T x, T y) : x(x), y(y) {}

	T getX() const {
		return x;
	}
	T getY() const {
		return y;
	}
	void setX(T newX) {
		x = newX;
	}
	void setY(T newY) {
		y = newY;
	}
	Vector2D<T> operator+(const Vector2D<T>& otroVector) const {
		return Vector2D<T>(x + otroVector.x, y + otroVector.y);
	}
	Vector2D<T> operator-(const Vector2D<T>& otroVector) const {
		return Vector2D<T>(x - otroVector.x, y - otroVector.y);
	}
	T operator*(const Vector2D<T>& otroVector) const {
		return x * otroVector.x + y * otroVector.y;
	}

	Vector2D<T> operator*(const T& escalar) const {
		return Vector2D<T>(x * escalar, y * escalar);
	}
	Vector2D<T>& operator*=(const T& escalar) {
		x *= escalar;
		y *= escalar;
		return *this;
	}
	Vector2D<T>& operator+=(const Vector2D<T>& otroVector) {
		x += otroVector.x;
		y += otroVector.y;
		return *this;
	}

};
template<typename T>
using Point2D = Vector2D<T>;

