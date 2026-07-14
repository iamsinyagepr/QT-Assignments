#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape2property.h"

class QPainter;

class Rectangle : public Shape2Property
{
public:
    Rectangle();

    void draw(QPainter *painter);

};

#endif // RECTANGLE_H
