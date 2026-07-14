#include "rectangle.h"
#include "helpers.h"
#include <QPainter>

Rectangle::Rectangle() {}

void Rectangle::draw(QPainter * painter)
{

    int w = this->getWidth();
    int h = this->getHeight();
    std::vector<int> XY = getXY(painter, w, h);

    painter->drawRect(XY.at(0), XY.at(1), w, h);
}