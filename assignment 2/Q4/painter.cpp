#include "painter.h"
#include "helpers.h"

#include <QDebug>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QBrush>



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

    return nullptr;
}

void Painter::setCurrentShape(int shape) {
    currentShape = shape;
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
    // qDebug() << shape->getClassName();
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

void Painter::draw(Shape* shape) {

    if(!shape) return;

    QString shapeType = shape->getClassName();

    // sets the shape so that proper properties are set
    if(shapeType == S_CIRCLE) currentShape = SHAPES::CIRCLE;
    if(shapeType == S_SQUARE) currentShape = SHAPES::SQUARE;
    if(shapeType == S_ELLIPSE) currentShape = SHAPES::ELLIPSE;
    if(shapeType == S_RECTANGLE) currentShape = SHAPES::RECTANGLE;


    setPenColor(shape->getPenColor());
    setPenWidth(shape->getPenWidth());
    setPenFill(shape->getFillColor());

    this->update();
}

void Painter::setPenColor(int color) {
    getCurrentShape()->setPenColor(color);
}

void Painter::setPenWidth(int width) {
    getCurrentShape()->setPenWidth(width);
}

void Painter::setPenFill(int color) {
    getCurrentShape()->setFillColor(color);
}

