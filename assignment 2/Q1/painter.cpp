#include "painter.h"
#include <QDebug>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QBrush>

enum SHAPES {
    CIRCLE,
    SQUARE,
    ELLIPSE,
    RECTANGLE
};

QColor getColor(int index) {
    switch(index) {
    case 0:
        return Qt::yellow;
    case 1:
        return Qt::red;
    case 2:
        return Qt::blue;
    case 3:
        return Qt::green;
    default:
        return Qt::black;
    }
}

Painter::Painter(QWidget *parent) : QWidget(parent)
{
    // parent->setStyleSheet("background-color: white;");
}

Shape* Painter::getCurrentShape() {
    switch(currentShape){
    case SHAPES::CIRCLE:
        return circle;
    case SHAPES::SQUARE:
        return square;
    case SHAPES::ELLIPSE:
        return ellipse;
    case SHAPES::RECTANGLE:
        return rectangle;
    }

    return circle;
}

void Painter::updatePen(QColor color, int penWidth, QColor penFill) {
    pen.setColor(color);
    pen.setWidth(penWidth);
    brush.setColor(penFill);
}

void Painter::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    pen.setStyle(Qt::SolidLine);
    brush.setStyle(Qt::SolidPattern);

    Shape* shape = getCurrentShape();
    updatePen(
        getColor(shape->getPenColor()),
        shape->getPenWidth(),
        getColor(shape->getFillColor())
    );


    painter.setPen(pen);
    painter.setBrush(brush);
    shape->draw(&painter);
}

Shape * Painter::draw(int shapeIndex) {
    currentShape = shapeIndex;
    this->update();
    return getCurrentShape();
}


void Painter::setPenColor(int color) {

    getCurrentShape()->setPenColor(color);
    this->update();
}

void Painter::setPenWidth(int width) {

    getCurrentShape()->setPenWidth(width);
    this->update();
}

void Painter::setPenFill(int color) {

    getCurrentShape()->setFillColor(color);
    this->update();
}

