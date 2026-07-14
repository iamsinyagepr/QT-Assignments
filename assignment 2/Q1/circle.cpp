#include "circle.h"
#include <QPainter>
#include <QPoint>

Circle::Circle() { }

void Circle::draw(QPainter * painter) {

    // 4. Circle (An ellipse with equal width and height)
    // You can also use a center point and radius: QPoint(center_x, center_y), radius
    painter->drawRoundedRect(
        5,
        5,
        this->getSize(),
        this->getSize(),
        qreal(this->getSize()),
        qreal(this->getSize()),
        Qt::AbsoluteSize
    );

    // drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius,
    //                 Qt::SizeMode mode = Qt::AbsoluteSize);

}