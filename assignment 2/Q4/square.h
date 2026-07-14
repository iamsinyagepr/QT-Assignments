#ifndef SQUARE_H
#define SQUARE_H


#include "shape1property.h"
#include "helpers.h"


class QPainter;

class Square: public Shape1Property
{
private:
    QString className = S_SQUARE;
public:
    Square();
    Square(int penWidth, int penColor, int fillColor, int property1);

    void draw(QPainter *painter) override;
    QString getClassName() override {
        return className;
    }
};

#endif // SQUARE_H
