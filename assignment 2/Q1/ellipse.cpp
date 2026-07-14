#include "ellipse.h"
#include <QPainter>

Ellipse::Ellipse() { }

void Ellipse::draw(QPainter * painter) {
   painter->drawEllipse(5, 5, this->getWidth(), this->getHeight());
}