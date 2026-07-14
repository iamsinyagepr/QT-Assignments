#include "ellipse.h"
#include "helpers.h"
#include <QPainter>

Ellipse::Ellipse() { }

void Ellipse::draw(QPainter * painter) {

    int w = this->getWidth();
    int h = this->getHeight();
    std::vector<int> XY = getXY(painter, w, h);

    painter->drawEllipse(XY.at(0), XY.at(1), w, h);
}