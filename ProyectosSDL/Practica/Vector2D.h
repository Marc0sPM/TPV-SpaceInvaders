#pragma once


using namespace std;
template<typename T>
class Vector2D
{
private:
	T x, y;

public:
	Vector2D<T>::Vector2D() : x(), y() {};
	Vector2D<T>::Vector2D(T x1, T y1) : x(x1), y(y1) {};
	
	getX() { return x; };
	getY() { return y; };

	Vector2D<T> operator+(const Vector2D<T> other) {
		return Vector2D<T>(x + other.x, y + other.y);
	}
	Vector2D<T> operator-(const Vector2D<T> other) {
		return Vector2D<T>(x - other.x, y - other.y);
	}
	T operator*(const Vector2D<T> other) {
		return x * x.other + y * other.y;
	}
	Vector2D<T> operator*(const T esc) {
		return Vector2D<T>(x * esc, y * esc);
	}

};

template<typename T>
using Point2D = Vector2D;

