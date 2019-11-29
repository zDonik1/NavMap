#include "vector2.h"

Vector2::Vector2()
    : x(0)
    , y(0)
{
}

Vector2::Vector2(int l_x, int l_y)
    : x(l_x)
    , y(l_y)
{
}

Vector2 Vector2::operator+(const Vector2 &l_rhs)
{
    return Vector2(x + l_rhs.x, y + l_rhs.y);
}

Vector2 Vector2::operator-(const Vector2 &l_rhs)
{
    return Vector2(x - l_rhs.x, y - l_rhs.y);
}

Vector2 &Vector2::operator+=(const Vector2 &l_rhs)
{
    x += l_rhs.x;
    y += l_rhs.y;
    return *this;
}

bool Vector2::operator==(const Vector2 &l_rhs) const
{
    return x == l_rhs.x && y == l_rhs.y;
}
