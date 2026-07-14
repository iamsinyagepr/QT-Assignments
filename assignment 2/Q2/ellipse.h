#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape2property.h"
#include "helpers.h"

class QPainter;

class Ellipse : public Shape2Property
{
private:
    QString className = S_ELLIPSE;
public:
    Ellipse();

    void draw(QPainter *painter);
    QString getClassName() override {
        return className;
    }
};

#endif // ELLIPSE_H
