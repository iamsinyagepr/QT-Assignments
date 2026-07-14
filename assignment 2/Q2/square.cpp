#include "square.h"
#include "helpers.h"
#include <QPainter>

Square::Square() { }

void Square::draw(QPainter * painter) {

    int size = this->getSize();
    std::vector<int> XY = getXY(painter, size, size);

    painter->drawRect(XY.at(0), XY.at(1), size,  size);
}