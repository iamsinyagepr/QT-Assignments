#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape2property.h"
#include "helpers.h"

class QPainter;

class Rectangle : public Shape2Property
{
private:
    QString className = S_RECTANGLE;
public:
    Rectangle();

    void draw(QPainter *painter);
    QString getClassName() override {
        return className;
    }
};

#endif // RECTANGLE_H
