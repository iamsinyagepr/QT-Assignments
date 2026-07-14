#ifndef SQUARE_H
#define SQUARE_H


#include "shape1property.h"

class QPainter;

class Square: public Shape1Property
{
public:
    Square();

    void draw(QPainter *painter) override;

};

#endif // SQUARE_H
