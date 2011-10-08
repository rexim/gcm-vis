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
