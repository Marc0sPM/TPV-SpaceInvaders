#pragma once
#include "checkML.h"

template <typename T>
class Vector2D {
private:
    T x, y;

public:
    Vector2D():x(T()), y(T()){}
    Vector2D(T x1, T y1) : x(x1), y(y1) {}

    T getX() const { return x; }
    T getY() const { return y; }
    

    Vector2D<T> operator+(const Vector2D<T>& other) const {
        return Vector2D<T>(x + other.x, y + other.y);
    }

    Vector2D<T> operator-(const Vector2D<T>& other) const {
        return Vector2D<T>(x - other.x, y - other.y);
    }
    //Producto escalar
    T operator*(const Vector2D<T>& other) const {
        return x * other.x + y * other.y;
    }
    //Escalar * vector
    Vector2D<T> operator*(const T esc) const {
        return Vector2D<T>(x * esc, y * esc);
    }
    bool operator>=(const T other) const {
        return x >= other;
    }
    bool operator<(const T other) const {
        return x < other;
    }

};
template <typename T>
using Point2D = Vector2D<T>;