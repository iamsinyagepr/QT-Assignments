#include "square.h"
#include <QPainter>

Square::Square() { }

void Square::draw(QPainter * painter) {
    painter->drawRect(5, 5, this->getSize(),  this->getSize());
}