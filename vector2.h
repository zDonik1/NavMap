#pragma once

#include <utility>


struct Vector2
{

    // --- Member variables

    int x, y;


    // --- C/D-tors

    Vector2();

    Vector2(int l_x, int l_y);


    // --- Overloaded operators

    Vector2 &&operator+ (const Vector2 &l_rhs);
    Vector2 &&operator- (const Vector2 &l_rhs);
    Vector2 &operator+= (const Vector2 &l_rhs);
    bool operator== (const Vector2 &l_rhs) const;

};
