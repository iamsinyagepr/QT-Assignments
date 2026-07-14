#include "rectangle.h"
#include <QPainter>

Rectangle::Rectangle() {}

void Rectangle::draw(QPainter * painter)
{
    painter->drawRect(5, 5, this->getWidth(), this->getHeight());
}