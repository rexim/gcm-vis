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

#ifndef MISC_HPP
#define MISC_HPP

struct Vector2D
{
    float x, y;

    Vector2D(float a_x = 0.0f, float a_y = 0.0f);

    Vector2D &operator+=(const Vector2D &other);
    Vector2D &operator-=(const Vector2D &other);
    Vector2D &operator*=(float scalar);
    Vector2D &operator/=(float scalar);

    float length() const;
};

Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
Vector2D operator*(const Vector2D &v, float scalar);
Vector2D operator*(float scalar, const Vector2D &v);
Vector2D operator/(const Vector2D &v, float scalar);

#endif // MISC_HPP
