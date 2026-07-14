#include "rectangle.h"
#include "helpers.h"
#include <QPainter>

Rectangle::Rectangle() {}

Rectangle::Rectangle(int pW, int pC, int fC, int p1, int p2) {
    setPenWidth(pW);
    setPenColor(pC);
    setFillColor(fC);
    setProperty1(p1);
    setProperty1(p2);
}


void Rectangle::draw(QPainter * painter)
{

    int w = this->getWidth();
    int h = this->getHeight();
    std::vector<int> XY = getXY(painter, w, h);

    painter->drawRect(XY.at(0), XY.at(1), w, h);
}