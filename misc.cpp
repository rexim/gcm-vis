// Copyright (c) 2011 by rexim
// 
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
