#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape2property.h"

class QPainter;

class Ellipse : public Shape2Property
{
public:
    Ellipse();

    void draw(QPainter *painter);

};

#endif // ELLIPSE_H
