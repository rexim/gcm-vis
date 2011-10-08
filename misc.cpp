#include <cmath>
#include "misc.hpp"

Vector2D::Vector2D(float a_x, float a_y):
    x(a_x), y(a_y)
{}

Vector2D &Vector2D::operator+=(const Vector2D &other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D &Vector2D::operator-=(const Vector2D &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2D &Vector2D::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2D &Vector2D::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

float Vector2D::length() const
{
    return sqrt(x * x + y * y);
}

Vector2D operator+(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

Vector2D operator-(const Vector2D &v1, const Vector2D &v2)
{
    return Vector2D(v1.x - v2.x, v1.y - v2.y);
}

Vector2D operator*(const Vector2D &v, float scalar)
{
    return Vector2D(v.x * scalar, v.y * scalar);
}

Vector2D operator*(float scalar, const Vector2D &v)
{
    return v * scalar;
}

Vector2D operator/(const Vector2D &v, float scalar)
{
    return Vector2D(v.x / scalar, v.y / scalar);
}
