#include "circle.h"
#include "helpers.h"

#include <QPainter>
#include <QPoint>

Circle::Circle() { }

Circle::Circle(int pW, int pC, int fC, int p1) {
    setPenWidth(pW);
    setPenColor(pC);
    setFillColor(fC);
    setProperty1(p1);
}

void Circle::draw(QPainter * painter) {

    int size = this->getSize();
    std::vector<int> XY = getXY(painter, size, size);

    painter->drawRoundedRect(
        XY.at(0),
        XY.at(1),
        this->getSize(),
        this->getSize(),
        qreal(this->getSize()),
        qreal(this->getSize()),
        Qt::AbsoluteSize
    );

}