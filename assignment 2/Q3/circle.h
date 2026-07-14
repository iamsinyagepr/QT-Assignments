#ifndef CIRCLE_H
#define CIRCLE_H

#include <QDebug>

#include "helpers.h"
#include "shape1property.h"


class QPainter;

class Circle : public Shape1Property
{

private:
    QString className = S_CIRCLE;
public:

    Circle();
    Circle(int penWidth, int penColor, int fillColor, int property1);

    void draw(QPainter *painter) override;
    QString getClassName() override {
        return className;
    }


};

#endif // CIRCLE_H
