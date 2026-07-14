#ifndef CIRCLE_H
#define CIRCLE_H

#include <QDebug>
#include "shape1property.h"

class QPainter;

class Circle : public Shape1Property
{


public:

    Circle();
    void draw(QPainter *painter) override;
    // int getSize();
    // void setSize(int size);


};

#endif // CIRCLE_H
