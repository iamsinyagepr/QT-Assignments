#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QPaintEvent>

#include <QPen>
#include <QBrush>

#include "qpainter.h"

#include "shape.h"
#include "square.h"
#include "circle.h"
#include "ellipse.h"
#include "rectangle.h"


class QPainter;
class QString;

class Painter : public QWidget {
    Q_OBJECT

public:
    Painter(QWidget *parent = nullptr);


    QPen pen;
    QBrush brush;

    int currentShape = 0;

    Square* square = new Square();
    Circle* circle = new Circle();
    Ellipse* ellipse = new Ellipse();
    Rectangle* rectangle = new Rectangle();

    void updatePen(QColor color, int penWidth, QColor penFill);


    void setPenColor(int penColor);
    void setPenWidth(int penWidth);
    void setPenFill(int fillColor);

    Shape* getCurrentShape();

    void changeBrushColor();

    Shape* draw(int shape);

protected:
    // This is the crucial method you must override
    void paintEvent(QPaintEvent *event) override;
};

#endif // PAINTER_H