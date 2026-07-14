#include "square.h"
#include "helpers.h"
#include <QPainter>

Square::Square() { }

Square::Square(int pW, int pC, int fC, int p1) {
    setPenWidth(pW);
    setPenColor(pC);
    setFillColor(fC);
    setProperty1(p1);
}


void Square::draw(QPainter * painter) {

    int size = this->getSize();
    std::vector<int> XY = getXY(painter, size, size);

    painter->drawRect(XY.at(0), XY.at(1), size,  size);
}