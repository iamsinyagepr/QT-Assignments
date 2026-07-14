#include "circle.h"
#include "helpers.h"

#include <QPainter>
#include <QPoint>

Circle::Circle() { }

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

    // drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius,
    //                 Qt::SizeMode mode = Qt::AbsoluteSize);

}